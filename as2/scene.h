/*
 * scene.h
 *
 *  Created on: Oct 4, 2013
 *      Author: Owner
 */
#include "defs.h"

#ifndef SCENE_H_
#define SCENE_H_

class Scene {
public:
    Scene();
    Scene(int x, int y, Point eyepos);

	Point eyePos;  //Camera position
	Point LL, LR, UR, UL;  //Corners of the image plane
	int sizeX, sizeY;  //Output size in pixels
};



#endif /* SCENE_H_ */
