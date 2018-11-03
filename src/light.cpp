#include "light.h"
#include <stdio.h>

using namespace glm;
using namespace std;

dvec3 PointLight::normalizedVectorToLight(dvec3 p) {
    return normalize(position - p);
}

decimal PointLight::attenuationFactor(dvec3 p) {
    decimal dist = distanceToLight(p);
    assert(dist * dist > 0);
    return 1 / (dist * dist);
}

decimal PointLight::distanceToLight(dvec3 p) {
    return distance(position, p);
}

dvec3 DirectionalLight::normalizedVectorToLight(dvec3 p) {
    return normalize(-direction);
}

decimal DirectionalLight::attenuationFactor(dvec3 p) {
    return 1;
}

decimal DirectionalLight::distanceToLight(dvec3 p) {
    return INFINITY;
}

dvec3 SpotLight::normalizedVectorToLight(dvec3 p) {
    return normalize(position - p);
}

decimal SpotLight::attenuationFactor(dvec3 p) {
    decimal angle = glm::acos(dot(-normalizedVectorToLight(p), normalize(direction)));
    if (angle > maxAngle)
        return 0;

    decimal dist = distanceToLight(p);
    assert(dist * dist > 0);

    return 1 / (dist * dist) * glm::pow(glm::cos(angle/maxAngle * .5 * PI), falloffExponent);
}

decimal SpotLight::distanceToLight(dvec3 p) {
    return distance(position, p);
}
