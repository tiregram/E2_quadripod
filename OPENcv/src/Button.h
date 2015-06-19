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
#include "DetectInterface.h"
#include "Action.h"
#include "Detect.h"


class Button : public ItemInterface {
public:
	Button( std::string ,int ,int ,int  );
	virtual ~Button();
	virtual void addDetectAndAction(std::vector<std::pair<DetectInterface,Action>>&);
	virtual void draw(cv::Mat& img);

private:
	int x;
	int y;
	int size;
	std::string name;
	bool valid;
	int timerDeValid;
	int timeBeforeRepeat;

};

#endif /* BUTTON_H_ */
