#pragma once
#include "main.h"
#include "basicStructures.h"
#include "texture.h"
#include "light.h"

class Material
{
public:
    std::string name;
    
    Material() : name("") {}
	// m�thode principale des mat�riaux, retourne la couleur calcul�e pour une intersection donn�e en utilisant les informations de la scene (e.g. les lumi�res).
    virtual glm::vec3 shade(Intersection inter, Scene& scene) = 0;
};

// retourne une couleur constante sans se pr�occuper de l'�clairage r�el.
class MaterialUniform : public Material
{
public:
    glm::vec3 color;
    
    MaterialUniform() :
        color(glm::vec3(0)) {}
    glm::vec3 shade(Intersection inter, Scene& scene);
};


// mat�riau Lambertien avec albedo diffus constant.
class MaterialLambert : public Material
{
public:
    glm::vec3 albedo;
    
    MaterialLambert() :
        albedo(glm::vec3(0)) {}
    glm::vec3 shade(Intersection inter, Scene& scene);
};


// mat�riau Lambertien avec albedo diffus pris d'une texture.
class MaterialLambertTextured : public Material
{
public:
    Texture* albedoTexture;
    
    MaterialLambertTextured(Texture* tex) :
        albedoTexture(tex) {}
    glm::vec3 shade(Intersection inter, Scene& scene);
};


// Lambertien + BlinnPhong sp�culaire + ambiant
class MaterialPhong : public Material
{
public:
    glm::vec3 diffuseAlbedo, specularAlbedo, ambientColor;
	decimal shininess;
    
    MaterialPhong() :
        diffuseAlbedo(glm::vec3(0)), specularAlbedo(glm::vec3(0)), ambientColor(glm::vec3(0)), shininess(0) {}
    glm::vec3 shade(Intersection inter, Scene& scene);
};


// %r�flection + %ambiant
class MaterialReflective : public Material
{
public:
    glm::vec3 ambientColor;
    decimal reflectiveness; // dans [0,1], portion de la lumi�re r�fl�chie.

    MaterialReflective() :
        ambientColor(glm::vec3(0)), reflectiveness(0) {}
    glm::vec3 shade(Intersection inter, Scene& scene);
};


// %r�fraction + %ambiant
class MaterialRefractive : public Material
{
public:
    glm::vec3 ambientColor;
    decimal refractiveness; // dans [0,1], portion de la lumi�re r�fract�e.
    decimal refractiveIndex;

    MaterialRefractive() :
        ambientColor(glm::vec3(0)), refractiveness(0), refractiveIndex(1) {}
    glm::vec3 shade(Intersection inter, Scene& scene);
};