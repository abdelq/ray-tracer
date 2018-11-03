#pragma once
#include "main.h"

// forward declarations
class Material;
class Scene;

class Ray
{
public:
    glm::dvec3 origin;
    glm::dvec3 direction; // longueur unitaire
    int recursionLevel; // commence à 0, incrémente à chaque rebond.
    bool isInsideGeometry; // utile pour gérer les rayons réfractés au fil des rebonds

    Ray() :
        origin(glm::dvec3(0)), direction(glm::dvec3(0)), recursionLevel(0), isInsideGeometry(false) {}
    Ray(glm::dvec3 origin, glm::dvec3 direction, int recursionLevel) :
        origin(origin), direction(direction), recursionLevel(recursionLevel), isInsideGeometry(false) {}
};

class Intersection
{
public:
    Ray incidentRay;
    glm::dvec3 position;
    glm::dvec3 normal; // longueur unitaire
    glm::dvec2 uv; // dans [0,1]x[0,1]
    Material* material;

    Intersection() :
        incidentRay(Ray()), position(glm::dvec3(0)), normal(glm::dvec3(0)), uv(glm::dvec3(0)), material(nullptr) {}
};
