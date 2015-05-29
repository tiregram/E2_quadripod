/*
 * =====================================================================================
 *
 *       Filename:  opencv_gesture.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/04/2015 19:23:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ruhtra (o$), ruhtra.mar@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */


#include "cv.h"
#include "highgui.h"
#include <math.h>
#include <iostream>
#include "opencv_jostic.h"

using namespace cv;

int main(int argc, char** argv)
{
	Mat img, gray;
	VideoCapture cap(0); // open the default camera

	Ocv_jostic jos(100,100);


	if(!cap.isOpened())  // check if we succeeded
		return -1;

	cap>>img;
	namedWindow( "circles", 1 );
	
	std::cout<<"row:"<<img.rows<<"col:"<<img.cols<<std::endl;
	Point controle1(img.cols*4/5,img.rows*3/4);
	Point controle2(img.cols*1/5,img.rows*3/4);

	while(1){
		cap>>img;


		cvtColor(img, gray, CV_BGR2GRAY);
		// smooth it, otherwise a lot of false circles may be detected
		GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
		vector<Vec3f> circles;
		HoughCircles(gray, circles, CV_HOUGH_GRADIENT,
				2, gray.rows/4,atoi(argv[1]), atoi(argv[2]), 1,200);//100 100
		for( size_t i = 0; i < circles.size(); i++ )
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			// draw the circle center
		
			circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
			circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}

		jos.use(img,circles);	
		jos.refresh(img);	

		imshow("cirlces", img);
		if(waitKey(30) >= 0) break;

	}
	waitKey(0);
	return 0;
}


