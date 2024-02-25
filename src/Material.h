//
// Created by ozgur on 25/02/2024.
//

#ifndef SDL_RAYTRACING_MATERIAL_H
#define SDL_RAYTRACING_MATERIAL_H

#include "Ray.h"

struct HitInfo;

class Material {
    Material() = delete;
    virtual ~Material() = delete;

    virtual bool scatter(
            const Ray& r_in, const HitInfo& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
};


#endif //SDL_RAYTRACING_MATERIAL_H
