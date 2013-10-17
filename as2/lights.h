/*
 * lights.h
 *
 *  Created on: Oct 16, 2013
 *      Author: Owner
 */
#include "defs.h"

#ifndef LIGHTS_H_
#define LIGHTS_H_

struct Light {

	Light();
	Light(tDVector direction, float intensity);

	tDVector getLightVector(Point p);

	tDVector kd, ks, ka;
	float sp;
};

struct DLight : Light {
	DLight();
	DLight(tDVector direction, float intensity);
};

struct PLight : Light {
	PLight();
	PLight(tDVector direction, float intensity);

	tDVector getLightVector(Point p);
};



#endif /* LIGHTS_H_ */
