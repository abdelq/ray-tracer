#pragma once
#include "main.h"

class Light
{
public:
    glm::dvec3 color; // la couleur inclus l'intensité de la lumière
    bool castsShadows = true;

    // retourne la direction (vecteur unitaire) de p vers la lumière.
    virtual glm::dvec3 normalizedVectorToLight(glm::dvec3 p) = 0;

    // retourne le facteur multiplicatif d'atténuation, causé par e.g. la distance de p à la lumière.
    virtual decimal attenuationFactor(glm::dvec3 p) = 0;

    // retourne la distance entre p et la lumière.
    virtual decimal distanceToLight(glm::dvec3 p) = 0;
};

class PointLight : public Light
{
public:
    glm::dvec3 position;

    PointLight() {}
    glm::dvec3 normalizedVectorToLight(glm::dvec3 p);
    decimal attenuationFactor(glm::dvec3 p);
    decimal distanceToLight(glm::dvec3 p);
};

class DirectionalLight : public Light
{
public:
    glm::dvec3 direction;

    DirectionalLight() {}
    glm::dvec3 normalizedVectorToLight(glm::dvec3 p);
    decimal attenuationFactor(glm::dvec3 p);
    decimal distanceToLight(glm::dvec3 p);
};

class SpotLight : public Light
{
public:
    glm::dvec3 position;
    glm::dvec3 direction;
    decimal maxAngle, falloffExponent;

    SpotLight() {}
    glm::dvec3 normalizedVectorToLight(glm::dvec3 p);
    decimal attenuationFactor(glm::dvec3 p);
    decimal distanceToLight(glm::dvec3 p);
};
