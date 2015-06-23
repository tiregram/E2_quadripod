#ifndef COMMANDECERCLE_H_
#define COMMANDECERCLE_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

#define ECCART 5

class CommandeCercle{
public:
	CommandeCercle(int iLowH, int iHighH,int iLowS,int iHighS,int iLowV, int iHighV ,int radius,cv::Scalar colorDisplay);
	void drawCercle(cv::Mat& image);
	void isolateCircles();
	void averageCenter();
	void detectCircle(cv::Mat& image);
	cv::Point getPoint();


private:
	int radius, iLowH, iHighH, iLowS, iHighS, iLowV, iHighV, thickness;
	cv::Scalar colorDisplay;
	cv::Point point;
	std::vector<cv::Vec3f> cercleDetect;
};

#endif /* COMMANDECERCLE_H_ */
