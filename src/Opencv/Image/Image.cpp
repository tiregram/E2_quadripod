//g++ `pkg-config --cflags opencv` Image.cpp `pkg-config --libs opencv` -o Image
//

#include "Image.h"

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "CommandeCercle.h"

Image::Image(){
	cv::namedWindow("OutImg",CV_WINDOW_FULLSCREEN);
	//cv::setWindowProperty("OutImg", CV_WND_PROP_ASPECTRATIO, CV_WINDOW_KEEPRATIO);
	cercleJoystick=new CommandeCercle(24,30,104,255,0,255,25,cv::Scalar(0,0,255));
	cercleCommande=new CommandeCercle(69, 91,52,255,0,255,25,cv::Scalar(0,255,0));
	this->cap= cv::VideoCapture(1);
	if ( !cap.isOpened() )  // if not success, exit program
	  {
	         	std::cout << "Cannot open the web cam" << std::endl;
	         	this->isOn = false;
	  }
	else{
		this->isOn = true;
	 }
	 Image::creeImage();
	
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
		cercleJoystick->drawCercle(this->imgOriginal);
		cercleCommande->drawCercle(this->imgOriginal);
		imshow("OutImg",this->imgOriginal);
		cv::waitKey(10);
		}
	else
		std::cout<<"cam probleme"<<std::endl;

}

cv::Mat& Image::getImgOriginal(){
	return this->imgOriginal;
}

 CommandeCercle* Image::getJoystick(){
	return this->cercleJoystick;

}
 CommandeCercle* Image::getCommande(){
	return this->cercleCommande;

}


/* int main( int argc, char** argv )
 {
	Image image;

	while(true){
		image.creeImage();
		image.renderImage();}
	
	return 0;
}*/
