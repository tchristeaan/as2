/*
 * sampler.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: Owner
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include "sampler.h"
#include "FreeImage.h"
#include <stdio.h>
#include <iostream>

float INFINITY = std::numeric_limits<float>::infinity();

Sample::Sample() {
	x = 0.0;
	y = 0.0;

	closestT = -INFINITY;
}

Sample::Sample(float a, float b) {
	x = a;
	y = b;
	closestT = -INFINITY;
}

Sampler::Sampler() {
	imgWidth = 100;
	imgHeight = 100;
	fovV = M_PI / 2;
	fovH = M_PI / 2;
	imgRatio = 1;
	widthBigger = true;
}

Sampler::Sampler(float width, float height, float field) {
	imgWidth = width;
	imgHeight = height;
	fovV = field;
	fovH = atan(width/2);
	widthBigger = width > height;
	imgRatio = width / height;
	if (!widthBigger) {
		imgRatio = height / width;
	}
}


bool Sampler::getSample(Sample *sample, Point lookFrom, Point lookAt, tDVector up) {
	sample->x += 1;
	if (sample->x == imgWidth) {
		sample->x = 0;
		sample->y += 1;
	}
	if (sample->y == imgHeight) {
		return false;
	}
	rasterToWorld(sample, lookFrom, lookAt, up);
	return true;
}

Point Sampler::rasterToWorld(float x, float y, Point lookFrom) {
	//Assuming distance of 1 between camera and image plane
    float px = (2 * (x + 0.5) / imgWidth - 1) * tan(fovH / 2);
    float py = (1 - 2 * (y + 0.5) / imgHeight) * tan(fovV / 2);
	if (widthBigger) {
		px *= imgRatio;
	} else {
		py *= imgRatio;
	}
	tDVector t = {px, py, lookFrom.z - 1};
	t = normalize(t);
	Point p = {t.x, t.y, t.z};
	return p;
}

void Sampler::rasterToWorld(Sample *sample, Point lookFrom, Point lookAt, tDVector up) {
	tDVector z = lookFrom - lookAt;
	tDVector xAxis = cross(up, z);
	tDVector yAxis = cross(xAxis, xAxis);
	Ray temp;
	float px = (2 * (sample->x + 0.5)/imgWidth - 1) * tan(fovH/2);
	float py = (2 * (sample->y + 0.5)/imgHeight - 1) * tan(fovV/2);
	tDVector a = xAxis * px + up * py - z;
	temp.direction = normalize(a);
	temp.origin = lookFrom;
	sample->ray = temp;
	sample->wPoint.assign(px, py, lookFrom.z - 1.0);

}

Film::Film() {
	height = 100;
	width = 100;
	colors = new std::vector<tDVector>;
}

Film::Film(int x, int y) {
	height = y;
	width = x;
	colors = new std::vector<tDVector>;
}

void Film::commit(Sample &sample, tDVector &color) {
	colors->push_back(color);
}

int Film::scaleFloat(float x) {
	return ((int) x * 255);
}

tDVector* Film::getPixel(int x, int y) {
	return &(colors->at(y * width + x));
}

bool Film::writeImage(const char *outfile) {
	FreeImage_Initialise();
	FIBITMAP *bitmap = FreeImage_Allocate(width, height, 24);
	RGBQUAD color;
	if (!bitmap) {
		std::cerr << "Failed to allocate space for image.\n";
		return false;
	}
	std::cout << "colors size : " << colors->size() << std::endl;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			tDVector *pixel = getPixel(x, y);
			color.rgbRed = scaleFloat(pixel->x);
			color.rgbGreen = scaleFloat(pixel->y);  //G
			color.rgbBlue = scaleFloat(pixel->z);  //B
			FreeImage_SetPixelColor(bitmap, x, y, &color);
		}
	}
	if (!FreeImage_Save(FIF_PNG, bitmap, outfile, 0)) {
		std::cerr << "Failed to save image to file " << outfile << std::endl;
	}
	FreeImage_DeInitialise();
	return true;
}

