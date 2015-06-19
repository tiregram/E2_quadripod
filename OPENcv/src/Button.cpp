/*
 * Button.cpp
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#include "Button.h"
#include <string>
#include "Detect.h"
#include "DetectInterface.h"
#include "Action.h"
#include <vector>
#include <tuple>
#include "ItemInterface.h"


Button::Button(std::string name,int x,int y,int size){

	this->name = name;
	this->valid =false;
	this->timerDeValid = 0;
	this->timeBeforeRepeat=0;
	this->x =x ;
	this->y =y;
	this->size = size;
}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

void Button::draw(cv::Mat& img){
	cv::Point pos(x,y);
	cv::circle(img,pos, this->size,cv::Scalar(255,0,0),2, 8, 0 );

	cv::Point origine(this->x - this->size +5 ,this->y +5);

	cv::putText(img,this->name, origine,cv::FONT_HERSHEY_SIMPLEX,0.5,CV_RGB(255,255,255),2,8,false);


}


void Button::addDetectAndAction(std::vector<std::pair<DetectInterface,Action>>& vad){

	DetectInterface det(this->x,this->y,this->size);
	Action act(this->name);


	vad.push_back(std::make_pair(det,act));


}



