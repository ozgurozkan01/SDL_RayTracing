//
// Created by ozgur on 18/02/2024.
//

#ifndef SDL_RAYTRACING_RAY_H
#define SDL_RAYTRACING_RAY_H

#include "Vector3.h"

class Ray {
public:
    Ray() = default;
    Ray(const Vector3& _origin, const Vector3& _direction);

    [[nodiscard]] Vector3 getOrigin() const;
    [[nodiscard]] Vector3 getDirection() const;
    [[nodiscard]] Vector3 at(float t) const;
private:
    Vector3 origin;
    Vector3 direction;
};


#endif //SDL_RAYTRACING_RAY_H
