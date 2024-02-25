//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_SPHERE_H
#define SDL_RAYTRACING_SPHERE_H

#include "GLM/glm/glm.hpp"
#include "Hittable.h"

class Sphere : public Hittable{
public:
public:
    Sphere(glm::vec3 _center, float _radius, Material* material);
    bool isHit(const Ray& ray, double ray_tmin, double ray_tmax, HitInfo& hitInfo) const override;

    static glm::vec3 randomVector();
    static glm::vec3 randomVector(double min, double max);
    static glm::vec3 randomPointInUnitSphere();
    static glm::vec3 randomUnitVector();
    static glm::vec3 randomOnHemisphere(const glm::vec3& normal);
    static bool isDirectionNearZero(const glm::vec3& direction);
private:
    float radius;
    glm::vec3 center;
    Material* material;
};


#endif //SDL_RAYTRACING_SPHERE_H
