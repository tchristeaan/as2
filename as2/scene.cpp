/*
 * scene.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: Owner
 */

#include "scene.h"

Scene::Scene() {
	sizeX = 100;
	sizeY = 100;

	eyePos.assign(0.0, 0.0, 0.0);
	LL.assign(-1.0, -1.0, -1.0);
	LR.assign(1.0, -1.0, -1.0);
	UL.assign(-1.0, 1.0, -1.0);
	UR.assign(1.0, 1.0, -1.0);
}

Scene::Scene(int x, int y, Point eyepos) {
	sizeX = x;
	sizeY = y;

	eyePos = eyepos;
	LL.assign(-1.0, -1.0, -1.0);
	LR.assign(1.0, -1.0, -1.0);
	UL.assign(-1.0, 1.0, -1.0);
	UR.assign(1.0, 1.0, -1.0);
}



