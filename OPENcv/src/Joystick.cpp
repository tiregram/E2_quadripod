/*
 * Joystick.cpp
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#include "Joystick.h"

Joystick::Joystick(int* x,int* y,int size,int* maxX,int* maxY,int* minX ,int* minY) {
	this->x = x;
	this->y = y;
	this->size =size;
	this->maxX = maxX;
	this->maxY = maxY;
	this->minX = minX;
	this->minY = minY;

}

Joystick::~Joystick() {


}

void Joystick::draw(cv::Mat& img){


}
void Joystick::addActionAndDetect(std::vector<std::pair<Detect,Action>>){}

