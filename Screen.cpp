//
// Created by ozgur on 10/02/2024.
//

#include "Screen.h"
#include <stdio.h>

Screen::Screen() :
    WINDOW_HEIGHT(720),
    WINDOW_WIDTH(1280),
    WINDOW_NAME("SDL_RayTracing"),
    isRunning(true)
{
    init();
}

Screen::~Screen()
{
    destroy();
}

bool Screen::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    mainWindow = SDL_CreateWindow(WINDOW_NAME,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  WINDOW_WIDTH,
                                  WINDOW_HEIGHT,
                                  SDL_WINDOW_SHOWN);

    if (mainWindow == nullptr)
    {
        SDL_Quit();
        printf("error creating window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        printf("error creating renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Screen::update()
{
    while (isRunning)
    {
        eventProcess();
        render();
    }
}

void Screen::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

void Screen::eventProcess()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }
}

void Screen::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255 ,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
