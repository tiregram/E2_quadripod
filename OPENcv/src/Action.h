/*
 * Action.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef ACTION_H_
#define ACTION_H_

class Action {
public:
	Action();
	virtual ~Action();
	virtual void doAction()=0;


};

#endif /* ACTION_H_ */
