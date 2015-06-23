#include "ctrl_Base.h"
#include "ctrl_openCv.h"
#include "../data/data_ListMenu.h"
#include "../include/ctrl.h"
#include "ctrl_Sequence.h"
#include "../interface/ncurses_Menu.h"
#include "../interface/ncurses_CmdLine.h"
#include "../data/data_Sequence.h"
#include "../interface/ncurses_MessageBox.h"
#include "../interface/ncurses_ListSequence.h"
#include "../interface/ncurses_FileSelect.h"
#include "../include/global.h"

//ils sont 1 et ce ne sont que des * 


ncu_menu_panel * menu_base;
ncu_fileSelect * file_selector;


//menuPrincipal
int Cbase_lauch(){

	ncu_menu_refrech(menu_base);
	while(1)
	switch(ncu_menu_action(menu_base,cmda)){
		case 0:
			Cseq_lauch();
			ncu_menu_refrech(menu_base);
			break;
		case 1: 
			Copencv_lauch();
			ncu_menu_refrech(menu_base);
			break;
		case  2: 
			messageBox_print(messBoxa,MESBOX_BASIC,"Dans un premier temps il est preférable de crée des sequence");
			break;
		case 3: 
			return 0;
			break;

		case -1:return 0;
			break;
	}
	return 0;

}



int Cbase_init(){
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	noecho();		/* Don't echo() while we do getch */
	start_color();
	
	char ** menu = menu_list_init(20,5);
	menu[0] = "Sequence";
	menu[1] = "OpenCv";	
	menu[2] = "help";
	menu[3] = "Exit";	
	menu_base = ncu_menu_init(1,1,20,9,menu,4);
	messBoxa=  messageBox_init(COLS*3/4+1,1,LINES-2,COLS/4,"Message");
	messageBox_print(messBoxa,MESBOX_BASIC,"salut\n");
	messageBox_refrech(messBoxa);	
	
	seqa = sequence_init();
	
	cmda = ncu_cmd_init();
		
	file_selector = ncu_fileSelect_init(20,6,25,1);
	fileSelecGlobal = file_selector;
	Cseq_init();
	Copencv_init();

	Copencv_setFileSelector(file_selector);
	Cseq_setFileSelector(file_selector);


	return 0;
	
}


int Cbase_destr(){
	echo();
	noraw();
	endwin();	
	return 0;

}
