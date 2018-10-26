#pragma once
#include "main.h"

class Light
{
public:
	glm::vec3 color; // la couleur inclus l'intensit� de la lumi�re
    bool castsShadows = true;
    
	// retourne la direction (vecteur unitaire) de p vers la lumi�re.
    virtual glm::vec3 normalizedVectorToLight(glm::vec3 p) = 0;
    
	// retourne le facteur multiplicatif d'att�nuation, caus� par e.g. la distance de p � la lumi�re.
    virtual decimal attenuationFactor(glm::vec3 p) = 0;

	// retourne la distance entre p et la lumi�re.
    virtual decimal distanceToLight(glm::vec3 p) = 0;
};

class PointLight : public Light
{
public:
    glm::vec3 position;
    
    PointLight() {}
    glm::vec3 normalizedVectorToLight(glm::vec3 p);
    decimal attenuationFactor(glm::vec3 p);
    decimal distanceToLight(glm::vec3 p);
};

class DirectionalLight : public Light
{
public:
    glm::vec3 direction;
    
    DirectionalLight() {}
    glm::vec3 normalizedVectorToLight(glm::vec3 p);
    decimal attenuationFactor(glm::vec3 p);
    decimal distanceToLight(glm::vec3 p);
};

class SpotLight : public Light
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    decimal maxAngle, falloffExponent;
    
    SpotLight() {}
    glm::vec3 normalizedVectorToLight(glm::vec3 p);
    decimal attenuationFactor(glm::vec3 p);
    decimal distanceToLight(glm::vec3 p);
};





