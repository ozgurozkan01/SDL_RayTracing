//
// Created by ozgur on 26/02/2024.
//

#ifndef SDL_RAYTRACING_VECTOR3_H
#define SDL_RAYTRACING_VECTOR3_H

#include <cmath>
#include <iostream>

struct Vector3
{
    double coordinates[3];
    Vector3() : coordinates{0,0,0} {}
    Vector3(double x, double y, double z) : coordinates{x,y,z} {}

    [[nodiscard]] double x() const { return coordinates[0]; }
    [[nodiscard]] double y() const { return coordinates[1]; }
    [[nodiscard]] double z() const { return coordinates[2]; }
};


#endif //SDL_RAYTRACING_VECTOR3_H
