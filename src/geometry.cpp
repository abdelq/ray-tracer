#include "geometry.h"
#include "basicStructures.h"

using namespace glm;
using namespace std;

bool solvedQuadratic(const decimal &a, const decimal &b, const decimal &c,
                     decimal &x0, decimal &x1)
{
    decimal disc = b*b - 4*a*c; // Discriminant
    if (disc < 0)
        return false;

    if (disc == 0.) {
        x0 = x1 = -.5 * b / a;
    } else {
        x0 = -.5 * (b + sqrt(disc)) / a;
        x1 = -.5 * (b - sqrt(disc)) / a;
    }

    return x0 >= 0 || x1 >= 0; // Cas recherchés
}

bool Sphere::closestIntersection(Ray ray, Intersection &inter)
{
    decimal a = dot(ray.direction, ray.direction),
            b = 2 * dot(ray.origin, ray.direction),
            c = dot(ray.origin, ray.origin) - 1;

    decimal t0, t1;
    if (!solvedQuadratic(a, b, c, t0, t1))
        return false;

    inter.position = ray.origin + (t1 < 0 || t0 < t1 ? t0 : t1) * ray.direction;
    inter.normal = normalize(inter.position);
    inter.uv = .5 + .5 * dvec2(atan2(inter.normal.x, inter.normal.z) / PI,
                               inter.normal.y);
    inter.material = material;

    return true;
}

bool Plane::closestIntersection(Ray ray, Intersection &inter)
{
    if (ray.direction.y == 0.)
        return false;

    decimal t = -ray.origin.y / ray.direction.y;
    if (t < 0)
        return false;

    inter.position = ray.origin + t * ray.direction;
    inter.normal = dvec3(0, ray.direction.y > 0 ? -1 : 1, 0);
    inter.uv = dvec2(mod<decimal>(inter.position.x, 1),
                     mod<decimal>(-inter.position.z, 1));
    inter.material = material;

    return true;
}

bool Cube::closestIntersection(Ray ray, Intersection &inter)
{
    dvec3 invDir = 1. / ray.direction;
    dvec3 bounds = dvec3(invDir.x < 0 ? 1 : -1,
                         invDir.y < 0 ? 1 : -1,
                         invDir.z < 0 ? 1 : -1);

    dvec3 tNear = (bounds - ray.origin) * invDir,
          tFar = (-bounds - ray.origin) * invDir;
    if (tNear.x > tFar.y || tFar.x < tNear.y)
        return false;

    decimal t0 = tNear.y > tNear.x ? tNear.y : tNear.x,
            t1 = tFar.y < tFar.x ? tFar.y : tFar.x;
    if (t0 > tFar.z || t1 < tNear.z)
        return false;

    t0 = tNear.z > t0 ? tNear.z : t0;
    t1 = tFar.z < t1 ? tFar.z : t1;
    if (t0 < 0 && t1 < 0)
        return false;

    inter.position = ray.origin + (t0 < 0 ? t1 : t0) * ray.direction;
    inter.normal = normalize(dvec3(abs(abs(inter.position.x) - 1.) < EPSILON ? inter.position.x : 0,
                                   abs(abs(inter.position.y) - 1.) < EPSILON ? inter.position.y : 0,
                                   abs(abs(inter.position.z) - 1.) < EPSILON ? inter.position.z : 0));
    if (abs(abs(inter.normal.x) - 1.) < EPSILON)
        inter.uv = .5 * dvec2(mod<decimal>(inter.position.y, 1), mod<decimal>(-inter.position.z, 1));
    else if (abs(abs(inter.normal.y) - 1.) < EPSILON)
        inter.uv = .5 * dvec2(mod<decimal>(inter.position.x, 1), mod<decimal>(-inter.position.z, 1));
    else
        inter.uv = .5 * dvec2(mod<decimal>(inter.position.x, 1), mod<decimal>(-inter.position.y, 1));
    /*inter.uv = .5 * dvec2(mod<decimal>(abs(inter.normal.x) == 1. ? inter.position.y : inter.position.x, 1),
                          mod<decimal>(abs(inter.normal.y) == 1. ? inter.position.z : inter.position.y, 1));*/
    inter.material = material;

    return true;
}

