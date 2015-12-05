/*
 * Action.cpp
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#include "Action.h"
#include <iostream>
#include <string>

Action::Action(std::string name,int num,data_UartSender *sender) {

	this->name = name;
	this->num = num;
	this->sender = sender;
}


void Action::doAction(){
	std::cout << "Action:"<< this->name << std::endl;
	this->sender->play(sender->file,this->sender->listOfAction[this->num]);

}


Action::~Action() {
	// TODO Auto-generated destructor stub
}

