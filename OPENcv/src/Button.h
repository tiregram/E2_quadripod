/*
 * Button.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef BUTTON_H_
#define BUTTON_H_


#include <vector>
#include <tuple>
#include <utility>
#include "Action.h"
#include "Detect.h"

class Button {
public:
	Button();
	virtual ~Button();
	void addDetectAndAction(std::vector<std::pair<int,int> > );

private:
	int timerDeValid;
	int timeBeforeRepeat;


};

#endif /* BUTTON_H_ */
