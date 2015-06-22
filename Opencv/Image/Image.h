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

#define ECCART 5

class Image {
public:
	Image();
	virtual ~Image();
	void detectCircle(int iLowH, int iHighH);
	void creeImage();
	void renderImage();
	//void createCercleDetect(); //deprecated
	void drawCercle(cv::Point center,int radius,cv::Scalar color, int thickness);
	void isolateCircles();
	cv::Point averageCenter();
	cv::Mat& getImgOriginal();

private:
	cv::Mat imgOriginal;
	cv::VideoCapture cap;
	std::vector<cv::Vec3f> cercleDetect;
	bool isOn;
	bool canRead;

};

#endif /* IMAGE_H_ */
