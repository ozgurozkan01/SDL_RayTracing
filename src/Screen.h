//
// Created by ozgur on 10/02/2024.
//

#ifndef SDL_RAYTRACING_SCREEN_H
#define SDL_RAYTRACING_SCREEN_H

#include <SDL2/SDL.h>
#include "Camera.h"
#include "Sphere.h"
#include "HittableCollection.h"
#include "Material.h"

class Screen {
private:
    SDL_Window* mainWindow{};
    SDL_Renderer* renderer{};

    Camera* camera;
    HittableCollection world;

    bool isRunning;

    const int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    const char* WINDOW_NAME;

    float aspectRatio;

    bool init();
    void eventProcess();
    void destroy();
    void sphereGenerator();

public:
    Screen();
    ~Screen();

    void update();
};


#endif //SDL_RAYTRACING_SCREEN_H
