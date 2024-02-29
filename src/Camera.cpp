//
// Created by ozgur on 19/02/2024.
//
#include "SDL2/SDL.h"
#include <cstdlib>
#include "Camera.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"

const double infinity = std::numeric_limits<double>::infinity();

Camera::Camera(int _windowWidth, int _windowHeight, SDL_Renderer* renderer) :
        windowHeight(_windowHeight),
        windowWidth(_windowWidth),
        renderer(renderer),
        samplesPerPixel(20),
        maxDepth(15),
        verticalFOV(20.0),
        lookFrom(-2,2,1),
        lookAt(0,0,-1),
        viewUp(0, 1, 0)
{
    init();
}

void Camera::init()
{
    cameraCenter = lookFrom;
    focalLength = (lookAt - lookFrom).length();

    pixels = new uint32_t[windowWidth * windowHeight];
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC,
                                windowWidth,
                                windowHeight);

    thetaAngle = verticalFOV * (M_PI / 180);
    halfHeightVerticalFOV = tan(thetaAngle/2);
    viewportHeight = 2 * halfHeightVerticalFOV * focalLength;
    viewportWidth = viewportHeight * (static_cast<double>(windowWidth) / windowHeight);

    w = normalize(lookFrom - lookAt);
    u = normalize(cross(viewUp, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewportU = viewportWidth * u;
    viewportV = -viewportHeight * v;
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixelDeltaU = viewportU / (float)windowWidth;
    pixelDeltaV = viewportV / (float)windowHeight;
    // Calculate the location of the upper left pixel.
    viewportUpperLeft = cameraCenter - (focalLength * w) - (viewportU / (float)2) - (viewportV / (float)2);
    centeredPixelLoc = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
}

Vector3 Camera::rayColor(const Ray &ray, int depth, const class Hittable& world)
{
    HitInfo hitInfo;

    if (depth <= 0)
    {
        return {0,0,0};
    }

    if (world.isHit(ray, 0.001, infinity, hitInfo))
    {
        Ray scatteredRay;
        Vector3 attenuation;
        if (hitInfo.material->scatter(ray, hitInfo, attenuation, scatteredRay))
        {
            return attenuation * rayColor(scatteredRay, depth-1, world);
        }

        return {0, 0, 0};
    }

    Vector3 unitDirection = normalize(ray.getDirection());
    float a = 0.5f * (unitDirection.y() + 1.0f);
    return ((1.0f - (float)a) * Vector3(1.0, 1.0, 1.0)) + ((float)a * Vector3(0.5, 0.7, 1.0));
}

void Camera::setPixelColors(const Hittable &world)
{
    for (int y = 0; y < windowHeight; ++y)
    {
        for (int x = 0; x < windowWidth; ++x)
        {
            Vector3 pixelColorVector(0, 0, 0);

            for (int i = 0; i < samplesPerPixel; ++i)
            {
                /** Anti-aliasing to smooth color transition */
                Ray r = getRay(x, y);
                pixelColorVector += rayColor(r, maxDepth, world);
            }

            pixelColorVector /= samplesPerPixel;
            int red = static_cast<int>(255 * sqrt(pixelColorVector.x()));
            int green = static_cast<int>(255 * sqrt(pixelColorVector.y()));
            int blue = static_cast<int>(255 * sqrt(pixelColorVector.z()));
            int alpha = 255;

            uint32_t pixelColor = (red << 24) | (green << 16) | (blue << 8) | alpha;
            pixels[x + y * windowWidth] = pixelColor;
        }
    }
}


void Camera::render()
{
    SDL_UpdateTexture(texture, nullptr, pixels, windowWidth * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

Camera::~Camera()
{
    delete [] pixels;
    SDL_DestroyTexture(texture);
}

Vector3 Camera::pixelSampleSquare() const
{
    // Returns a random point in the square surrounding a pixel at the origin.
    auto px = -0.5 + rand() / (RAND_MAX + 1.0);
    auto py = -0.5 + rand() / (RAND_MAX + 1.0);
    return ((float)px * pixelDeltaU) + ((float)py * pixelDeltaV);
}

Ray Camera::getRay(int x, int y)
{
    auto pixelCenter = centeredPixelLoc + ((float)x * pixelDeltaU) + ((float)y * pixelDeltaV);
    auto pixelSample = pixelCenter + pixelSampleSquare();

    auto rayOrigin = cameraCenter;
    auto rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}