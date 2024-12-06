#include <Nuntius/Nuntius.hpp>
#include <Nuntius/Game/Event/EventListeners/KeyPressEventListener.hpp>
#include <Nuntius/Game/Event/EventDispatcher.hpp>
#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>
#include <Nuntius/Game/Flecs/FlecsWorld.hpp>
#include <Nuntius/FileServer/JsonFileServer.hpp>
#include <Nuntius/Game/World/WorldLoader.hpp>
#include <Nuntius/Game/Props/RendererProperties.hpp>
#include <Nuntius/Game/Props/WindowProperties.hpp>
#include <Nuntius/Game/Resource/Types.hpp>
#include <Nuntius/Game/Resource/ResourceLoader.hpp>

#include <spdlog/spdlog.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <csignal>

bool isRunning = false;

void SigHandler(int sig) {
    if (sig == SIGINT) {
        spdlog::info("Received SIGINT");
        isRunning = false;
    }
}

int main(int argc, char* argv[]) {
    { // Init
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_pattern("%^[%T] [%l] %v%$");
        spdlog::info("Nuntius Sandbox");

        { // Props
            auto windowProp = std::make_shared<nt::props::WindowProperties>();
            auto rendererProp = std::make_shared<nt::props::RendererProperties>();

            windowProp->width = 1280;
            windowProp->height = 720;
            windowProp->title = "Nuntius Sandbox";

            nt::ObjectRegistry::Provide(windowProp);
            nt::ObjectRegistry::Provide(rendererProp);
        }

        { // Flecs
            auto ecs = std::make_shared<nt::ecs::FlecsWorld>();
            nt::ObjectRegistry::Provide(ecs);
        }

        { // Event
            auto dispatcher = std::make_shared<nt::EventDispatcher>();
            nt::ObjectRegistry::Provide(dispatcher);
            nt::KeyPressListener listener;
            dispatcher->addListener(&listener);
        }

        { // SDL
            if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
                throw std::runtime_error("Error: SDL_Init(): " + std::string(SDL_GetError()));
            }

            if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
                throw std::runtime_error("Error: IMG_Init(): " + std::string(SDL_GetError()));
            }

            if (Mix_Init(MIX_INIT_OGG) == 0) {
                throw std::runtime_error("Error: Mix_Init(): " + std::string(SDL_GetError()));
            }

            {
                // Setup Audio
                SDL_AudioDeviceID deviceId = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;

                auto *spec = new SDL_AudioSpec();
                spec->channels = 2;
                spec->freq = 44100;
                spec->format = SDL_AUDIO_S16LE;
                if (!Mix_OpenAudio(deviceId, spec)) {
                    SDL_Log("Failed to open audio -> %s", SDL_GetError());
                    throw std::runtime_error("Error: Mix_OpenAudio(): " + std::string(SDL_GetError()));
                }
                delete spec;
            }
            auto wp = nt::ObjectRegistry::Get<nt::props::WindowProperties>();
            auto rp = nt::ObjectRegistry::Get<nt::props::RendererProperties>();
            {
                // Set Window Properties
                SDL_PropertiesID props = SDL_CreateProperties();
                SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING,
                                      wp->title.c_str());
                SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, wp->width);
                SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, wp->height);
                SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,
                                      wp->isBorderless); // Borderless
                SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true); // HDPI

                // Init Window
                wp->window = SDL_CreateWindowWithProperties(props);
                if (wp->window == nullptr) {
                    throw std::runtime_error("Error: SDL_CreateWindow(): " + std::string(SDL_GetError()));
                }
                SDL_DestroyProperties(props);
                SDL_Surface *surface = IMG_Load("res/images/logo.png");
                SDL_SetWindowIcon(wp->window, surface);
                SDL_DestroySurface(surface);
            }

            {
                // Init Renderer
                SDL_PropertiesID props = SDL_CreateProperties();
                SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, wp->window);
                SDL_SetNumberProperty(props, SDL_PROP_RENDERER_CREATE_PRESENT_VSYNC_NUMBER,
                                      rp->isVsync ? 1 : 0);
                rp->renderer = SDL_CreateRendererWithProperties(props);
                if (rp->renderer == nullptr) {
                    throw std::runtime_error("Error: SDL_CreateRenderer(): " + std::string(SDL_GetError()));
                }
                SDL_DestroyProperties(props);
            }

            SDL_SetWindowPosition(wp->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

            SDL_SetRenderScale(rp->renderer, 3.0, 3.0);
            SDL_ShowWindow(wp->window);
        }

        { // Resources
            auto loader = std::make_shared<nt::res::ResourceLoader>();
            nt::ObjectRegistry::Provide(loader);

            std::vector<nt::types::ResourceInfo> resources = {
                    {nt::types::ResourceType::eTexture, "test.logo", "res/images/logo.png"},
                    {nt::types::ResourceType::eTexture, "test.air", "res/images/air.png"},
                    {nt::types::ResourceType::eTexture, "test.floor", "res/images/floor.png"},
                    {nt::types::ResourceType::eTexture, "test.flower", "res/images/flower.png"}
            };
            for (const auto& res : resources) {
                loader->Add<nt::types::Texture>(res.id, res.path);
            }
        }

        { // World Loader
            auto world = std::make_shared<nt::world::World>();
            auto room = std::make_shared<nt::world::Room>();
            nt::ObjectRegistry::Provide(world);
            nt::ObjectRegistry::Provide(room);

            auto loader = std::make_shared<nt::world::WorldLoader>();
            nt::fileserver::JsonFileServer jsonFileServer;
            nlohmann::json meta, map, tile;
            std::vector<std::string> worlds = {"world1"};
            int currentWorld = 0;
            jsonFileServer.read(std::format("res/map/{}/meta.json", worlds[currentWorld]).c_str(), meta);
            jsonFileServer.read(std::format("res/map/{}/{}", worlds[currentWorld],meta["map"].get<std::string>()).c_str(), map);
            jsonFileServer.read(std::format("res/map/{}/{}",worlds[currentWorld], meta["tile"].get<std::string>()).c_str(), tile);
            loader->uploadTileCollection(tile);
            loader->uploadWorld(map);
            loader->uploadWorldStruct(meta["struct"]);
            loader->load();
            nt::ObjectRegistry::Provide(loader);
            spdlog::info("Current Room: {}", room->rID);

            for (int i = 0; i < 25; i+= 5) {
                for (int j = 0; j < 5; j++) {
                    std::cout << room->getTailGrid()[i+j].info.tileID << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    nt::LKeyPressEvent e(1, false);

    { // Game Loop
        auto eventPatcher = nt::ObjectRegistry::Get<nt::EventDispatcher>();
        auto ecs = nt::ObjectRegistry::Get<nt::ecs::FlecsWorld>();
        auto wp = nt::ObjectRegistry::Get<nt::props::WindowProperties>();
        auto rp = nt::ObjectRegistry::Get<nt::props::RendererProperties>();
        auto res = nt::ObjectRegistry::Get<nt::res::ResourceLoader>();

        isRunning = true;
        while (isRunning) {
            SDL_SetRenderDrawColor(rp->renderer, 35, 35, 35, 255);
            SDL_RenderClear(rp->renderer);
//            std::cout << "\x1B[2J" << std::flush;
            std::signal(SIGINT, SigHandler);
            eventPatcher->dispatch(e);

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                    isRunning = false;
                if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(wp->window))
                    isRunning = false;
            }

            { // Draw Room
                auto room = nt::ObjectRegistry::Get<nt::world::Room>();
                auto world = nt::ObjectRegistry::Get<nt::world::World>();

                for (const auto& tile : room->getTailGrid()) {
                    auto t = world->tiles[tile.info.tileID];
                    auto* texture = dynamic_cast<nt::types::Texture*>(res->Get(t["texID"]).get());
                    SDL_FRect dst = {(float)(tile.info.pos.x*texture->w), (float)(tile.info.pos.y*texture->h), (float)(tile.info.pos.x + texture->w), (float)(tile.info.pos.y + texture->h)};
                    SDL_FRect src = {0, 0, (float)texture->w, (float)texture->h};
                    SDL_RenderTexture(rp->renderer, texture->texture, &src, &dst );
                    SDL_SetRenderDrawColor(rp->renderer, 255, 0, 0, 255);
                    SDL_RenderRect(rp->renderer, &dst);
                }
            }

            ecs->world.progress(15.0f);

            // Present
            SDL_RenderPresent(rp->renderer);
        }
    }

    { // Cleanup
        auto wp = nt::ObjectRegistry::Get<nt::props::WindowProperties>();
        auto rp = nt::ObjectRegistry::Get<nt::props::RendererProperties>();
        Mix_CloseAudio();

        SDL_DestroyWindow(wp->window);
        SDL_DestroyRenderer(rp->renderer);
        nt::ObjectRegistry::Destroy();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;
    }
}