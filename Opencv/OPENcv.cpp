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

	Button but("mouv1",SAY_MOUV_1,100,100,30);
	Button but1("mouv2",SAY_MOUV_2,100,200,30);
	Button but2("mouv3",SAY_MOUV_3,100,300,30);
	Button but3("mouv4",SAY_MOUV_4,100,400,30);

	Button but4("LEFT",SAY_RIGHT,400,300,30);
	Button but5("RUN",SAY_AVANCE,500,200,30);
	Button but6("BACK",SAY_RECULE,500,400,30);;
	Button but7("RIGHT",SAY_LEFT,600,300,30);


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


		for(auto ite : detecteToActionButton)
		{
			if(ite.first.tryToDetect(image.getCommande()->getPoint())){

				ite.second.doAction();

			}

		}



		for(auto ite : detecteToActionJoss)
			{
				if(ite.first.tryToDetect(image.getJoystick()->getPoint())){

					ite.second.doAction();

				}

			}





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
