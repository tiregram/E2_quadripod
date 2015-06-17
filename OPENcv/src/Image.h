/*
 * Image.h
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Image {
public:
	Image();
	virtual ~Image();



private:
	cv::Mat img;
	std::vector<cv::Vec3f> cercleDetect;
};

#endif /* IMAGE_H_ */
