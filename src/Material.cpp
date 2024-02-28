//
// Created by ozgur on 25/02/2024.
//

#include "Material.h"
#include "Hittable.h"
#include "Sphere.h"

Lambertian::Lambertian(const Vector3 &color) : albedo(color)
{}

bool Lambertian::scatter(const Ray &r_in, const HitInfo &hitInfo, Vector3 &attenuation, Ray &scatteredRay) const
{
    Vector3 scatterDirection = hitInfo.normal + randomUnitVector();

    if (isDirectionNearZero(scatterDirection))
    {
        // If direction is nearly zero, then set the direction again
    }

    scatteredRay = Ray(hitInfo.p, scatterDirection);
    attenuation = albedo;
    return true;
}

Metal::Metal(const Vector3 &color, double fuzz) : albedo(color), fuzz(fuzz < 1 ? fuzz : 1)
{}

bool Metal::scatter(const Ray &r_in, const HitInfo &hitInfo, Vector3 &attenuation, Ray &scatteredRay) const
{
    Vector3 reflected = reflect(normalize(r_in.getDirection()), hitInfo.normal);
    scatteredRay = Ray(hitInfo.p, reflected + (float)fuzz * randomUnitVector());
    attenuation = albedo;
    return dot(scatteredRay.getDirection(), hitInfo.normal) > 0;
}

Dielectric::Dielectric(double refractionIndex) : refractionIndex(refractionIndex)
{}

bool Dielectric::scatter(const Ray &r_in, const HitInfo &hitInfo, Vector3 &attenuation, Ray &scatteredRay) const
{

    attenuation = Vector3(1.0, 1.0, 1.0);
    double refractionRatio = hitInfo.frontFace ? (1.0 / refractionIndex) : refractionIndex;
    Vector3 unitDirection = normalize(r_in.getDirection());

    double cosTheta = fmin(dot(-unitDirection, hitInfo.normal), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    Vector3 direction;

    if (cannotRefract || reflectance(cosTheta, refractionRatio) > (rand() / (RAND_MAX + 1.0)))
        direction = reflect(unitDirection, hitInfo.normal);
    else
        direction = refract(unitDirection, hitInfo.normal, refractionRatio);
    scatteredRay = Ray(hitInfo.p, direction);
    return true;
}
