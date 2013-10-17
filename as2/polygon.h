/*
 * polygon.h
 *
 *  Created on: Oct 10, 2013
 *      Author: Owner
 */
#include "defs.h"

#ifndef POLYGON_H_
#define POLYGON_H_

struct Ray {
	Point origin;
	tDVector direction;

	Ray();
	/* A ray from a to b */
	Ray(Point a, Point b);
};

/* Not meant for use */
struct Primitive {
	virtual bool intersects(const Ray &ray, float &closestT);
	virtual tDVector getNormalAt(const Point &p);

	tDVector color;
};

struct Sphere : Primitive {

	Sphere();
	Sphere(Point c, float r, tDVector color);

	bool intersects(const Ray &ray, float &closestT);

	/* Get the normal vector at p */
	tDVector getNormalAt(const Point &p);

	/* Get the unit normal at p */
	tDVector getUNormalAt(const Point &p);

	Point center;
	float radius;
};



#endif /* POLYGON_H_ */
