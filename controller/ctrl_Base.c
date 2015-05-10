#include "ctrl_Base.h"
#include "../data/data_ListMenu.h"
#include "../include/ctrl.h"
#include "ctrl_Sequence.h"
#include "../interface/ncurses_Menu.h"
#include "../interface/ncurses_CmdLine.h"
#include "../data/data_Sequence.h"
//ils sont 1 et ce ne sont que des * 



menu_panel * menu_base;

//menuPrincipal
int Cbase_lauch(){
	cmda = cmd_init();
	




	menu_refrech(menu_base);
	while(1)
	switch(menu_action(menu_base,cmda)){
		case 0:
			Cseq_lauch();
			menu_refrech(menu_base);
			break;
		case 1: 
			menu_refrech(menu_base);
			break;
		case -1:return 0;
			break;
	}

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
	menu_base = menu_init(1,1,20,9,menu,4);
	
	seqa = sequence_init();
	
	Cseq_init();
	
}
