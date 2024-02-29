//
// Created by ozgur on 29/02/2024.
//

#include <iostream>
#include "PPM.h"

PPM::PPM(int _imageWidth, int imageHeight) : imageWidth(_imageWidth), imageHeight(imageHeight)
{
    init();
}

void PPM::init()
{
    imageFile.open(fileName);

    if (imageFile.is_open())
    {
        imageFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    }
}

void PPM::loadImage(int red, int green, int blue, int alpha)
{
    if (imageFile.is_open())
    {
        imageFile << red << " " << green << " " << blue << " " << "\n";
    }
}

PPM::~PPM()
{
    imageFile << 255 << "\n";						//Declare that you want to use ASCII colour values
    imageFile.close();
}
