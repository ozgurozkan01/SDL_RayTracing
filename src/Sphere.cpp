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