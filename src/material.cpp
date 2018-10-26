#include "main.h"
#include "material.h"
#include "scene.h"
#include <iostream>

using namespace glm;
using namespace std;

vec3 MaterialUniform::shade(Intersection, Scene&)
{
    return color;
}

vec3 MaterialLambert::shade(Intersection inter, Scene& scene)
{
    // À COMPLÉTER
    return vec3(0);
}

vec3 MaterialLambertTextured::shade(Intersection inter, Scene& scene)
{
    // À COMPLÉTER
    return vec3(0);
}

vec3 MaterialPhong::shade(Intersection inter, Scene& scene)
{
    // À COMPLÉTER
    return vec3(0);
}

vec3 MaterialReflective::shade(Intersection inter, Scene &scene)
{
    // À COMPLÉTER
    return vec3(0);
}

vec3 MaterialRefractive::shade(Intersection inter, Scene &scene)
{
    // À COMPLÉTER
    return vec3(0);
}
