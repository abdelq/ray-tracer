#include "main.h"
#include "texture.h"
#include <fstream>
#include <iostream>

using namespace glm;
using namespace std;

vec3 TextureCheckerboard::getColor(vec2 uv)
{
    uv = floor(uv * vec2(nbSquaresX, nbSquaresY));
    return (int(uv.x+uv.y) % 2) == 0 ? color1 : color2;
}


vec3 TextureImageFile::getColor(vec2 uv)
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
	return vec3(0);
}
