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
#include <vector>
#include "CommandeCercle.h"



class Image {
public:
	Image();
	void creeImage();
	void renderImage();
	cv::Mat& getImgOriginal();
    CommandeCercle* getJoystick();
	 CommandeCercle* getCommande();

private:
	cv::Mat imgOriginal;
	cv::VideoCapture cap;
	bool isOn;
	bool canRead;
	CommandeCercle* cercleJoystick;
	CommandeCercle* cercleCommande;

};

#endif /* IMAGE_H_ */
