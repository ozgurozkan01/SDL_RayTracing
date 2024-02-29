//
// Created by ozgur on 10/02/2024.
//

#include "Screen.h"
#include <cstdio>
#include <memory>

Screen::Screen() :
    WINDOW_NAME("SDL_RayTracing"),
    isRunning(true),
    aspectRatio(16.f / 9.f),
    WINDOW_WIDTH(720),
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
    sphereGenerator();

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

void Screen::sphereGenerator()
{
    std::shared_ptr<Lambertian> groundMaterial = std::make_shared<Lambertian>(Vector3(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Vector3(0,-1000.0,0), 1000.f, groundMaterial));
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Vector3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Vector3(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    std::shared_ptr<Lambertian> sphereMaterial= std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    std::shared_ptr<Metal> sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else {
                    // glass
                    std::shared_ptr<Dielectric> sphereMaterial = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    std::shared_ptr<Dielectric> material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vector3(0, 1, 0), 1.0, material1));

    std::shared_ptr<Lambertian> material2= std::make_shared<Lambertian>(Vector3(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Vector3(-4, 1, 0), 1.0, material2));

    std::shared_ptr<Metal> material3 = std::make_shared<Metal>(Vector3(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Vector3(4, 1, 0), 1.0, material3));
}
