cmake_minimum_required(VERSION 3.27)
project(SDL_RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 CONFIG REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(SDL_RayTracing main.cpp
        Screen.cpp
        Screen.h
        Render.cpp
        Render.h)

target_link_libraries(SDL_RayTracing ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)