//============================================================================
// Name        : OPENcv.cpp
// Author      : ruhtra
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ItemInterface.h"
#include <vector>
#include "Action.h"
#include "Detect.h"
#include "Image.h"
#include "Button.h"
#include <tuple>


using namespace std;

int main() {

	std::cout << "hi" <<std::endl;
	std::cout << "init" <<std::endl;

	std::cout << "cam" <<std::endl;
	Image image;

	std::cout << "list Item" <<std::endl;
	std::vector<ItemInterface> listItem;

	Button but("mouv1",100,100,30);
	Button but1("mouv2",100,200,30);
	Button but2("mouv3",100,300,30);
	Button but3("mouv4",100,400,30);

	Button but4("RIGHT",400,300,30);
	Button but5("UP",500,200,30);
	Button but6("DOWN",500,400,30);
	Button but7("LEFT",600,300,30);


	std::cout << "detecte and action" <<std::endl;

	std::vector<std::pair<DetectInterface,Action>> detecteToActionButton;
	std::vector<std::pair<DetectInterface,Action>> detecteToActionJoss;

	but.addDetectAndAction(detecteToActionButton);
	but1.addDetectAndAction(detecteToActionButton);
	but2.addDetectAndAction(detecteToActionButton);
	but3.addDetectAndAction(detecteToActionButton);
	but4.addDetectAndAction(detecteToActionJoss);
	but5.addDetectAndAction(detecteToActionJoss);
	but6.addDetectAndAction(detecteToActionJoss);
	but7.addDetectAndAction(detecteToActionJoss);




	while('q' !=cv::waitKey(10)){
		image.creeImage();



		image.detectCircle(61,96);
		image.isolateCircles();
		cv::Point cercle1=image.averageCenter();

		for(auto ite : detecteToActionButton)
		{
			if(ite.first.tryToDetect(cercle1)){

				ite.second.doAction();

			}

		}

		image.detectCircle(96,110);
		image.isolateCircles();
		cv::Point cercle2=image.averageCenter();

		for(auto ite : detecteToActionJoss)
			{
				if(ite.first.tryToDetect(cercle2)){

					ite.second.doAction();

				}

			}


		image.drawCercle(cercle1,20,cv::Scalar(0,0,255),5);
		image.drawCercle(cercle2,20,cv::Scalar(255,0,0),5);


		but.draw(image.getImgOriginal());
		but1.draw(image.getImgOriginal());
		but2.draw(image.getImgOriginal());
		but3.draw(image.getImgOriginal());
		but4.draw(image.getImgOriginal());
		but5.draw(image.getImgOriginal());
		but6.draw(image.getImgOriginal());
		but7.draw(image.getImgOriginal());


		image.renderImage();
	}


	return 0;
}
