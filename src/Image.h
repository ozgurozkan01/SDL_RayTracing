//
// Created by ozgur on 10/02/2024.
//

#ifndef SDL_RAYTRACING_IMAGE_H
#define SDL_RAYTRACING_IMAGE_H

#include <cstdint>
#include <SDL2/SDL.h>
#include <GLM/glm/glm.hpp>

class Image {
public:
    Image(int width, int height, SDL_Renderer* renderer);
    ~Image();

    void init();
    [[nodiscard]] uint32_t getPixelColor(glm::vec2 coords) const;
    void setPixelColor();
    void display();

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    uint32_t * imagePixels;

    glm::vec3 newVec;

    const int window_width;
    const int window_height;
};


#endif //SDL_RAYTRACING_IMAGE_H
