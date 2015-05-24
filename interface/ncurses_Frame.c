#include <stdlib.h>
#include <ncurses.h>
#include "../include/basic.h"
#include "../data/data_struct.h"
#include "ncurses_Frame.h"
#include "ncurses_ServoWindow.h"
#include "ncurses_CmdLine.h"

ncu_frame * ncu_frame_init(int x,int y/*,circular_vector* data*/){
	ncu_frame * this = malloc(sizeof(ncu_frame));
	this->con = newwin(25,50, y, x);

	this->servo_panel = ncu_servoWindows_init(25,0);
	//servoWindows_refrechWindows(this->servo_panel);

	this->delay = ncu_inputSelect_init(NULL,y+5+9,x+18,100,999999,6);
	this->scrool = newwin(19,48,y+5,x+1);
	
	return this;
}

void ncu_frame_change(ncu_frame *this,circular_vector *data){
	werase(this->scrool);
	ncu_servoWindows_change(this->servo_panel ,data->curent->mouv);	
	this->data = data;

}




void renderOneMouv(WINDOW * win, int y,int option,struct circular_vector_mouv * is,char * text){
	wattron(win,option);
	mvwprintw( win,y,1,"=>a%s| delay %6u",
			text,
			is->delay
			);
	wattroff(win,option);
}




void ncu_frame_refrechlist(ncu_frame* this){	
	int y;
	struct 	circular_vector_mouv*  stop = this->data->curent;
	y=getmaxy(this->scrool);
	renderOneMouv(this->scrool,y/2,A_REVERSE,stop,"frame");
	struct 	circular_vector_mouv* pr = stop->prev;
	struct 	circular_vector_mouv* nx = stop->next;
	int i= 1;
	while(!(pr == nx || pr->next==nx || (y/2-i)==0) ){


		if(nx==this->data->first)
			renderOneMouv(this->scrool,y/2+i,A_UNDERLINE |A_NORMAL,nx,"frame");
		else 
			renderOneMouv(this->scrool,y/2+i,A_NORMAL,nx,"frame");
		
		if(pr==this->data->first)
			renderOneMouv(this->scrool,y/2-i,A_UNDERLINE|A_NORMAL,pr,"frame");
		else 
			renderOneMouv(this->scrool,y/2-i,A_NORMAL,pr,"frame");

		pr = pr->prev;
		nx = nx->next;	
		i=i+1;		
	}
	mvwprintw(this->con,2,2,"nb of Frame %3i",(i-1)*2+1);
	wrefresh(this->con);
	wrefresh(this->scrool);
}

void ncu_frame_change_delay(ncu_frame* this){
	ncu_inputSelect_changeCible(this->delay,&this->data->curent->delay);	
	ncu_inputSelect_modifInput(this->delay);	
}
 
void ncu_frame_hide(ncu_frame * this){
	wclear(this->scrool);
	wclear(this->con);
	wrefresh(this->scrool);
	wrefresh(this->con);
	ncu_servoWindows_hide(this->servo_panel);
}

void frame_show(ncu_frame * this){
	box(this->con, 0 , 0);	
	wprintw(this->con,"Frame");
	mvwhline(this->con,4 ,1,' '|A_REVERSE,48);
	mvwhline(this->con,23 ,1,' '|A_REVERSE,48);
	ncu_servoWindows_show(this->servo_panel);	
	wrefresh(this->con);
	wrefresh(this->scrool);
}



//action 0 no refrech| 1 refrech | 2 refrech|
int ncu_frame_action(ncu_frame* this,ncu_cmdLine* cmda){
	frame_show(this);
	ncu_servoWindows_refrechWindows(this->servo_panel);	
	while(1){
	ncu_frame_refrechlist(this);

	int action= ncu_cmd_getCh(cmda);

	switch(action){
		case 'q':
			ncu_frame_hide(this);
			return 0;
			break;
		case KEY_UP:
			this->data->curent= this->data->curent->prev;
		//	inputSelect_changeCible(this->delay_panel,&this->data->curent->delay);
			ncu_servoWindows_change(this->servo_panel,this->data->curent->mouv);
			ncu_servoWindows_refrechWindows(this->servo_panel);	
			break;
		case KEY_DOWN:
			this->data->curent= this->data->curent->next;
		//	inputSelect_changeCible(this->delay_panel,&this->data->curent->delay);
			ncu_servoWindows_change(this->servo_panel,this->data->curent->mouv);
			ncu_servoWindows_refrechWindows(this->servo_panel);	
			break;
		case 'n':
			struct_new(this->data,STRUCT_AVANT);
			
			break;
		case 'd':
			ncu_frame_change_delay(this);		
			break;
		case 'e':

			while(ncu_servoWindows_action(this->servo_panel,cmda)){
			;}
			
				
			break;
	}
	}
	return 1;
}


void ncu_frame_dest(ncu_frame * this){
	delwin(this->scrool);	
	delwin(this->con);	
	ncu_inputSelect_dest(this->delay);
	ncu_listServo_dest(this->servo_panel);
	free(this);
}	


char * getKey(){
	return "UP: move up, DOWN: move DOWN, r: refresh, n: new";
}
