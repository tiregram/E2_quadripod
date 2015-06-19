/*
 * ItemIterface.h

 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef ITEMINTERFACE_H_
#define ITEMINTERFACE_H_

#include <iostream>
#include "ItemInterface.h"
#include "DetectInterface.h"
#include <vector>
#include "Action.h"
#include "Detect.h"
#include "Image.h"
#include <tuple>



class ItemInterface {
public:
	ItemInterface();
	virtual ~ItemInterface();
	virtual void addDetectAndAction(std::vector<std::pair<DetectInterface,Action>>&);
	virtual void draw(cv::Mat& img);


};


#endif /* ITEMINTERFACE_H_ */
