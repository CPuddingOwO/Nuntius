cmake_minimum_required(VERSION 3.28)
project(Nuntius)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(FLECS_SHARED ON)
set(SDLIMAGE_BUILD_SHARED_LIBS ON)
set(SDLMIXER_BUILD_SHARED_LIBS ON)
set(SDL_SHARED ON)
set(SDL_STATIC OFF)

# Set libraries

if (NOT DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR NOT CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install")
endif ()

include(GNUInstallDirs)
list(APPEND CMAKE_MODULE_PATH "${CatBirdRemake_SOURCE_DIR}/cmake")

# add_subdirectory(...)
add_subdirectory(ext/flecs)
add_subdirectory(ext/sdl)
add_subdirectory(ext/sdl_image)
add_subdirectory(ext/sdl_mixer)
# find_package(...)
find_package(spdlog)
find_package(stb)
find_package(nlohmann_json)
#find_package(flecs)

set(SRC_CODE
        src/Nuntius.cpp
        src/ObjectRegistry/ObjectRegistry.cpp
        src/Game/Event/EventDispatcher.cpp
        src/Game/Event/EventRegister.cpp
        src/Game/Event/Events/UPlayerSpawn.cpp
        src/Game/Event/Events/LKeyPress.cpp
        src/Game/Event/Events/LMouseClick.cpp
        src/Game/Event/EventListeners/KeyPressEventListener.cpp
        src/Game/Flecs/FlecsWorld.cpp
        src/Game/Flecs/FlecsSystems.cpp
        src/Game/Flecs/FlecsHelper.cpp
        src/Game/World/World.cpp
        src/Game/World/WorldLoader.cpp
        src/Game/World/Room.cpp
        src/FileServer/JsonFileServer.cpp
        src/StringEx.cpp
        src/Game/World/Tile.cpp
        inc/Nuntius/Vecturm.hpp
        src/Game/Resource/ResourceLoader.cpp
        src/Game/Resource/Types.cpp
        src/FileServer/ImageFileServer.cpp
)

set(SANDBOX_CODE
        sandbox/main.cpp
)

# Library
add_library(Nuntius SHARED ${SRC_CODE})
install(TARGETS Nuntius SDL3-shared SDL3_image-shared SDL3_mixer-shared
        LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_compile_definitions( Nuntius PRIVATE
        NUNTIUS_EXPORTS
)

target_include_directories(Nuntius PUBLIC
        inc
)

target_link_libraries(Nuntius PUBLIC
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        stb::stb
        flecs::flecs
        SDL3::SDL3-shared
        SDL3_mixer-shared
        SDL3_image-shared
)

# Sandbox
add_executable(sandbox ${SANDBOX_CODE})
install(TARGETS sandbox
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(sandbox PRIVATE
        Nuntius
        spdlog::spdlog
)

