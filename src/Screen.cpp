//
// Created by ozgur on 10/02/2024.
//

#include "Screen.h"
#include <cstdio>
#include <iostream>

Screen::Screen() :
    WINDOW_NAME("SDL_RayTracing"),
    isRunning(true),
    aspectRatio(16.f / 9.f),
    WINDOW_WIDTH(720),
    groundMaterial(Lambertian(glm::vec3(0.8, 0.8, 0.8))),
    centerMaterial(Lambertian(glm::vec3(0.7, 0.3, 0.3))),
    leftMaterial(Metal(glm::vec3(0.8, 0.8, 0.8), 0.3)),
    rightMaterial(Metal(glm::vec3(0.8, 0.6, 0.2), 1.0)),
    sphereRef(Sphere(glm::vec3(0,-100.5,-1), 100.f, &groundMaterial)),
    sphereRef2(Sphere(glm::vec3( 0.0,    0.0, -1.0),   0.5,  &centerMaterial)),
    sphereRef3(Sphere(glm::vec3(-1.0,0,-1), 0.5f, &leftMaterial)),
    sphereRef4(Sphere(glm::vec3(1.0,0,-1), 0.5f, &rightMaterial)),
    world()
{
    init();
}

Screen::~Screen()
{
    destroy();
}

bool Screen::init()
{
    world.add(&sphereRef);
    world.add(&sphereRef2);
    world.add(&sphereRef3);
    world.add(&sphereRef4);

    WINDOW_HEIGHT = WINDOW_WIDTH / aspectRatio;
    WINDOW_HEIGHT = (WINDOW_HEIGHT < 1) ? 1 : WINDOW_HEIGHT;

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

    camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, renderer);
    return true;
}

void Screen::update()
{
    while (isRunning)
    {
        eventProcess();
        camera->setPixelColors(world);
        camera->render();
    }
}

void Screen::destroy()
{
    delete camera;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

void Screen::eventProcess() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}