//
// Created by ozgur on 19/02/2024.
//

#include "HittableCollection.h"

HittableCollection::HittableCollection() = default;

HittableCollection::HittableCollection(std::shared_ptr<Hittable> object)
{
    add(object);
}

void HittableCollection::clear()
{
    hittables.clear();
}

void HittableCollection::add(std::shared_ptr<Hittable> object)
{
    hittables.push_back(object);
}

bool HittableCollection::isHit(const Ray &r, double ray_tmin, double ray_tmax, HitInfo &rec) const {
    HitInfo tempInfo;
    bool hit_anything = false;
    auto closest_so_far = ray_tmax;

    for (const auto& hittable : hittables) {
        if (hittable->isHit(r, ray_tmin, closest_so_far, tempInfo)) {
            hit_anything = true;
            closest_so_far = tempInfo.t;
            rec = tempInfo;
        }
    }

    return hit_anything;}
