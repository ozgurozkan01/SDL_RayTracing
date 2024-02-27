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

    Vector3 operator-() const { return Vector3(-coordinates[0], -coordinates[1], -coordinates[2]); }
    double operator[](int index) const { return coordinates[index]; }
    double& operator[](int index) { return coordinates[index]; }

    Vector3& operator+=(const Vector3& vector3)
    {
        coordinates[0] += vector3.coordinates[0];
        coordinates[1] += vector3.coordinates[1];
        coordinates[2] += vector3.coordinates[2];

        return *this;
    }

    Vector3& operator*=(double t)
    {
        coordinates[0] *= t;
        coordinates[1] *= t;
        coordinates[2] *= t;

        return *this;
    }

    Vector3& operator/=(double t)
    {
        return *this *= (1/t);
    }

    double length() const
    {
        return sqrt(dotProduct());
    }

    double dotProduct() const
    {
        return coordinates[0] * coordinates[0] +
                coordinates[1] * coordinates[1] +
                coordinates[2] * coordinates[2];
    }
};

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const Vector3 &v) {
    return out << v.coordinates[0] << ' ' << v.coordinates[1] << ' ' << v.coordinates[2];
}

inline Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.coordinates[0] + v.coordinates[0],
                   u.coordinates[1] + v.coordinates[1],
                   u.coordinates[2] + v.coordinates[2]);
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.coordinates[0] - v.coordinates[0],
                   u.coordinates[1] - v.coordinates[1],
                   u.coordinates[2] - v.coordinates[2]);
}

inline Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.coordinates[0] * v.coordinates[0],
                   u.coordinates[1] * v.coordinates[1],
                   u.coordinates[2] * v.coordinates[2]);
}

inline Vector3 operator*(double t, const Vector3 &v) {
    return Vector3(t*v.coordinates[0],
                   t*v.coordinates[1],
                   t*v.coordinates[2]);
}

inline Vector3 operator*(const Vector3 &v, double t) {
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector3 &u, const Vector3 &v) {
    return u.coordinates[0] * v.coordinates[0]
           + u.coordinates[1] * v.coordinates[1]
           + u.coordinates[2] * v.coordinates[2];
}

inline Vector3 cross(const Vector3 &u, const Vector3 &v) {
    return Vector3(u.coordinates[1] * v.coordinates[2] - u.coordinates[2] * v.coordinates[1],
                u.coordinates[2] * v.coordinates[0] - u.coordinates[0] * v.coordinates[2],
                u.coordinates[0] * v.coordinates[1] - u.coordinates[1] * v.coordinates[0]);
}

inline Vector3 unit_vector(Vector3 v) {
    return v / v.length();
}

#endif //SDL_RAYTRACING_VECTOR3_H
