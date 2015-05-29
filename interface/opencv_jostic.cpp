#include "opencv_jostic.h"

using namespace cv;
using namespace std;

Ocv_jostic::Ocv_jostic(double x, double y){
	this->pos = new cv::Point(x,y);
	this->isActivate = false;
	this->name = "jos";
	this->activateCounter = 0;
}

Ocv_jostic::~Ocv_jostic(){


}
/*
   int Ocv_jostic::use(){
   return true;	
   }

   int Ocv_jostic::detecteaction(){
   return true;	
   }*/

void Ocv_jostic::refresh(cv::Mat& mat){
	char nameval[20];
	sprintf( nameval,"%s %i",this->name,this->activateCounter);
	cv::circle(mat,*this->pos ,SIZE_FIRST,(isActivate)?Scalar(100,100,255):Scalar(0,255,0),6,8, 0);
	cv::circle(mat,*this->pos ,
	(isActivate)?
			SIZE_SECOND - this->activateCounter : 
			SIZE_FIRST + this->activateCounter
			,
	(isActivate)?
			Scalar(100,100,100):
			Scalar(200,100,100)
			,2,8, 0);
	cv::Point origine(this->pos->x+SIZE_SECOND,(this->pos->y)+SIZE_FIRST);
	cv::putText(mat,nameval, origine,FONT_HERSHEY_SIMPLEX,0.5,CV_RGB(255,255,255),2,8,false);
}


void Ocv_jostic::activate(Mat mat, vector<Vec3f> circle){
	bool haveACircleOn = false;

	for(int i = 0 ; i<circle.size();i++){	
		if(
		(this->isActivate)?
		SIZE_SECOND * SIZE_SECOND:
		SIZE_FIRST * SIZE_FIRST >= 
		(this->pos->x - circle[i][0])*
		(this->pos->x - circle[i][0])+
		(this->pos->y - circle[i][1])*
		(this->pos->y - circle[i][1])
		  ){
			haveACircleOn = true;
		}	
	}

	if(this->isActivate){
		if(!haveACircleOn){
			this->activateCounter  += 1;	
		}else{
			if(this->activateCounter!=0)
				this->activateCounter -=1; 
		}
	}else{
		if(haveACircleOn){
			this->activateCounter += 1;
		}else {	
			if(this->activateCounter!=0)
				this->activateCounter -=1; 
		}
	}



	if(this->activateCounter == SIZE_SECOND-SIZE_FIRST){
		this->activateCounter =0;	
		this->isActivate = !this->isActivate;	
	}

}

void Ocv_jostic::use(Mat mat,vector<Vec3f> circle){
	this->activate(mat,circle);
		
	if (this->isActivate){
		for(:){
		
		
		
		}				
	
	}	

	return;	
}



/*
   bool Ocv_jostic::detectNord(vector<Vec3f> circles , Mat mat){

   return false;
   }

   bool Ocv_jostic::detectWest(vector<Vec3f> circles , Mat mat){

   return false;
   }

   bool Ocv_jostic::detectSouth(vector<Vec3f> circles , Mat mat){

   return false;
   }

   bool Ocv_jostic::detectEast(vector<Vec3f> circles , Mat mat){

   return false;
   }
   */
