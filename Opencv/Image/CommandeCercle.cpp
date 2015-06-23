
//g++ `pkg-config --cflags opencv` CommandeCercle.cpp `pkg-config --libs opencv` -o CommandeCercle
#include "CommandeCercle.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

CommandeCercle::CommandeCercle(int iLowH, int iHighH,int iLowS,int iHighS,int iLowV, int iHighV ,int radius,cv::Scalar colorDisplay){
	  this->iLowH=iLowH;
	  this->iHighH=iHighH;
	  this->iLowS=iLowS;
	  this->iHighS=iHighS;
	  this->iLowV=iLowV;
	  this->iHighV=iHighV;
	  this->radius=radius;
	  this->colorDisplay=colorDisplay;
	  this->thickness=-1;
}


void CommandeCercle::detectCircle(cv::Mat& image){

		cv::Mat imgHSV, imgThresholded, imgGrayTraite;
		cvtColor(image, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
		cv::inRange(imgHSV,cv::Scalar(this->iLowH, this->iLowS, this->iLowV),cv::Scalar(this->iHighH, this->iHighS, this->iHighV),imgThresholded);

		//morphological opening (remove small objects from the foreground)
		cv::erode(
				imgThresholded,
				imgThresholded,
				cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

		cv::dilate(
				imgThresholded,
				imgThresholded,
				getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

		//morphological closing (fill small holes in the foreground)
		cv::dilate(
				imgThresholded,
				imgThresholded,
				cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(5, 5)) );

		cv::erode(
				imgThresholded,
				imgThresholded,
				cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );


		cv::cvtColor(image,imgGrayTraite, cv::COLOR_BGR2GRAY);
		bitwise_and(imgGrayTraite,imgThresholded,imgThresholded);
		//imshow("imgThresholded", imgThresholded);

	        cv::GaussianBlur(imgThresholded,imgThresholded,cv::Size(9,9),2,2);

		HoughCircles( imgThresholded, this->cercleDetect, CV_HOUGH_GRADIENT, 1, 1, 100, 20, 10, 100 );
	        /// Apply the Hough Transform to find the circles25, 200 );
	        //HoughCircles( imgGrayTraite, circles, CV_HOUGH_GRADIENT, 2, imgGrayTraite.rows/4, 200, 100, 1, 200 );

}

void CommandeCercle::drawCercle(cv::Mat& image){
		CommandeCercle::detectCircle(image);
		CommandeCercle::isolateCircles();
		cv::circle( image, this->point, this->radius, this->colorDisplay,this->thickness, 8, 0 );
	}

void CommandeCercle::isolateCircles(){

	CommandeCercle::averageCenter();
	for( size_t i = 0; i < this->cercleDetect.size(); i++ )
		{
		    if((this->point.x+ECCART>this->cercleDetect[i][0]&&this->cercleDetect[i][0]>this->point.x-ECCART)||(this->point.y+ECCART>this->cercleDetect[i][1]&&this->cercleDetect[i][1]>this->point.y-ECCART)){
			this->cercleDetect.erase(this->cercleDetect.begin()+i);
			}
		}
}

void CommandeCercle::averageCenter(){
 int somme=0;
 int x=0;
 int y=0;

	for( size_t i = 0; i < this->cercleDetect.size(); i++ )
		{
		    x+=this->cercleDetect[i][0];
		    y+=this->cercleDetect[i][1];
		    somme++;
		}
	this->point=cv::Point(cvRound((float)x/somme),cvRound((float)y/somme));
}

cv::Point CommandeCercle::getPoint(){

	return this->point;
}
