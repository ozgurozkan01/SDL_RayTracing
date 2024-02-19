//
// Created by ozgur on 18/02/2024.
//

#ifndef SDL_RAYTRACING_RAY_H
#define SDL_RAYTRACING_RAY_H

#include "GLM/glm/glm.hpp"

class Sphere;

class Ray {
public:
    Ray() = default;
    Ray(const glm::vec3& _origin, const glm::vec3& _direction);

    [[nodiscard]] glm::vec3 getOrigin() const;
    [[nodiscard]] glm::vec3 getDirection() const;
    [[nodiscard]] glm::vec3 at(float t) const;

    glm::vec3 rayColor(const Ray& ray, const class Hittable& world);
private:
    glm::vec3 origin;
    glm::vec3 direction;
};


#endif //SDL_RAYTRACING_RAY_H
