#include "light.h"

using namespace glm;
using namespace std;

dvec3 PointLight::normalizedVectorToLight(dvec3 p) {
    // À COMPLÉTER
    return dvec3(0);
}

decimal PointLight::attenuationFactor(dvec3 p) {
    // À COMPLÉTER
    return 0;
}

decimal PointLight::distanceToLight(dvec3 p) {
    // À COMPLÉTER
    return 0;
}

dvec3 DirectionalLight::normalizedVectorToLight(dvec3 p) {
    // À COMPLÉTER
    return dvec3(0);
}


decimal DirectionalLight::attenuationFactor(dvec3 p) {
    // À COMPLÉTER
    return 0;
}

decimal DirectionalLight::distanceToLight(dvec3 p) {
    // À COMPLÉTER
    return 0;
}

dvec3 SpotLight::normalizedVectorToLight(dvec3 p) {
    // À COMPLÉTER
    return dvec3(0);
}

decimal SpotLight::attenuationFactor(dvec3 p) {
    // À COMPLÉTER
    return 0;
}

decimal SpotLight::distanceToLight(dvec3 p) {
    // À COMPLÉTER
    return 0;
}
