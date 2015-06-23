
#include "../interface/ncurses_Menu.h"
#include "../interface/ncurses_MessageBox.h"
#include "../include/ctrl.h"
#include "../data/data_UartSender.h"
#include "../data/data_ListMenu.h"
#include "../interface/ncurses_FileSelect.h"
#include "../interface/ncurses_Match.h"
#include "ctrl_Sequence.h"

ncu_menu_panel * menu_opencv;
data_UartSender * sender;
ncu_fileSelect * file_selector;
ncu_match *match;


int Copencv_init(){
	char** menu= menu_list_init(20,8);
	menu[0] ="Launch";
	menu[1] ="Config";
	menu[2] ="Help";
	menu[3] ="Exit";
	menu_opencv = ncu_menu_init(1,1,20,9,menu,4);
	ncu_fileSelect_getUart(file_selector,cmda);
	sender = data_UartSender_passModelToSender(file_selector->uart);
	match = ncu_match_init(sender);

	return 0;
}

void Copencv_setFileSelector(ncu_fileSelect * fs){
	file_selector = fs;
}
int main_cpp(data_UartSender *);

int Copencv_lauch(){
	ncu_menu_refrech(menu_opencv);
	while(1)
		switch(ncu_menu_action(menu_opencv,cmda)){
			case 0:
				messageBox_print(messBoxa,MESBOX_VALID,"Lancement de OpenCv");

				main_cpp(sender);

				break;
			case 1:
				ncu_match_action(match,cmda,interface_seq);

				break;
			case 2:

				break;
			case 3:

				break;

			case 4 :

				break;

			case -1:return 0;
				break;
		}
}


	void Copencv_dest(){
		}

