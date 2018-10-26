#include "geometry.h"
#include "basicStructures.h"

using namespace glm;
using namespace std;

bool Sphere::closestIntersection(Ray ray, Intersection& inter)
{
    // À COMPLÉTER
    return false;
}

bool Plane::closestIntersection(Ray ray, Intersection& inter)
{
    vec3 p = ray.origin;
    vec3 d = ray.direction;

    decimal minT = INFINITY, t;
    vec3 tempP;

    if(d.y != 0) {
        t = (0-p.y)/d.y;
        tempP = p + t*d;
        if(t > 0 && t < minT) {
            minT = t;
            inter.normal = vec3(0,1,0);
            if(dot(inter.normal,ray.direction)>0) inter.normal = -inter.normal;
            inter.uv = vec2(mod<decimal>(tempP.x,1), mod<decimal>(-tempP.z,1));
        }
    }
    inter.position = p + minT*d;
    inter.material = material;

    return minT!=INFINITY;
}

bool Cube::closestIntersection(Ray ray, Intersection& inter)
{
    // À COMPLÉTER
    return false;
}

bool Cylinder::closestIntersection(Ray ray, Intersection& inter)
{
    // À COMPLÉTER
    return false;
}

bool Cone::closestIntersection(Ray ray, Intersection& inter)
{
    // À COMPLÉTER
    return false;
}
