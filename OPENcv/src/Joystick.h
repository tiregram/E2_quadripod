/*
 * Joystick.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <vector>

class Joystick : ItemIterface{
public:
	Joystick();
	virtual ~Joystick();

	void draw();

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
