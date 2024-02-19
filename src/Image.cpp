//
// Created by ozgur on 10/02/2024.
//

#include "Image.h"
#include <iostream>
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "HittableCollection.h"

Image::Image(int width, int height, SDL_Renderer* renderer, Camera* camera) :
        image_width(width),
        image_height(height),
        renderer(renderer),
        cameraRef(camera),
        sphereRef(glm::vec3(0,0,-1), 0.5f),
        sphereRef2(glm::vec3(0,-100.5,-1), 100),
        world()
{
    init();
}

Image::~Image()
{
    delete [] imagePixels;
    SDL_DestroyTexture(texture);
}

void Image::init()
{
    imagePixels = new uint32_t[image_width * image_height];
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC,
                                image_width,
                                image_height);


    world.add(&sphereRef);
    world.add(&sphereRef2);
}

void Image::display()
{
    setPixelColor();

    SDL_UpdateTexture(texture, nullptr, imagePixels, image_width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Image::setPixelColor()
{
    for (int y = 0; y < image_height; ++y)
    {
        for (int x = 0; x < image_width; ++x)
        {
            auto pixelCenter = cameraRef->centeredPixelLoc + ((float)x * cameraRef->pixelDeltaU) + ((float)y * cameraRef->pixelDeltaV);
            auto rayDirection = pixelCenter - cameraRef->cameraCenter;
            Ray r(cameraRef->cameraCenter, rayDirection);

            glm::vec3 pixelColorVector = r.rayColor(r, world);
            int red = static_cast<int>(255.999 * pixelColorVector.r);
            int green = static_cast<int>(255.999 * pixelColorVector.g);
            int blue = static_cast<int>(255.999 * pixelColorVector.b);
            int alpha = 255;

            uint32_t pixelColor = (red << 24) | (green << 16) | (blue << 8) | alpha;
            imagePixels[x + y * image_width] = pixelColor;
        }
    }
}
