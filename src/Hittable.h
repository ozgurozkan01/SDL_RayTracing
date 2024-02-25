//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_HITTABLE_H
#define SDL_RAYTRACING_HITTABLE_H

#include "Ray.h"
#include "GLM/glm/glm.hpp"

class Material;

struct HitInfo
{
    glm::vec3 p;
    glm::vec3 normal;
    double t;

    Material* material;

    bool frontFace;

    void setFaceNormal(const Ray& r, const glm::vec3& outwardNormal)
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
