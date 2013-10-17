/*
 * rayTrace.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Owner
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include "scene.h"
#include "sampler.h"
#include "defs.h"
#include <iostream>
#include "polygon.h"

int main(int argc, char *argv[]) {
	/* To be set by command arguments */
	int width, height;
	width = 100;
	height = 100;
	Point lookFrom = {0.0, 0.0, 0.0};
	Point lookAt = {0.0, 0.0, -1.0};
	tDVector upVec = {0.0, 1.0, 0.0};
	float fov = M_PI/2; //should be in radians

	tDVector blank = {0.0, 0.0, 0.0};
	std::vector<Primitive> shapes;
	Point p = {0.0, 0.0, -2.0};
	tDVector color = {1.0, 0.0, 0.0};
	shapes.push_back(Sphere(p, 1, color));

	Scene scene(width, height, lookFrom);
	Sampler sampler(width, height, fov);
	Film film(width, height);

	Sample *s = new Sample(-1, 0);
	while (sampler.getSample(s, lookFrom, lookAt, upVec)) {
		for (int i = 0; i < (int)shapes.size(); i++) {
			//Sphere *sphere = dynamic_cast<Sphere*>(&shapes.at(i));
			if (shapes.at(i).intersects(s->ray, s->closestT)) {
					blank = shapes.at(i).color;
					s->closestS = shapes.at(i);
			}
		}
		film.commit(*s, blank);
		blank.assign(0.0, 0.0, 0.0);
	}

	free(s);
	char* outf = argv[1];
	if (!film.writeImage(outf)) {
		std::cerr << "Error writing image.\n";
		return 1;
	}
	std::cout << "All is well.\n";
	return 0;
}


