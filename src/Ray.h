//
// Created by ozgur on 11/02/2024.
//

#ifndef SDL_RAYTRACING_RAY_H
#define SDL_RAYTRACING_RAY_H

#include <GLM/glm/glm.hpp>

class Ray
{
public:
    Ray(const glm::vec2 point1, const glm::vec2 point2);

    [[nodiscard]] inline glm::vec2 getPoint1() const { return point1; }
    [[nodiscard]] inline glm::vec2 getPoint2() const { return point2; }

private:

    glm::vec2 point1;
    glm::vec2 point2;
    glm::vec2 pointsDiff;
};


#endif //SDL_RAYTRACING_RAY_H
