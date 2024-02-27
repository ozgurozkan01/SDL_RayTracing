//
// Created by ozgur on 25/02/2024.
//

#ifndef SDL_RAYTRACING_MATERIAL_H
#define SDL_RAYTRACING_MATERIAL_H

#include "Ray.h"
#include "Vector3.h"

struct HitInfo;

class Material {
public:
    virtual bool scatter(
            const Ray& r_in, const HitInfo& hitInfo, Vector3& attenuation, Ray& scatteredRay) const = 0;
};

class Lambertian : public Material
{
public:
    explicit Lambertian(const Vector3& color);
    bool scatter(const Ray& r_in, const HitInfo& hitInfo, Vector3& attenuation, Ray& scatteredRay) const override;
private:
    Vector3 albedo;
};


class Metal : public Material
{
public:
    explicit Metal(const Vector3& color, double fuzz);
    bool scatter(const Ray& r_in, const HitInfo& hitInfo, Vector3& attenuation, Ray& scatteredRay) const override;
private:
    Vector3 albedo;
    double fuzz;
};

class Dielectric : public Material
{
public:
    explicit Dielectric(double refractionIndex);
    bool scatter(const Ray& r_in, const HitInfo& hitInfo, Vector3& attenuation, Ray& scatteredRay) const override;
private:
    double refractionIndex;
};

#endif //SDL_RAYTRACING_MATERIAL_H
