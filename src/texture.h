#pragma once
#include "main.h"
#include "image.h"
#include <string>

class Texture
{
public:
    std::string name;

    Texture() : name() {}

    // retourne la couleur de la texture pour des coordonnées UV données.
    virtual glm::dvec3 getColor(glm::dvec2 uv) = 0;
};

class TextureCheckerboard : public Texture
{
public:
    int nbSquaresX, nbSquaresY;
    glm::dvec3 color1, color2;

    TextureCheckerboard() :
        nbSquaresX(16), nbSquaresY(16), color1(0), color2(1) {}
    glm::dvec3 getColor(glm::dvec2 uv);
};

class TextureImageFile : public Texture
{
public:
    Image image;
    bool bilinear;

    TextureImageFile(std::string filename) : image(filename), bilinear(false) {}
    glm::dvec3 getColor(glm::dvec2 uv);
    unsigned int width() {return image.getNbPixelsX();}
    unsigned int height() {return image.getNbPixelsY();}
};
