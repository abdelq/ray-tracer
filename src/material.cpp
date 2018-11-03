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
    Intersection shadowInter;

    dvec3 color = dvec3(0);
    for (auto light : scene.lights) {
        decimal lightDist = scene.getClosestIntersection(Ray(inter.position + decimal(EPSILON) * inter.normal, light->normalizedVectorToLight(inter.position), 0), shadowInter);
        if (!light->castsShadows || lightDist >= light->distanceToLight(inter.position))
            color += light->color * light->attenuationFactor(inter.position) * glm::max(0., dot(light->normalizedVectorToLight(inter.position), inter.normal)) * albedo;
    }
    return color;
}

dvec3 MaterialLambertTextured::shade(Intersection inter, Scene& scene)
{
    Intersection shadowInter;

    dvec3 color = dvec3(0);
    for (auto light : scene.lights) {
        decimal lightDist = scene.getClosestIntersection(Ray(inter.position + decimal(EPSILON) * inter.normal, light->normalizedVectorToLight(inter.position), 0), shadowInter);
        if (!light->castsShadows || lightDist >= light->distanceToLight(inter.position))
            color += light->color * light->attenuationFactor(inter.position) * glm::max(0., dot(light->normalizedVectorToLight(inter.position), inter.normal)) * albedoTexture->getColor(inter.uv);
    }
    return color;
}

dvec3 MaterialPhong::shade(Intersection inter, Scene& scene)
{
    Intersection shadowInter;

    dvec3 diffuse = dvec3(0), specular = dvec3(0), ambient = ambientColor;
    for (auto light : scene.lights) {
        decimal lightDist = scene.getClosestIntersection(Ray(inter.position + decimal(EPSILON) * inter.normal, light->normalizedVectorToLight(inter.position), 0), shadowInter);
        if (!light->castsShadows || lightDist >= light->distanceToLight(inter.position)) {
            diffuse += light->color * light->attenuationFactor(inter.position) * diffuseAlbedo * glm::max(0., dot(light->normalizedVectorToLight(inter.position), inter.normal));
            specular += light->color * light->attenuationFactor(inter.position) * specularAlbedo * glm::pow(glm::max(0., dot(normalize(light->normalizedVectorToLight(inter.position) + normalize(-inter.incidentRay.direction)), inter.normal)), shininess);
        }
    }
    return ambient + diffuse + specular;
}

dvec3 MaterialReflective::shade(Intersection inter, Scene &scene)
{
    if (inter.incidentRay.recursionLevel > scene.maxRecursionLevel)
        return ambientColor;

    return (1 - reflectiveness) * ambientColor +
            reflectiveness * scene.getIntersectionColor(
                Ray(inter.position + decimal(EPSILON) * inter.normal,
                    reflect(inter.incidentRay.direction, inter.normal),
                    inter.incidentRay.recursionLevel + 1));
}

dvec3 MaterialRefractive::shade(Intersection inter, Scene &scene)
{
    if (inter.incidentRay.recursionLevel > scene.maxRecursionLevel)
        return ambientColor;

    // XXX scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
    decimal cosi = clamp(-1., 1., dot(inter.incidentRay.direction, inter.normal));
    decimal eta = 1 / refractiveIndex;
    dvec3 normal = inter.normal;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        eta = refractiveIndex;
        normal = -inter.normal;
    }

    decimal k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0) {
        return (1 - refractiveness) * ambientColor +
                refractiveness * scene.getIntersectionColor(
                    Ray(inter.position + decimal(EPSILON) * normal,
                        reflect(inter.incidentRay.direction, normal),
                        inter.incidentRay.recursionLevel + 1));
    } else {
        return (1 - refractiveness) * ambientColor +
                refractiveness * scene.getIntersectionColor(
                    Ray(inter.position - decimal(EPSILON) * normal,
                        refract(inter.incidentRay.direction, normal, eta),
                        inter.incidentRay.recursionLevel + 1));
    }

    /*decimal eta = inter.incidentRay.isInsideGeometry ? refractiveIndex : 1/refractiveIndex;
    dvec3 normal = inter.incidentRay.isInsideGeometry ? -inter.normal : inter.normal;

    dvec3 refraction = refract(inter.incidentRay.direction, normal, eta);
    decimal cosi = abs(clamp(-1., 1., dot(inter.incidentRay.direction, normal)));
    decimal k = 1 - eta * eta * (1 - cosi * cosi);
    //if (refraction.x < EPSILON && refraction.y < EPSILON && refraction.z < EPSILON) {
    if (k < 0) {
        return (1 - refractiveness) * ambientColor +
                refractiveness * scene.getIntersectionColor(
                    Ray(inter.position - decimal(EPSILON) * normal,
                        reflect(inter.incidentRay.direction, normal),
                        inter.incidentRay.recursionLevel + 1));
    } else {
        inter.incidentRay.isInsideGeometry = !inter.incidentRay.isInsideGeometry;
        return (1 - refractiveness) * ambientColor +
                refractiveness * scene.getIntersectionColor(
                    Ray(inter.position - decimal(EPSILON) * normal,
                        refraction,
                        //eta * inter.incidentRay.direction + (eta * cosi - glm::sqrt(k)) * normal,
                        inter.incidentRay.recursionLevel + 1));
    }*/
}
