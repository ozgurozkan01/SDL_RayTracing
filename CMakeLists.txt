cmake_minimum_required(VERSION 3.27)
project(SDL_RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 CONFIG REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(SDL_RayTracing src/main.cpp
        src/Screen.cpp
        src/Screen.h
        src/Ray.cpp
        src/Ray.h
        src/Camera.cpp
        src/Camera.h
        src/Hittable.cpp
        src/Hittable.h
        src/Sphere.cpp
        src/Sphere.h
        src/HittableCollection.cpp
        src/HittableCollection.h
        src/Material.cpp
        src/Material.h
        src/Vector3.h
        src/PPM.cpp
        src/PPM.h
)

target_link_libraries(SDL_RayTracing ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)