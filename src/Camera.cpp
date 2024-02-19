//
// Created by ozgur on 19/02/2024.
//

#include <iostream>
#include "Camera.h"

Camera::Camera(int _windowWidth, int _windowHeight) :
    windowHeight(_windowHeight),
    windowWidth(_windowWidth),
    focalLength(1.f),
    viewportHeight(2.f),
    cameraCenter(0, 0, 0)
{
    init();
}

void Camera::init()
{
    viewportWidth = viewportHeight * (static_cast<double>(windowWidth) / windowHeight);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewportU = glm::vec3(viewportWidth, 0, 0);
    viewportV = glm::vec3(0, -viewportHeight, 0);
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixelDeltaU = viewportU / (float)windowWidth;
    pixelDeltaV = viewportV / (float)windowHeight;
    // Calculate the location of the upper left pixel.
    viewportUpperLeft = cameraCenter - glm::vec3(0, 0, focalLength) - (viewportU / (float)2) - (viewportV / (float)2);
    centeredPixelLoc = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
}
