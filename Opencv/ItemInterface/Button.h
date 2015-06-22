/*
 * Button.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#define TIME_VALID 100;
#define TIME_REPEAT 100;


#include <vector>
#include <tuple>
#include <utility>
#include <string>
#include "ItemInterface.h"
#include "Detects/DetectInterface.h"
#include "Action/Action.h"
#include "Detects/Detect.h"


class Button : public ItemInterface {
public:
	Button( std::string ,int,int ,int ,int);
	virtual ~Button();
	virtual void addDetectAndAction(std::vector<std::pair<DetectInterface,Action>>&,data_UartSender * sender);
	virtual void draw(cv::Mat& img);

private:
	int num;
	int x;
	int y;
	int size;
	std::string name;
	bool valid;
	int timerDeValid;
	int timeBeforeRepeat;

};

#endif /* BUTTON_H_ */
