/*
 * Image.cpp
 *
 *  Created on: 17 juin 2015
 *      Author: ruhtra
 */

//g++ `pkg-config --cflags opencv` Image.cpp `pkg-config --libs opencv` -o Image

#include "Image.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

Image::Image() {
	this->canRead=false;
	cv::namedWindow("OutImg",CV_WINDOW_AUTOSIZE);
	this->cap= cv::VideoCapture(1);
	if ( !cap.isOpened() )  // if not success, exit program
	  {
	         	std::cout << "Cannot open the web cam" << std::endl;
	         	this->isOn = false;
	  }
	else{
		this->isOn = true;
	 }
	
}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

void Image::detectCircle(int iLowH, int iHighH){

		int iLowS = 0, iHighS = 255;
		int iLowV = 0, iHighV = 255;
		cv::Mat imgHSV, imgThresholded, imgGrayTraite;

		cvtColor(this->imgOriginal, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
		cv::inRange(imgHSV,cv::Scalar(iLowH, iLowS, iLowV),cv::Scalar(iHighH, iHighS, iHighV),imgThresholded);

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

		//imshow("Original", imgOriginal); //show the original image
		imshow("Thresholded Image", imgThresholded); //show the thresholded image

		cv::cvtColor(imgOriginal,imgGrayTraite, cv::COLOR_BGR2GRAY);
		bitwise_and(imgGrayTraite,imgThresholded,imgThresholded);
		//imshow("imgThresholded", imgThresholded);

	        cv::GaussianBlur(imgThresholded,imgThresholded,cv::Size(9,9),2,2);

		HoughCircles( imgThresholded, this->cercleDetect, CV_HOUGH_GRADIENT, 1, 1, 115, 25, 20, 100 );
	        /// Apply the Hough Transform to find the circles25, 200 );
	        //HoughCircles( imgGrayTraite, circles, CV_HOUGH_GRADIENT, 2, imgGrayTraite.rows/4, 200, 100, 1, 200 );

}



void Image::creeImage(){
	 if(this->isOn){
		bool bSuccess = this->cap.read(this->imgOriginal); // read a new frame from video
	         if (!bSuccess) //if not success, break loop
	        {
	             std::cout << "Cannot read a frame from video stream" << std::endl;
	             this->canRead = false;
	        }
		else{
		 this->canRead = true;
		 flip(this->imgOriginal, this->imgOriginal, 2);
		}
	}
	  

}

void Image::renderImage(){

	if(this->canRead){
		imshow("OutImg",this->imgOriginal);

		}
	else
		std::cout<<"cam probleme"<<std::endl;

}

//deprecated
/*void Image::createCercleDetect(){

		for( size_t i = 0; i < this->cercleDetect.size(); i++ )
		{
		    cv::Point center(cvRound(this->cercleDetect[i][0]), cvRound(this->cercleDetect[i][1]));
		    int radius = cvRound(this->cercleDetect[i][2]);
		    // circle center
		    //cv::circle( this->imgOriginal, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
		    // circle outline
		    cv::circle( this->imgOriginal, center, radius, cv::Scalar(0,0,255), 3, 8 , 0 );
		} 

}*/

void Image::drawCercle(cv::Point center,int radius,cv::Scalar color, int thickness){
		cv::circle( this->imgOriginal, center, radius, color,thickness, 8, 0 );
	}

void Image::isolateCircles(){

	cv::Point averagePoint=Image::averageCenter();
	for( size_t i = 0; i < this->cercleDetect.size(); i++ )
		{
		    if((averagePoint.x+ECCART>this->cercleDetect[i][0]&&this->cercleDetect[i][0]>averagePoint.x-ECCART)||(averagePoint.y+ECCART>this->cercleDetect[i][1]&&this->cercleDetect[i][1]>averagePoint.y-ECCART)){
			this->cercleDetect.erase(this->cercleDetect.begin()+i);
			}
		} 
}

cv::Point Image::averageCenter(){
 int somme=0;
 int x=0;
 int y=0;

	for( size_t i = 0; i < this->cercleDetect.size(); i++ )
		{
		    x+=this->cercleDetect[i][0];
		    y+=this->cercleDetect[i][1];
		    somme++;
		} 
	return cv::Point(cvRound((float)x/somme),cvRound((float)y/somme));
}
/*
int main( int argc, char** argv ){
	
	Image image;
	while('q' !=cv::waitKey(10)){
	image.creeImage();
	image.detectCircle(61,96);
	image.isolateCircles();
	image.isolateCircles();
  	cv::Point cercle1=image.averageCenter();
	image.detectCircle(96,110);
	image.isolateCircles();
	image.isolateCircles();
	image.isolateCircles();
  	cv::Point cercle2=image.averageCenter();
        image.drawCercle(cercle1,20,cv::Scalar(0,0,255),-1);
	image.drawCercle(cercle2,20,cv::Scalar(255,0,0),-1);
	image.renderImage();}
	
	return 0;
}*/


cv::Mat& Image::getImgOriginal(){
	return this->imgOriginal;
}
