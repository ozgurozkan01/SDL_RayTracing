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
private:
    float radius;
    glm::vec3 center;
    Material* material;
};


#endif //SDL_RAYTRACING_SPHERE_H
