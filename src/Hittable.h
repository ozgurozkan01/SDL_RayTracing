//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_HITTABLE_H
#define SDL_RAYTRACING_HITTABLE_H

#include "Ray.h"
#include "Vector3.h"
#include <memory>

class Material;

struct HitInfo
{
    Vector3 p;
    Vector3 normal;
    double t;

    std::shared_ptr<Material> material;

    bool frontFace;

    void setFaceNormal(const Ray& r, const Vector3& outwardNormal)
    {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outwardNormal` is assumed to have unit length.
        frontFace = dot(r.getDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool isHit(const Ray& r, double ray_tmin, double ray_tmax, HitInfo& rec) const = 0;
};


#endif //SDL_RAYTRACING_HITTABLE_H
