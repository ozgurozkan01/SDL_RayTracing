//
// Created by ozgur on 29/02/2024.
//

#ifndef SDL_RAYTRACING_PPM_H
#define SDL_RAYTRACING_PPM_H

#include "fstream"
#include "cstdint"

class PPM {
    int imageWidth;
    int imageHeight;

    const char* fileName = "image.ppm";

    std::ofstream imageFile;
public:
    void init();
    PPM(int _imageWidth, int imageHeight);
    ~PPM();
    void loadImage(int red, int green, int blue, int alpha);
};


#endif //SDL_RAYTRACING_PPM_H
