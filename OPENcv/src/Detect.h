/*
 * Detect.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef DETECT_H_
#define DETECT_H_

class Detect {
public:
	Detect();
	virtual ~Detect();
	virtual bool tryDetect()=0;
//	virtual static cv::Mat getVideo();
protected:
//static cv::Mat outVideo;

};

#endif /* DETECT_H_ */