bool Cylinder::closestIntersection(Ray ray, Intersection &inter)
{
    decimal a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z,
            b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z),
            c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;

    decimal t0, t1;
    if (!solvedQuadratic(a, b, c, t0, t1))
        return false;
    if (t0 > t1)
        swap(t0, t1);

    decimal y0 = ray.origin.y + t0 * ray.direction.y,
            y1 = ray.origin.y + t1 * ray.direction.y;
    if ((y0 < -1 && y1 < -1) || (y0 > 1 && y1 > 1))
        return false;

    if (y0 < -1 || y0 > 1) { // Cap
        t0 = (sign(y0) - (ray.origin.y/* - 1*/)) / ray.direction.y;
        inter.position = ray.origin + t0 * ray.direction;
        inter.normal = dvec3(0, sign(y0), 0);
        inter.uv = dvec2(glm::sqrt(inter.position.x * inter.position.x + inter.position.z * inter.position.z),
                         glm::atan(inter.position.z / inter.position.x));
        /*inter.uv = .5 + .5 * dvec2(normalize(inter.position).x,
                                   normalize(inter.position).z);*/
        /*inter.uv = .5 * dvec2(1 + inter.position.x,
                              1 + inter.position.z);*/
        /*inter.uv = dvec2(inter.position.x * glm::sqrt(1 - .5 * inter.position.z * inter.position.z),
                         inter.position.z * glm::sqrt(1 - .5 * inter.position.x * inter.position.x));*/
    } else { // Side
        if (t0 < 0)
            return false;

        inter.position = ray.origin + t0 * ray.direction;
        inter.normal = normalize(dvec3(inter.position.x, 0, inter.position.z));
        inter.uv = .5 * dvec2(atan2(inter.position.x, inter.position.z) / PI,
                              inter.position.y + 1);
    }

    inter.material = material;

    return true;
}

bool Cone::closestIntersection(Ray ray, Intersection &inter)
{
    dvec3 orig = ray.origin, dir = ray.direction;
    decimal a = dir.x * dir.x - .25 * dir.y * dir.y + dir.z * dir.z,
            b = 2 * (orig.x * dir.x - .25 * (orig.y-1) * dir.y + orig.z * dir.z),
            c = orig.x * orig.x - .25 * (orig.y-1) * (orig.y-1) + orig.z * orig.z;

    decimal t0, t1;
    if (!solvedQuadratic(a, b, c, t0, t1))
        return false;
    if (t0 > t1)
        swap(t0, t1);

    decimal y0 = ray.origin.y + t0 * ray.direction.y,
            y1 = ray.origin.y + t1 * ray.direction.y;
    if (y0 > 1 || (y0 < -1 && y1 < -1))
        return false;

    if (y0 < -1) { // Cap
        t0 = (-1 - (ray.origin.y/* - 1*/)) / ray.direction.y;
        inter.position = ray.origin + t0 * ray.direction;
        if (dot(inter.position - dvec3(0, -1, 0), inter.position - dvec3(0, -1, 0)) > 1)
            return false;
        inter.normal = dvec3(0, -1, 0);
        inter.uv = dvec2(glm::sqrt(inter.position.x * inter.position.x + inter.position.z * inter.position.z),
                         glm::atan(inter.position.z / inter.position.x));
    } else { // Side
        if (t0 < 0)
            return false;

        inter.position = ray.origin + t0 * ray.direction;
        inter.normal = normalize(dvec3(2 * inter.position.x,
                                       -.5 * (inter.position.y - 1),
                                       2 * inter.position.z));
        inter.uv = .5 * dvec2(atan2(inter.position.x, inter.position.z) / PI,
                              inter.position.y + 1);
    }

    inter.material = material;

    return true;
}
