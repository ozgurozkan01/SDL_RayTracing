//
// Created by ozgur on 25/02/2024.
//

#ifndef SDL_RAYTRACING_MATERIAL_H
#define SDL_RAYTRACING_MATERIAL_H

#include "Ray.h"

struct HitInfo;

class Material {
public:
    virtual bool scatter(
            const Ray& r_in, const HitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const = 0;
};

class Lambertian : public Material
{
public:
    explicit Lambertian(const glm::vec3& color);
    bool scatter(const Ray& r_in, const HitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const override;
private:
    glm::vec3 albedo;
};


class Metal : public Material
{
public:
    explicit Metal(const glm::vec3& color, double fuzz);
    bool scatter(const Ray& r_in, const HitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const override;
private:
    glm::vec3 albedo;
    double fuzz;
};

#endif //SDL_RAYTRACING_MATERIAL_H
