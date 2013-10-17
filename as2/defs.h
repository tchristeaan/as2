/*
 * defs.h
 *
 *  Created on: Oct 4, 2013
 *      Author: Owner
 */

#include <math.h>
#ifndef DEFS_H_
#define DEFS_H_

struct tDVector {
	float x, y, z;

	inline void assign(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
};

struct Point {
	float x, y, z;

	inline void assign(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
};

inline tDVector operator + (const tDVector &a, const tDVector &b) {
	tDVector temp = {a.x + b.x, a.y + b.y, a.z + b.z};
	return temp;
}

inline tDVector operator - (const tDVector &a, const tDVector &b) {
	tDVector temp = {a.x - b.x, a.y - b.y, a.z - b.z};
	return temp;
}

inline tDVector operator * (const tDVector &a, float f) {
	tDVector temp = {a.x * f, a.y * f, a.z *f};
	return temp;
}

inline tDVector operator / (const tDVector &a, float f) {
	tDVector temp = {a.x / f, a.y / f, a.z / f};
	return temp;
}

inline tDVector normalize(const tDVector &a) {
	float mag = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	tDVector temp = {a.x / mag, a.y / mag, a.z / mag};
	return temp;
}

inline tDVector operator - (const Point &a, const Point &b) {
	tDVector temp = {a.x - b.x, a.y - b.y, a.z - b.z};
	return temp;
}

inline Point operator + (const Point &p, const tDVector &vec) {
	Point temp = {vec.x + p.x, vec.y + p.y, vec.z + p.z};
	return temp;
}

inline Point operator - (const Point &p, const tDVector &vec) {
	Point temp = {p.x - vec.x, p.y - vec.y, p.z - vec.z};
	return temp;
}

inline float dot(const tDVector &a, const tDVector &b) {
	return a.x * b.x + a.y * b.y + a.z *b.z;
}

inline tDVector cross(const tDVector &a, const tDVector &b) {
	tDVector temp = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
	return temp;
}


#endif /* DEFS_H_ */
