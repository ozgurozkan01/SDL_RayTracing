#include "Sphere.h"

Sphere::Sphere(glm::vec3 _center, float _radius, Material* material)
        : center(_center), radius(_radius), material(material)
{}

bool Sphere::isHit(const Ray &ray, double ray_tmin, double ray_tmax, HitInfo &hitInfo) const
{
    glm::vec3 oc = ray.getOrigin() - center;
    auto a = glm::dot(ray.getDirection(), ray.getDirection());
    auto halfB = dot(oc, ray.getDirection());
    auto c = glm::dot(oc, oc) - radius*radius;

    auto discriminant = halfB * halfB - a * c;

    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-halfB - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (-halfB + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
            return false;
    }

    hitInfo.t = root;
    hitInfo.p = ray.at((float)hitInfo.t);
    hitInfo.material = material;

    glm::vec3 outwardNormal = (hitInfo.p - center) / radius;
    glm::normalize(outwardNormal);
    hitInfo.setFaceNormal(ray, outwardNormal);

    return true;
}


glm::vec3 Sphere::randomVector()
{
    return {-0.5 + rand() / (RAND_MAX + 1.0),
            -0.5 + rand() / (RAND_MAX + 1.0),
            -0.5 + rand() / (RAND_MAX + 1.0)};
}

glm::vec3 Sphere::randomVector(double min, double max)
{
    return {min + (max-min)*(-0.5 + rand() / (RAND_MAX + 1.0)),
            min + (max-min)*(-0.5 + rand() / (RAND_MAX + 1.0)),
            min + (max-min)*(-0.5 + rand() / (RAND_MAX + 1.0))
    };
}

glm::vec3 Sphere::randomPointInUnitSphere()
{
    while (true)
    {
        glm::vec3 pointInSphere = randomVector(-1, 1);

        if (glm::dot(pointInSphere, pointInSphere) < 1.f)
        {
            return pointInSphere;
        }
    }
}

glm::vec3 Sphere::randomUnitVector()
{
    return glm::normalize(randomPointInUnitSphere());
}

glm::vec3 Sphere::randomOnHemisphere(const glm::vec3 &normal)
{
    glm::vec3 onUnitSphere = randomUnitVector();
    // In the same hemisphere as the normal
    if (dot(onUnitSphere, normal) > 0.0) { return onUnitSphere; }
    else { return -onUnitSphere; }
}

bool Sphere::isDirectionNearZero(const glm::vec3 &direction)
{
    double overLimit = 1e-8;
    return (abs(direction.x) < overLimit) && (abs(direction.y) < overLimit) && (abs(direction.z) < overLimit);
}