//
// Created by ozgur on 10/02/2024.
//

#ifndef SDL_RAYTRACING_IMAGE_H
#define SDL_RAYTRACING_IMAGE_H

#include <cstdint>
#include <SDL2/SDL.h>
#include <GLM/glm/glm.hpp>
#include "Sphere.h"
#include "HittableCollection.h"

class Camera;
class Sphere;

class Image {
public:
    Image(int width, int height, SDL_Renderer* renderer, Camera* camera);
    ~Image();

    void display();
private:

    void init();
    void setPixelColor();

    SDL_Texture* texture;
    SDL_Renderer* renderer;
    uint32_t * imagePixels;

    Camera* cameraRef;
    Sphere sphereRef;
    Sphere sphereRef2;
    HittableCollection world;

    const int image_width;
    const int image_height;
};


#endif //SDL_RAYTRACING_IMAGE_H
