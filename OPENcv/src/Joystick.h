/*
 * Joystick.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <vector>
#include "ItemInterface.h"

class Joystick : public ItemInterface {
public:
	Joystick(int *x,int* y,int size,int* maxX,int* maxY,int* minX ,int* minY);
	virtual ~Joystick();
	virtual void draw(cv::Mat& img);
	virtual void addActionAndDetect(std::vector<std::pair<Detect,Action>>);

private:

	int * x;
	int * y;
	int size;
	int * maxX;
	int * maxY;
	int * minX;
	int * minY;

};

#endif /* JOYSTICK_H_ */
