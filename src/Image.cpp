//
// Created by ozgur on 10/02/2024.
//

#include "Image.h"
#include <iostream>

Image::Image(int width, int height, SDL_Renderer* renderer) :
        image_width(width),
        image_height(height),
        renderer(renderer)
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
}

uint32_t Image::getPixelColor(glm::vec2 coords) const
{
    // P(t) = A + tb -> ray equation
    // A is the origin of sphere (vec)
    glm::vec3 rayOrigin(0.0f, 0.f, 2.f);
    // b is the direction of sphere (vec)
    glm::vec3 rayDirection(coords.x, coords.y, -1);
    // t is the multiplier for scalar magnitude (float)

    float sphereRadius = 0.5;

    //       (a)t^2     +        (b)t       +          (c)  -> Quadratic Equation
    // (bx^2 + by^2)t^2 + (2(Axbx + Ayby))t + (Ax^2 + Ay^2 - r^2) = 0

    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.f * glm::dot(rayOrigin, rayDirection);
    float c = glm::dot(rayOrigin, rayOrigin) - pow(sphereRadius, 2);

    float discriminant = b*b - 4.f*a*c;

    if (discriminant >= 0)
    {
        return 0xFF0000FF;
    }

    return 0x000000FF;
}

void Image::setPixelColor()
{
    for (int y = 0; y < image_height; ++y)
    {
        for (int x = 0; x < image_width; ++x)
        {
            glm::vec2 pixelCoord((float)x / (float)image_width, (float)y / (float)image_height);
            // Update pixel range
            pixelCoord = (pixelCoord * 2.0f) - 1.f;
            pixelCoord.x *= (image_width / (float)image_height);
            imagePixels[x + y * image_width] = getPixelColor(pixelCoord);
        }
    }
}

void Image::display()
{
    setPixelColor();
    SDL_UpdateTexture(texture, nullptr, imagePixels, image_width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}