#include <ncurses.h>
#include <stdlib.h>

#include "ncurses_MessageBox.h"


WINDOW * a_privFunc_create_newwin(int height, int width, int starty, int startx);

MessBox * messageBox_init(int  startX,int startY,int sizeY,int sizeX,char * titre){
	
	MessBox * this = malloc(sizeof(MessBox));

	WINDOW * locale = a_privFunc_create_newwin(sizeY,sizeX,startY,startX);
	wprintw(locale," %s",titre);
	wrefresh(locale);		

	WINDOW * locMes = newwin(sizeY-2,sizeX-2,startY+1, startX+1);
	
	wrefresh(locMes);		
	scrollok(locMes, TRUE);
	
	this->cont = locale;
	this->mess = locMes;

	return this;
}

void messageBox_refrech(MessBox * this ){	
	wrefresh(this->mess);
}


void messageBox_print(MessBox * this,char type,char *message, ...){
	start_color();
	init_pair(1, COLOR_GREEN , COLOR_BLACK );
	init_pair(2, COLOR_WHITE , COLOR_BLACK );
	init_pair(3, COLOR_RED   , COLOR_BLACK );
	
	switch(type){
		case MESBOX_ERROR: 
			wattron(this->mess,COLOR_PAIR(3));
			break;
		case MESBOX_VALID: 
			wattron(this->mess,COLOR_PAIR(1));
			break;
		case MESBOX_BASIC: 
			wattron(this->mess,COLOR_PAIR(2));
			break;
	}
	va_list va;
	va_start(va,message);
	
	wprintw(this->mess,message,va);	
	switch(type){
		case MESBOX_ERROR: 
			wattroff(this->mess,COLOR_PAIR(3));
			break;
		case MESBOX_VALID: 
			wattroff(this->mess,COLOR_PAIR(1));
			break;
		case MESBOX_BASIC: 
			wattroff(this->mess,COLOR_PAIR(2));
			break;
	}
}



WINDOW *  a_privFunc_create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		
	wrefresh(local_win);		

	return local_win;
}
