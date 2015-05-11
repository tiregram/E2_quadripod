#include <ncurses.h>
#include <unistd.h>
#include "ncurses_Interface.h"
#include "../include/basic.h"
#include "ncurses_inputSelect.h"
#include "ncurses_ServoWindow.h"
#include "../data/data_struct.h"
#include "ncurses_MessageBox.h"
#include "ncurses_CmdLine.h"
#include "ncurses_Frame.h"



cmd_line  * cmda;
ncu_list_servo * servo_panel;
MessBox* messa_panel;
ncu_frame* frame_panel;

void  interface_init(circular_vector* data){
	initscr();		/* Start curses mode 		*/
	raw();			/* Line buffering disabled	*/
	noecho();		/* Don't echo() while we do getch */
	start_color();
	
	cmda = cmd_init();	

	messa_panel = messageBox_init(55,20,"message");
	messageBox_refrech(messa_panel);
	
	frame_panel = frame_init(1,20,data);
	frame_refrechlist(frame_panel);
}



int interface_action(){
	
	int ch;
	mvwprintw(cmda->win,0,0,"cmd:");
	wrefresh(cmda->win);
	frame_action(frame_panel,cmda);	
	return 1;
}












