/*
 * sampler.h
 *
 *  Created on: Oct 4, 2013
 *      Author: Owner
 */
#include "defs.h"
#include <vector>
#include "polygon.h"

#ifndef SAMPLER_H_
#define SAMPLER_H_

struct Sample {
	Sample();
	Sample(float a, float b);
	float x, y;

	Point wPoint;
	Ray ray;
	float closestT;
	Primitive closestS;
};

class Sampler {
public:
	Sampler();
	Sampler(float width, float height, float fov);

	/** Gets the next pixel (x,y) and gives it in world space (wx, wy, wz).
	 *  Also gets the ray starting from the lookFrom position and passing
	 *  through that pixel. */
	bool getSample(Sample *sample, Point lookFrom);

	bool getSample(Sample *sample, Point lookFrom, Point lookAt, tDVector up);

	/** Takes an (x,y) point in raster space and converts to world space.
	 *   Should be used to find the world coordinates for a ray shot
	 *   through that pixel. */
	Point rasterToWorld(float x, float y, Point lookFrom);

	void rasterToWorld(Sample *sample, Point lookFrom, Point lookAt, tDVector up);

	float imgRatio; // Width/Height if width > height, reversed otherwise
	float imgHeight, imgWidth, fovV, fovH;

private:
	bool widthBigger;
};

class Film {
public:
	Film();
	Film(int x, int y);

	void commit(Sample &sample, tDVector &color);
	bool writeImage(const char *outfile);
	int scaleFloat(float x);
	tDVector* getPixel(int x, int y);

	std::vector<tDVector> *colors;
	int height, width;
};


#endif /* SAMPLER_H_ */
