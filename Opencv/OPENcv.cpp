//============================================================================
// Name        : OPENcv.cpp
// Author      : ruhtra
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ItemInterface/ItemInterface.h"
#include <vector>
#include "ItemInterface/Action/Action.h"
#include "ItemInterface/Detects/Detect.h"
#include "Image/Image.h"
#include "ItemInterface/Button.h"
#include <tuple>

#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "../include/structForCPP.h"

extern "C" int main_cpp(data_UartSender *);

using namespace std;

int main_cpp(data_UartSender * sender) {




	std::cout << "hi" <<std::endl;
	std::cout << "init" <<std::endl;

	std::cout << "cam" <<std::endl;
	Image image;

	std::cout << "list Item" <<std::endl;
	std::vector<ItemInterface> listItem;

	Button but("mouv1",0,100,100,30);
	Button but1("mouv2",1,100,200,30);
	Button but2("mouv3",2,100,300,30);
	Button but3("mouv4",3,100,400,30);

	Button but4("RIGHT",4,400,300,30);
	Button but5("UP",SAY_AVANCE,500,200,30);
	Button but6("DOWN",6,500,400,30);;
	Button but7("LEFT",7,600,300,30);


	std::cout << "detecte and action" <<std::endl;

	std::vector<std::pair<DetectInterface,Action>> detecteToActionButton;
	std::vector<std::pair<DetectInterface,Action>> detecteToActionJoss;

	but.addDetectAndAction(detecteToActionButton,sender);
	but1.addDetectAndAction(detecteToActionButton,sender);
	but2.addDetectAndAction(detecteToActionButton,sender);
	but3.addDetectAndAction(detecteToActionButton,sender);
	but4.addDetectAndAction(detecteToActionJoss,sender);
	but5.addDetectAndAction(detecteToActionJoss,sender);
	but6.addDetectAndAction(detecteToActionJoss,sender);
	but7.addDetectAndAction(detecteToActionJoss,sender);




	while('q' !=cv::waitKey(10)){
		image.creeImage();



		image.detectCircle(25,44);
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

