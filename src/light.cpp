#include "light.h"

using namespace glm;
using namespace std;

vec3 PointLight::normalizedVectorToLight(vec3 p) {
    // À COMPLÉTER
    return vec3(0);
}

decimal PointLight::attenuationFactor(vec3 p) {
    // À COMPLÉTER
    return 0;
}

decimal PointLight::distanceToLight(vec3 p) {
    // À COMPLÉTER
    return 0;
}

vec3 DirectionalLight::normalizedVectorToLight(vec3 p) {
    // À COMPLÉTER
    return vec3(0);
}


decimal DirectionalLight::attenuationFactor(vec3 p) {
    // À COMPLÉTER
    return 0;
}

decimal DirectionalLight::distanceToLight(vec3 p) {
    // À COMPLÉTER
    return 0;
}

vec3 SpotLight::normalizedVectorToLight(vec3 p) {
    // À COMPLÉTER
    return vec3(0);
}

decimal SpotLight::attenuationFactor(vec3 p) {
    // À COMPLÉTER
    return 0;
}

decimal SpotLight::distanceToLight(vec3 p) {
    // À COMPLÉTER
    return 0;
}
