#include "main.h"
#include "material.h"
#include "scene.h"
#include <iostream>

using namespace glm;
using namespace std;

dvec3 MaterialUniform::shade(Intersection, Scene&)
{
    return color;
}

dvec3 MaterialLambert::shade(Intersection inter, Scene& scene)
{
    // À COMPLÉTER
    return dvec3(0);
}

dvec3 MaterialLambertTextured::shade(Intersection inter, Scene& scene)
{
    // À COMPLÉTER
    return dvec3(0);
}

dvec3 MaterialPhong::shade(Intersection inter, Scene& scene)
{
    // À COMPLÉTER
    return dvec3(0);
}

dvec3 MaterialReflective::shade(Intersection inter, Scene &scene)
{
    // À COMPLÉTER
    return dvec3(0);
}

dvec3 MaterialRefractive::shade(Intersection inter, Scene &scene)
{
    // À COMPLÉTER
    return dvec3(0);
}
