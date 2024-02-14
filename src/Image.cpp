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

glm::vec4 Image::getPixelColorVector(glm::vec2 coords) const
{
    // P(t) = A + tb -> ray equation
    // t is the multiplier for scalar magnitude (float)
    // A is the origin of sphere (vec)
    glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
    // b is the direction of sphere (vec)
    glm::vec3 rayDirection(coords.x, coords.y, -1);
    float sphereRadius = 1;
    //       (a)t^2     +        (b)t       +          (c)  -> Quadratic Equation
    // (bx^2 + by^2)t^2 + (2(Axbx + Ayby))t + (Ax^2 + Ay^2 - r^2) = 0

    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.f * glm::dot(rayOrigin, rayDirection);
    float c = glm::dot(rayOrigin, rayOrigin) - pow(sphereRadius, 2);

    float discriminant = (b * b) - (4.f * a * c);

    // No Intersection
    if (discriminant < 0.0f)
    {
        return glm::vec4(0, 0, 0, 1);
    }

    // This t value is the smallest, because of  subtraction
    // (-b -+ sqrt(discriminant)) / 2*a
    float smallestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);

    glm::vec3 hitPoint = rayOrigin + rayDirection * smallestT;
    glm::vec3 normal = glm::normalize(hitPoint);

    glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, 1, -1));
    float dotProductOfLight = glm::max(glm::dot(normal,-lightDirection), 0.0f);

    glm::vec3 sphereColor(1, 0, 0);
    sphereColor *= dotProductOfLight;

    return glm::vec4(sphereColor, 1.f);
}

uint32_t Image::ConvertToRGBA(glm::vec4 &colorVector)
{
    // x -> red, y -> green, z -> blue
    // x > others more red
    // y > others more green
    // z > others more blue

    uint8_t red = (uint8_t)(colorVector.x * 255.f);
    uint8_t green = (uint8_t)(colorVector.y * 255.f);
    uint8_t blue = (uint8_t)(colorVector.z * 255.f);
    uint8_t alpha = (uint8_t)(colorVector.a * 255.f);

    uint32_t color = (red << 24) | (green << 16) | (blue << 8) | alpha;

    return color;
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

            glm::vec4 color = getPixelColorVector(pixelCoord);
            // this clamping provides us to not get negative or bigger than 1 value
            // In this way all color values are going to be in [0-1] range -> [0, 255]
            color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
            imagePixels[x + y * image_width] = ConvertToRGBA(color);
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