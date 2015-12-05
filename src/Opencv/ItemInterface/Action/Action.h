/*
 * Action.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef ACTION_H_
#define ACTION_H_
#include "../../../include/structForCPP.h"
#include <iostream>
#include <string>

class Action {
public:
	Action(std::string name ,int num,data_UartSender * sender);
	virtual ~Action();
	virtual void doAction();
private:

	std::string name;
	int num;
	data_UartSender* sender;


};


#endif /* ACTION_H_ */
