#include <fstream>
#include <iostream>
#include <random>

#include "scene.h"
#include "sceneLoader.h"
#include "material.h"
#include "glm/gtc/random.hpp"

using namespace glm;
using namespace std;

Scene::Scene(string sceneFilename) :
    supersampleLevel(1), outputImage(0, 0)
{
    SceneLoader sceneLoader(*this, sceneFilename);
}

void Scene::render()
{
    // pre-calcule les matrices de transformation inverses de chaque objet
    for(Geometry* geo : geometries) {
        geo->inverseTransform = inverse(geo->transform);
    }

    decimal imageHalfWidth = cam.imageDist * tan(cam.fov * PI/360);
    decimal imageHalfHeight = imageHalfWidth * outputImage.getNbPixelsY() / outputImage.getNbPixelsX();

    decimal subPixels = supersampleLevel * supersampleLevel;
    decimal subPixelSize = 1. / supersampleLevel;

    default_random_engine gen;
    uniform_real_distribution<decimal> dist(0, 1);

    // Pour chaque pixel, on détermine le centre du pixel puis on lance un rayon à travers le centre.
    for(unsigned int i = 0; i < outputImage.getNbPixelsX(); i++) {
        for(unsigned int j = 0; j < outputImage.getNbPixelsY(); j++) {
            dvec3 color = dvec3(0);

            dvec3 imageCenter = cam.eye + cam.imageDist * cam.lookAt -
                    (imageHalfWidth * cam.right + imageHalfHeight * cam.up);
            for (unsigned int k = 0; k < supersampleLevel; k++) {
                for (unsigned int l = 0; l < supersampleLevel; l++) {
                    dvec3 pixelCenter = imageCenter +
                            (i + (k + (jittered ? dist(gen) : .5)) * subPixelSize) / outputImage.getNbPixelsX() * 2 * imageHalfWidth * cam.right +
                            (j + (l + (jittered ? dist(gen) : .5)) * subPixelSize) / outputImage.getNbPixelsY() * 2 * imageHalfHeight * cam.up;

                    dvec3 subPixelcolor = getIntersectionColor(Ray(cam.eye, normalize(pixelCenter - cam.eye), 0));
                    color += subPixelcolor;
                }
            }

            outputImage.set(i, j, color / subPixels);
        }

        // Output percentage of completion
        if(i % 10 == 0)
            cout << 100.f*float(i)/(outputImage.getNbPixelsX()-1) << "%" << endl;
    }
}

void Scene::saveToFile(string filename)
{
    outputImage.saveToFile(filename);
}

decimal Scene::getClosestIntersection(Ray ray, Intersection& closestIntersection) {
    Intersection tempInter;
    decimal minT = INFINITY;
    for(Geometry* geo : geometries) {
        Ray modelRay(ray.origin, ray.direction, ray.recursionLevel);
        modelRay.origin = dvec3(geo->inverseTransform * dvec4(ray.origin, 1));
        modelRay.direction = normalize(dvec3(geo->inverseTransform * dvec4(ray.direction, 0)));

        if(geo->closestIntersection(modelRay, tempInter)) {
            tempInter.incidentRay = ray;
            tempInter.position = dvec3(geo->transform * dvec4(tempInter.position, 1));
            tempInter.normal = normalize(dvec3(transpose(geo->inverseTransform) * dvec4(tempInter.normal, 0)));

            decimal dist = distance(tempInter.position, ray.origin);
            if(dist < minT) {
                minT = dist;
                closestIntersection = tempInter;
            }
        }
    }
    return minT;
}

dvec3 Scene::getIntersectionColor(Ray ray)
{
    // intersect scene
    Intersection closestIntersection;
    decimal minT = getClosestIntersection(ray, closestIntersection);

    // compute material color
    if(minT < INFINITY) {
        return closestIntersection.material->shade(closestIntersection, *this);
    } else {
        return backgroundColor;
    }
}
