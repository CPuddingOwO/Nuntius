#include <Nuntius/Nuntius.hpp>
#include <Nuntius/Game/Event/EventListeners/KeyPressEventListener.hpp>
#include <Nuntius/Game/Event/EventDispatcher.hpp>
#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>
#include <Nuntius/Game/Flecs/FlecsWorld.hpp>

#include <Nuntius/Game/World/WorldLoader.hpp>

#include <spdlog/spdlog.h>
#include <csignal>
#include "Nuntius/FileServer/JsonFileServer.hpp"

bool isRunning = false;

void exitHandler(int sig) {
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
            loader->uploadMapData(map);
            nt::ObjectRegistry::Provide(loader);
            spdlog::info("Current Room: {}", room->rID);
        }
    }

    nt::LKeyPressEvent e(1, true);

    { // Game Loop
        auto event = nt::ObjectRegistry::Get<nt::EventDispatcher>();
        auto ecs = nt::ObjectRegistry::Get<nt::ecs::FlecsWorld>();

        isRunning = true;
        while (isRunning) {
//            std::cout << "\x1B[2J" << std::flush;
            std::signal(SIGINT, exitHandler);
            event->dispatch(e);
            ecs->world.progress(15.0f);
        }
    }

    { // Cleanup

        nt::ObjectRegistry::Destroy();
        return 0;
    }
}