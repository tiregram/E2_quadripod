/*
 * Action.cpp
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#include "Action.h"
#include <iostream>
#include <string>

Action::Action(std::string name) {

	this->name = name;
}


void Action::doAction(){
	std::cout << "Action:"<< this->name << std::endl;

}


Action::~Action() {
	// TODO Auto-generated destructor stub
}

