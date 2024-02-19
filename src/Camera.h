//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_CAMERA_H
#define SDL_RAYTRACING_CAMERA_H

#include "GLM/glm/glm.hpp"

class Camera {
public:
    Camera(int _windowWidth, int _windowHeight);

    int windowWidth;
    int windowHeight;

    double viewportHeight;
    double viewportWidth;

    glm::vec3 viewportUpperLeft;
    glm::vec3 centeredPixelLoc;
    glm::vec3 viewportU;
    glm::vec3 viewportV;
    glm::vec3 pixelDeltaU;
    glm::vec3 pixelDeltaV;

    glm::vec3 cameraCenter;
    double focalLength;
private:
    void init();
};


#endif //SDL_RAYTRACING_CAMERA_H
