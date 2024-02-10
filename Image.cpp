//
// Created by ozgur on 10/02/2024.
//

#include "Image.h"
#include <iostream>

Image::Image(int width, int height, SDL_Renderer* renderer) :
    window_width(width),
    window_height(height),
    renderer(renderer)
{
    init();
    std::cout << newVec.x << ", " << newVec.y << std::endl;
}

Image::~Image()
{
    delete [] imagePixels;
    SDL_DestroyTexture(texture);
}

void Image::init()
{
    imagePixels = new uint32_t[window_width * window_height];
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC,
                                window_width,
                                window_height);
}

uint32_t Image::getPixelColor(glm::vec2 coords) const
{
    uint8_t red = (coords.x) / (window_width-1) * 255;
    uint8_t green = (double(coords.y) / (window_height-1)) * 255;

    uint32_t pixelColor = 0x00000000;
    pixelColor += red;
    pixelColor <<= 8;
    pixelColor += green;
    pixelColor <<= 8;
    pixelColor += 0x00;
    pixelColor <<= 8;
    pixelColor += 0xFF;

    return pixelColor;
}

void Image::setPixelColor()
{
    for (int y = 0; y < window_height; ++y)
    {
        for (int x = 0; x < window_width; ++x)
        {
            glm::vec2 pixelCoord(x, y);
            imagePixels[x + y * window_width] = getPixelColor(pixelCoord);
        }
    }
}

void Image::display()
{
    setPixelColor();
    SDL_UpdateTexture(texture, nullptr, imagePixels, window_width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}