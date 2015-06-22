/*
 * ItemIterface.h

 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef ITEMINTERFACE_H_
#define ITEMINTERFACE_H_


#include "ItemInterface.h"
#include "Detects/DetectInterface.h"
#include "Action/Action.h"
#include "Detects/Detect.h"
#include "../Image/Image.h"

#include <vector>
#include <iostream>
#include <tuple>



class ItemInterface {
public:
	ItemInterface();
	virtual ~ItemInterface();
	virtual void addDetectAndAction(std::vector<std::pair<DetectInterface,Action>>&);
	virtual void draw(cv::Mat& img);


};


#endif /* ITEMINTERFACE_H_ */
