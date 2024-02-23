//
// Created by ozgur on 19/02/2024.
//

#include <iostream>
#include "Camera.h"
#include "Ray.h"
#include "Hittable.h"
#include "SDL2/SDL.h"

const double infinity = std::numeric_limits<double>::infinity();

Camera::Camera(int _windowWidth, int _windowHeight, SDL_Renderer* renderer) :
    windowHeight(_windowHeight),
    windowWidth(_windowWidth),
    focalLength(1.f),
    viewportHeight(2.f),
    cameraCenter(0, 0, 0),
    renderer(renderer)
{
    init();
}

void Camera::init()
{
    imagePixels = new uint32_t[windowWidth * windowHeight];
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC,
                                windowWidth,
                                windowHeight);

    viewportWidth = viewportHeight * (static_cast<double>(windowWidth) / windowHeight);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewportU = glm::vec3(viewportWidth, 0, 0);
    viewportV = glm::vec3(0, -viewportHeight, 0);
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixelDeltaU = viewportU / (float)windowWidth;
    pixelDeltaV = viewportV / (float)windowHeight;
    // Calculate the location of the upper left pixel.
    viewportUpperLeft = cameraCenter - glm::vec3(0, 0, focalLength) - (viewportU / (float)2) - (viewportV / (float)2);
    centeredPixelLoc = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
}

glm::vec3 Camera::rayColor(const Ray &ray, const class Hittable& world)
{
    HitInfo hitInfo;
    if (world.isHit(ray, 0, infinity, hitInfo)) {
        return 0.5f * (hitInfo.normal + glm::vec3(1,1,1));
    }

    glm::vec3 unitDirection = glm::normalize(ray.getDirection());
    auto a = 0.5*(unitDirection.y + 1.0);
    return ((1.0f - (float)a) * glm::vec3(1.0, 1.0, 1.0)) + ((float)a * glm::vec3(0.5, 0.7, 1.0));
}

void Camera::setPixelColors(const Hittable &world)
{
    for (int y = 0; y < windowHeight; ++y)
    {
        for (int x = 0; x < windowWidth; ++x)
        {
            auto pixelCenter = centeredPixelLoc + ((float)x * pixelDeltaU) + ((float)y * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            glm::vec3 pixelColorVector = rayColor(r, world);
            int red = static_cast<int>(255.999 * pixelColorVector.r);
            int green = static_cast<int>(255.999 * pixelColorVector.g);
            int blue = static_cast<int>(255.999 * pixelColorVector.b);
            int alpha = 255;

            uint32_t pixelColor = (red << 24) | (green << 16) | (blue << 8) | alpha;
            imagePixels[x + y * windowWidth] = pixelColor;
        }
    }
}


void Camera::render()
{
    SDL_UpdateTexture(texture, nullptr, imagePixels, windowWidth * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

Camera::~Camera()
{
    delete [] imagePixels;
    SDL_DestroyTexture(texture);
}
