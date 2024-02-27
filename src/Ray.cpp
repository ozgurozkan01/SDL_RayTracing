//
// Created by ozgur on 18/02/2024.
//

#include "Ray.h"

Ray::Ray(const Vector3 &_origin, const Vector3 &_direction):
    origin(_origin),
    direction(_direction) {}

Vector3 Ray::getOrigin() const {
    return origin;
}

Vector3 Ray::getDirection() const {
    return direction;
}

Vector3 Ray::at(float t) const {
    return origin + (t * direction);
}

Vector3 Ray::reflect(const Vector3 &v, const Vector3 &n) {
    return v - 2 * dot(v, n) * n;
}
