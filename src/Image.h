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

    void display();

    inline int getImageWidth() const { return image_width; }
    inline int getImageHeight() const { return image_height; }
private:

    void init();
    [[nodiscard]] glm::vec4 getPixelColorVector(glm::vec2 coords) const;
    uint32_t ConvertToRGBA(glm::vec4& colorVector);
    void setPixelColor();
    void shading();

    SDL_Texture* texture;
    SDL_Renderer* renderer;
    uint32_t * imagePixels;

    glm::vec3 newVec;

    const int image_width;
    const int image_height;
};


#endif //SDL_RAYTRACING_IMAGE_H
