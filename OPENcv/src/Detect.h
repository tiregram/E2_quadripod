/*
 * Detect.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef DETECT_H_
#define DETECT_H_

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Detect {
public:
	Detect();
	virtual ~Detect();
	virtual bool tryDetect();
};

#endif /* DETECT_H_ */
