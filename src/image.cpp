#include <iostream>
#include "image.h"
#include "lodepng.h"

using namespace glm;
using namespace std;

Image::Image(unsigned int in_nbPixelsX, unsigned int in_nbPixelsY) {
    nbPixelsX = in_nbPixelsX;
    nbPixelsY = in_nbPixelsY;
    data.resize(4*nbPixelsX*nbPixelsY);
    for(unsigned int i=0; i<nbPixelsX*nbPixelsY; i++) {
        data[4*i + 0] = 0;
        data[4*i + 1] = 0;
        data[4*i + 2] = 0;
        data[4*i + 3] = 255;
    }
}

Image::Image(string filename) {
    unsigned error = lodepng::decode(data, nbPixelsX, nbPixelsY, filename.c_str());
    if(error) {
        std::cout << "Error loading image: " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}

dvec3 Image::get(unsigned int x, unsigned int y) {
    if(x >= nbPixelsX || y >= nbPixelsY) {cout << "Image::get: Out of range." << endl;}
    return dvec3(data[ 4*(nbPixelsX*(nbPixelsY-y-1) + x) + 0 ],
                 data[ 4*(nbPixelsX*(nbPixelsY-y-1) + x) + 1 ],
                 data[ 4*(nbPixelsX*(nbPixelsY-y-1) + x) + 2 ]) / 255.;
}

void Image::set(unsigned int x, unsigned int y, dvec3 color) {
    if(x >= nbPixelsX || y >= nbPixelsY) {cout << "Image::set: Out of range." << endl;}
    data[ 4*(nbPixelsX*(nbPixelsY-y-1) + x) + 0 ] = (unsigned char)(255.*clamp(color.r, 0.0, 1.0));
    data[ 4*(nbPixelsX*(nbPixelsY-y-1) + x) + 1 ] = (unsigned char)(255.*clamp(color.g, 0.0, 1.0));
    data[ 4*(nbPixelsX*(nbPixelsY-y-1) + x) + 2 ] = (unsigned char)(255.*clamp(color.b, 0.0, 1.0));
    data[ 4*(nbPixelsX*(nbPixelsY-y-1) + x) + 3 ] = 255;
}

void Image::saveToFile(string filename) {
    unsigned error = lodepng::encode(filename.c_str(), data, nbPixelsX, nbPixelsY);
    if(error) {
        std::cout << "Error saving image: " << error << ": "<< lodepng_error_text(error) << std::endl;
    }
}
