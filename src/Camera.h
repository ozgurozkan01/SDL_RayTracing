//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_CAMERA_H
#define SDL_RAYTRACING_CAMERA_H

#include "GLM/glm/glm.hpp"

class Camera {
public:
    Camera(int _windowWidth, int _windowHeight, class SDL_Renderer* renderer);
    ~Camera();

    int windowWidth;
    int windowHeight;
    int samplesPerPixel;
    int maxDepth;

    class SDL_Texture* texture;
    SDL_Renderer* renderer;
    uint32_t * pixels;

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

    void setPixelColors(const class Hittable& world);
    void render();
private:
    void init();
    glm::vec3 rayColor(const class Ray& ray, int depth, const class Hittable& world);
    Ray getRay(int x, int y);
    [[nodiscard]] glm::vec3 pixelSampleSquare() const;
};


#endif //SDL_RAYTRACING_CAMERA_H
