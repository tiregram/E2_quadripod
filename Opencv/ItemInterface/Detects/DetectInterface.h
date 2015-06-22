/*
 * DetectInterface.h
 *
 *  Created on: 18 juin 2015
 *      Author: ruhtra
 */

#ifndef DETECTINTERFACE_H_
#define DETECTINTERFACE_H_

#include "Detect.h"


class DetectInterface: public Detect{

public:
	DetectInterface(int x,int y,int size);
	virtual ~DetectInterface();
	virtual bool tryToDetect(cv::Point point);

private:


	int x;
	int y;
	int size;
	int time;

};

#endif /* DETECTINTERFACE_H_ */
