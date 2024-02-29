
#ifndef SDL_RAYTRACING_CAMERA_H
#define SDL_RAYTRACING_CAMERA_H

#include "Vector3.h"
#include "Ray.h"
#include "PPM.h"

class Camera
{
public:
    Camera(int _windowWidth, int _windoHeight, SDL_Renderer* renderer);
    ~Camera();

    void setPixelColors(const class Hittable& world);
    void render();

private:
    PPM* ppmImage;

    SDL_Renderer* renderer;
    SDL_Texture* texture;

    uint32_t* pixels;
    int windowWidth;
    int windowHeight;
    int samplesPerPixel;
    int maxDepth;
    int focusDistance;

    double verticalFOV;
    double difocusAngle;
    double thetaAngle;
    double halfHeightVerticalFOV;
    double viewportHeight;
    double viewportWidth;
    double defocusRadius;


    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;
    Vector3 viewportUpperLeft;
    Vector3 centeredPixelLoc;
    Vector3 viewportU;
    Vector3 viewportV;
    Vector3 u, v,w ;
    Vector3 cameraCenter;
    Vector3 lookFrom;
    Vector3 lookAt;
    Vector3 viewUp;
    Vector3 defocusDiskV;
    Vector3 defocusDiskU;

    void init();

    Vector3 pixelSampleSquare() const;
    Vector3 rayColor(const Ray& ray, int depth, const Hittable& world);
    Vector3 defocusDiskSample();
    Ray getRay(int x, int y);
};

#endif //SDL_RAYTRACING_CAMERA_H