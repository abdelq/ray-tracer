#pragma once
#include "main.h"

// forward declarations
class Intersection;
class Ray;
class Material;

class Geometry
{
public:
    Material* material;
    glm::dmat4 transform;
    glm::dmat4 inverseTransform;

    Geometry() :
        material(nullptr), transform(glm::dmat4(1)), inverseTransform(glm::inverse(glm::dmat4(1))) {}
    virtual ~Geometry() {}

    // retourne si oui ou non le rayon intersecte la géométrie.
    // Si il y a intersection, toutes ses informations sont insérées dans inter.
    virtual bool closestIntersection(Ray ray, Intersection& inter) = 0;
};

class Sphere : public Geometry
{
public:
    Sphere() {}
    bool closestIntersection(Ray ray, Intersection& inter);
};

class Plane : public Geometry
{
public:
    Plane() {}
    bool closestIntersection(Ray ray, Intersection& inter);
};

class Cube : public Geometry
{
public:
    Cube() {}
    bool closestIntersection(Ray ray, Intersection& inter);
};

class Cylinder : public Geometry
{
public:
    Cylinder() {}
    bool closestIntersection(Ray ray, Intersection& inter);
};

class Cone : public Geometry
{
public:
    Cone() {}
    bool closestIntersection(Ray ray, Intersection& inter);
};
