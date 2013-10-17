/*
 * polygon.cpp
 *
 *  Created on: Oct 10, 2013
 *      Author: Owner
 */

#include "polygon.h"

Ray::Ray() {
	Point temp = {0.0, 0.0, 0.0};
	origin = temp;
	direction = temp - temp;
}

Ray::Ray(Point a, Point b) {
	origin = a;
	direction = normalize(b - a);
}

bool Primitive::intersects(const Ray &ray, float &closestT) {
	return false;
}

tDVector Primitive::getNormalAt(const Point &p) {
	tDVector temp = {0.0, 0.0, 0.0};
	return temp;
}

Sphere::Sphere() {
	Point temp = {0.0, 0.0, 0.0};
	center = temp;
	radius = 1;
	color.assign(0.0, 0.0, 0.0);
}

Sphere::Sphere(Point c, float r, tDVector colors) {
	center = c;
	radius = r;
	color = colors;
}

bool Sphere::intersects(const Ray &ray, float &closestT) {
	float a, b, c;
	tDVector rayToSphere = ray.origin - center;
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, rayToSphere);
	c = dot(rayToSphere, rayToSphere) - radius * radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {  // ray misses the sphere
		return false;
	}

	discriminant = sqrtf(discriminant);
	float t0 = (-b - discriminant) / (2 * a);
	float t1 = (-b + discriminant) / (2 * a);
	if (t0 > t1) {
		float temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t1 < 0) { // behind the camera
		return false;
	}

	if (t0 > closestT) {
		return false;
	}
	closestT = t0;
	return true;
}

tDVector Sphere::getNormalAt(const Point &p) {
	return (p - center) * 2;
}

tDVector Sphere::getUNormalAt(const Point &p) {
	return (p - center) / radius;
}
