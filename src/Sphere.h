//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_SPHERE_H
#define SDL_RAYTRACING_SPHERE_H

#include <memory>
#include "Vector3.h"
#include "Hittable.h"

class Sphere : public Hittable{
public:
public:
    Sphere(Vector3 _center, float _radius, std::shared_ptr<Material> material);
    bool isHit(const Ray& ray, double ray_tmin, double ray_tmax, HitInfo& hitInfo) const override;
private:
    float radius;
    Vector3 center;
    std::shared_ptr<Material> material;
};


#endif //SDL_RAYTRACING_SPHERE_H
