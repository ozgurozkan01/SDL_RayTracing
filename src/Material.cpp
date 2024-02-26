//
// Created by ozgur on 25/02/2024.
//

#include "Material.h"
#include "Hittable.h"
#include "Sphere.h"

Lambertian::Lambertian(const glm::vec3 &color) : albedo(color)
{}

bool Lambertian::scatter(const Ray &r_in, const HitInfo &hitInfo, glm::vec3 &attenuation, Ray &scatteredRay) const
{
    glm::vec3 scatterDirection = hitInfo.normal + Sphere::randomUnitVector();

    if (Sphere::isDirectionNearZero(scatterDirection))
    {
        // If direction is nearly zero, then set the direction again
        scatterDirection = hitInfo.normal;
    }

    scatteredRay = Ray(hitInfo.p, scatterDirection);
    attenuation = albedo;
    return true;
}

Metal::Metal(const glm::vec3 &color, double fuzz) : albedo(color), fuzz(fuzz < 1 ? fuzz : 1)
{}

bool Metal::scatter(const Ray &r_in, const HitInfo &hitInfo, glm::vec3 &attenuation, Ray &scatteredRay) const
{
    glm::vec3 reflected = Ray::reflect(glm::normalize(r_in.getDirection()), hitInfo.normal);
    scatteredRay = Ray(hitInfo.p, reflected + (float)fuzz * Sphere::randomUnitVector());
    attenuation = albedo;
    return glm::dot(scatteredRay.getDirection(), hitInfo.normal) > 0;
}