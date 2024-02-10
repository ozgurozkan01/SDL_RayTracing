//
// Created by ozgur on 10/02/2024.
//

#ifndef SDL_RAYTRACING_SCREEN_H
#define SDL_RAYTRACING_SCREEN_H

#include <SDL2/SDL.h>
#include "Image.h"

class Screen {
private:
    SDL_Window* mainWindow{};
    SDL_Renderer* renderer{};

    Image* image;

    bool isRunning;

    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const char* WINDOW_NAME;
public:
    Screen();
    ~Screen();

    bool init();

    void update();
    void eventProcess();
    void render();

    void destroy();
};


#endif //SDL_RAYTRACING_SCREEN_H
