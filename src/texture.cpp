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
        decimal x = abs(uv.x) * (image.getNbPixelsX()-1),
                y = abs(uv.y) * (image.getNbPixelsY()-1);
        unsigned int xi = unsigned(x), yi = unsigned(y);
        decimal tx = x - xi, ty = y - yi;

        return (image.get(xi, yi)   * (1 - tx) + image.get(xi+1, yi)   * tx) * (1 - ty) +
               (image.get(xi, yi+1) * (1 - tx) + image.get(xi+1, yi+1) * tx) * ty;
    }

    return image.get(unsigned(clamp(mod<decimal>(uv.x, 1) * (image.getNbPixelsX()-1), 0., image.getNbPixelsX()-1.)),
                     unsigned(clamp(mod<decimal>(uv.y, 1) * (image.getNbPixelsY()-1), 0., image.getNbPixelsY()-1.)));
}
