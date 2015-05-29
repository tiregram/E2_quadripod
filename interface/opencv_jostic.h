#ifndef ocv_jostic_include 
#define ocv_jostic_include

#include "cv.h"
#include "highgui.h"
#include <string>
#include <map>
#define TIME_TO_LOCK 20
#define SIZE_FIRST 30
#define SIZE_SECOND 100

//typedef void (*actionPointer)(void); // function pointeAr type
//typedef void (*detectPointer)(void); // function pointeAr type
//typedef std::map<std::string, ScriptFunction> script_map;:
using  namespace cv;

#define FUNCTION_TYPE_DETECT (bool)((vector<Vec3f>*,Mat*));
#define FUNCTION_TYPE_ACTION


class Ocv_jostic{

	public:
		Ocv_jostic(double , double);
		~Ocv_jostic();	
	
		void refresh(Mat&);
		void use(Mat mat,vector<Vec3f> circle);
		void activate(Mat mat, vector<Vec3f> circle);
	

	private: 

	bool isActivate;
	cv::Point*  pos; 
	std::string name;
	int activateCounter;
	std::map<FUNCTION_TYPE_DETECT,FUNCTION_TYPE_ACTION> listAction;

};
#endif
