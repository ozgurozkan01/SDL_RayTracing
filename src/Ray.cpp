//
// Created by ozgur on 11/02/2024.
//

#include "Ray.h"

Ray::Ray(const glm::vec2 point1, const glm::vec2 point2)
{
    this->point1 = point1;
    this->point2 = point2;
    pointsDiff = point2 - point1;
}
