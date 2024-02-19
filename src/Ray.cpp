//
// Created by ozgur on 18/02/2024.
//

#include "Ray.h"
#include "Sphere.h"

const double infinity = std::numeric_limits<double>::infinity();

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

glm::vec3 Ray::rayColor(const Ray &ray, const class Hittable& world)
{
    HitInfo hitInfo;
    if (world.isHit(ray, 0, infinity, hitInfo)) {
        return 0.5f * (hitInfo.normal + glm::vec3(1,1,1));
    }

    glm::vec3 unitDirection = glm::normalize(ray.getDirection());
    auto a = 0.5*(unitDirection.y + 1.0);
    return ((1.0f - (float)a) * glm::vec3(1.0, 1.0, 1.0)) + ((float)a * glm::vec3(0.5, 0.7, 1.0));
}