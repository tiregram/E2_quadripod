#include <stdlib.h>
#include <ncurses.h>
#include "../include/basic.h"
#include "../data/data_struct.h"
#include "ncurses_Frame.h"
#include "ncurses_ServoWindow.h"
#include "ncurses_CmdLine.h"

ncu_frame * frame_init(int x,int y/*,circular_vector* data*/){
	ncu_frame * this = malloc(sizeof(ncu_frame));
	this->con = newwin(25,50, y, x);

	this->servo_panel = servoWindows_init(25,0);
	//servoWindows_refrechWindows(this->servo_panel);

	box(this->con, 0 , 0);	
	wprintw(this->con,"Frame");
	mvwhline(this->con,4 ,1,' '|A_REVERSE,48);
	mvwhline(this->con,23 ,1,' '|A_REVERSE,48);
	wrefresh(this->con);

	this->scrool = newwin(19,48,y+5,x+1);
	
/*	this->data = data;*/
	return this;
}

void frame_change(ncu_frame *this,circular_vector *data){
		
	this->data = data;
}




void renderOneMouv(WINDOW * win, int y,int option,struct circular_vector_mouv * is){
	wattron(win,option);
	mvwprintw( win,y,1,"=>|%3i|%3i|%3i|%3i|%3i|%3i|%3i|%3i|a%i",
			is->mouv[0].pos,
			is->mouv[1].pos,
			is->mouv[2].pos,
			is->mouv[3].pos,
			is->mouv[4].pos,
			is->mouv[5].pos,
			is->mouv[6].pos,
			is->mouv[7].pos,
			is
			);
	wattroff(win,option);
}


void frame_refrechlist(ncu_frame* this){	
	int x,y;
	struct 	circular_vector_mouv*  stop = this->data->curent;
	getmaxyx(this->scrool,y,x);
	renderOneMouv(this->scrool,y/2,A_REVERSE,stop);
	struct 	circular_vector_mouv* pr = stop->prev;
	struct 	circular_vector_mouv* nx = stop->next;
	int i= 1;
	while(!(pr == nx || pr->next==nx || (y/2-i)==0) ){


		if(nx==this->data->first)
			renderOneMouv(this->scrool,y/2+i,A_UNDERLINE |A_NORMAL,nx);
		else 
			renderOneMouv(this->scrool,y/2+i,A_NORMAL,nx);
		
		if(pr==this->data->first)
			renderOneMouv(this->scrool,y/2-i,A_UNDERLINE|A_NORMAL,pr);
		else 
			renderOneMouv(this->scrool,y/2-i,A_NORMAL,pr);

		pr = pr->prev;
		nx = nx->next;	
		i=i+1;		
	}
	mvwprintw(this->con,2,2,"nb of Frame %3i",(i-1)*2+1);
	wrefresh(this->scrool);
	wrefresh(this->con);

}


//action 0 no refrech| 1 refrech | 2 refrech|
int frame_action(ncu_frame* this,cmd_line* cmda){
	int action= cmd_getCh(cmda); 	
	switch(action){
		case 'q':
			return 0;
			break;
		case KEY_UP:
			this->data->curent= this->data->curent->prev;
			servoWindows_change(this->servo_panel,this->data->curent->mouv);
			servoWindows_refrechWindows(this->servo_panel);	
			break;
		case KEY_DOWN:
			this->data->curent= this->data->curent->next;
			servoWindows_change(this->servo_panel,this->data->curent->mouv);
			servoWindows_refrechWindows(this->servo_panel);	
			break;
		case 'n':
			struct_new(this->data,STRUCT_AVANT);
			
			break;
		case 'e':

			while(servoWindows_action(this->servo_panel,cmda)){
			;}
			
				
			break;
	}
	frame_refrechlist(this);
	return 1;
}

char * getKey(){
	return "UP: move up, DOWN: move DOWN, r: refresh, n: new";
}
