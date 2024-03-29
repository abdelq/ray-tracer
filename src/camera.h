#pragma once
#include "main.h"

class Camera
{
public:
    glm::dvec3 eye;
    glm::dvec3 lookAt;
    glm::dvec3 up;
    glm::dvec3 right;
    decimal fov; // angle de vue total horizontal, en radians
    decimal imageDist; // distance entre l'oeil et le plan image

    Camera() {}
};
