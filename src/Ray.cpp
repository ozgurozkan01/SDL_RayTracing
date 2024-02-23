//
// Created by ozgur on 18/02/2024.
//

#include "Ray.h"

Ray::Ray(const glm::vec3 &_origin, const glm::vec3 &_direction):
    origin(_origin),
    direction(_direction) {}

glm::vec3 Ray::getOrigin() const {
    return origin;
}

glm::vec3 Ray::getDirection() const {
    return direction;
}

glm::vec3 Ray::at(float t) const {
    return origin + (t * direction);
}