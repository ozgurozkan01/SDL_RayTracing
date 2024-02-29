//
// Created by ozgur on 19/02/2024.
//

#ifndef SDL_RAYTRACING_HITTABLECOLLECTION_H
#define SDL_RAYTRACING_HITTABLECOLLECTION_H

#include "Hittable.h"
#include <vector>
#include <memory>


class HittableCollection : public Hittable{
public:
    HittableCollection();
    explicit HittableCollection(std::shared_ptr<Hittable> object);
    void clear();
    void add(std::shared_ptr<Hittable> object);
    bool isHit(const Ray& r, double ray_tmin, double ray_tmax, HitInfo& rec) const override;
private:
    std::vector<std::shared_ptr<Hittable>> hittables;

};


#endif //SDL_RAYTRACING_HITTABLECOLLECTION_H
