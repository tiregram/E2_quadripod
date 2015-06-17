/*
 * ItemIterface.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef ITEMITERFACE_H_
#define ITEMITERFACE_H_

class ItemIterface {
public:
	ItemIterface();
	virtual ~ItemIterface();
	virtual void addDetectAndAction(std::vector<std::pair<Action,Detect>>)=0;
};

#endif /* ITEMITERFACE_H_ */
