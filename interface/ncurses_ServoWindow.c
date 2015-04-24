#include <ncurses.h>
#include <stdlib.h>
#include "ncurses_ServoWindow.h"
#include "ncurses_inputSelect.h"
#include "../include/basic.h"



void 	pricFunc_refrechWindow( servo * servo);
servo * privFunc_new(int x , int y,t_mouv val);
void  	pricFunc_destroy_win(WINDOW *local_win);
void 	privFunc_refrechWindow(servo * servo);


list_servo* servoWindows_init(int posx , int posy,t_mouv * mouv){
	list_servo * locale = malloc(sizeof(list_servo));
	for(int i = 0;i<nb_servo;i++){
		locale->list[i] = *privFunc_new(posx+1+20*i,posy+1+8*i,mouv[i]); 	
	}
	return locale;
}

void refrechWindows( list_servo * servos){
	int i = 0;
	for(i = 0 ; i<nb_servo ; i++){
		privFunc_refrechWindow(&servos->list[i]);
	}
}

WINDOW * privFunc_create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		
	wrefresh(local_win);		

	return local_win;
}


servo * privFunc_new(int x , int y,t_mouv val){
	servo * loc=malloc(sizeof(servo));
       	loc->win=privFunc_create_newwin(6,20,y,x);
	getbegyx(loc->win,y,x);
	wprintw(loc->win,"n*%i %s","test");
	mvwprintw(loc->win, 2, 2, "pin:");
	mvwprintw(loc->win, 4, 2, "pos:");
	loc->pos = inputSelect_init(&val.pos,y+4,x+9,1,255,3);	
	loc->pin = inputSelect_init(&val.pin,y+2,x+9,1,20,2);	

	return loc; 
}

void privFunc_refrechWindow(servo * servo){
		wrefresh(servo->win);	
		inputSelect_Actualiser(servo->pin);
		inputSelect_Actualiser(servo->pos);	
}

void  privFunc_destroy_win(WINDOW *local_win)
{	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}


