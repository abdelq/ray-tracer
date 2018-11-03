#include "main.h"
#include "texture.h"
#include <fstream>
#include <iostream>

using namespace glm;
using namespace std;

dvec3 TextureCheckerboard::getColor(dvec2 uv)
{
    uv = floor(uv * dvec2(nbSquaresX, nbSquaresY));
    return (int(uv.x+uv.y) % 2) == 0 ? color1 : color2;
}

dvec3 TextureImageFile::getColor(dvec2 uv)
{
    if (bilinear) {
        // TODO
        // filtrage bilineaire
    }
    else {
        // TODO
        // faire correspondre les coordonnées UV dans [0,1]x[0,1] avec les pixels de l'image [0, image.getNbPixelsX()]x[0, image.getNbPixelsY()].
        // attention de ne pas demander de pixels de l'image qui n'existent pas!
        // on peut obtenir la valeur des pixels de l'image avec image.get(x, y).
    }
    return dvec3(0);
}
