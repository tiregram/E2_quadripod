/*
 * DetectInterface.cpp
 *
 *  Created on: 18 juin 2015
 *      Author: ruhtra
 */

#include "DetectInterface.h"
#include "Detect.h"
#include <string>
#include <iostream>


DetectInterface::DetectInterface(int x,int y,int size){
	this->x =x;
	this->y =y;
	this->size = size;
	this->time =0;
}

DetectInterface::~DetectInterface() {

}

bool DetectInterface::tryToDetect(cv::Point point){

	if(this->time==0){
		int lap = (point.x - this->x)*(point.x - this->x) + (point.y - this->y)*(point.y - this->y);
		//std::cout << lap << std::endl;
		if(  lap < this->size *this->size){

			this->time = 100;
			return true;

		}else{
			return false;
		}

	}else
		this->time--;
		return false;


}
