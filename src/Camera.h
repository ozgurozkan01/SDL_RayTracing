//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_CAMERA_H
#define SDL_RAYTRACING_CAMERA_H

#include "Vector3.h"

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

    Vector3 viewportUpperLeft;
    Vector3 centeredPixelLoc;
    Vector3 viewportU;
    Vector3 viewportV;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;

    // Camera
    Vector3 cameraCenter;
    double focalLength;
    double verticalFOV;
    double thetaAngle;
    double halfHeightVerticalFOV;
    Vector3 lookFrom;
    Vector3 lookAt;
    Vector3 viewUp;
    Vector3 v, u, w;

    void setPixelColors(const class Hittable& world);
    void render();
private:
    void init();
    Vector3 rayColor(const class Ray& ray, int depth, const class Hittable& world);
    Ray getRay(int x, int y);
    [[nodiscard]] Vector3 pixelSampleSquare() const;
};


#endif //SDL_RAYTRACING_CAMERA_H
