#include <ncurses.h>
#include <stdlib.h>
#include "ncurses_ServoWindow.h"
#include "ncurses_inputSelect.h"
#include "ncurses_CmdLine.h"
#include "../include/basic.h"



void 	pricFunc_refrechWindow( servo * servo);
servo * privFunc_new(int x , int y,t_mouv val);
void  	pricFunc_destroy_win(WINDOW *local_win);
void 	privFunc_refrechWindow(servo * servo);


list_servo* servoWindows_init(int posx , int posy,t_mouv * mouv){
	list_servo * locale = malloc(sizeof(list_servo));
	for(int i = 0;i<nb_servo;i++){
		locale->list[i] = *privFunc_new(posx+1+20*(i%4),posy+1+8*(i/4),mouv[i]); 	
	}
	return locale;
}

void servoWindows_refrechWindows(list_servo * servos){
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
	wprintw(loc->win," %s","test");
	mvwprintw(loc->win, 2, 2, "pin:");
	mvwprintw(loc->win, 4, 2, "pos:");
	loc->pos = inputSelect_init(&val.pos,y+4,x+9,1,255,3);	
	loc->pin = inputSelect_init(&val.pin,y+2,x+9,1,20,2);	

	return loc; 
}

void  servoWindows_change(list_servo* l_servo,t_mouv * mouv){
	for(int i=0; i<nb_servo;i++)
	{
		inputSelect_changeCible(l_servo->list[i].pin,&mouv[i].pin);
		inputSelect_changeCible(l_servo->list[i].pos,&mouv[i].pos);
		inputSelect_Actualiser(l_servo->list[i].pos);
		inputSelect_Actualiser(l_servo->list[i].pin);
	}

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

void privFunc_select(list_servo*this){
	int a = A_REVERSE;
	wattron(this->list[this->actual].win,a);
	box(this->list[this->actual].win, 0 , 0);	
	mvwprintw(this->list[this->actual].win,0,0," %s","test");
	wattroff(this->list[this->actual].win,a);
	wrefresh(this->list[this->actual].win);
	inputSelect_Actualiser(this->list[this->actual].pos);
	inputSelect_Actualiser(this->list[this->actual].pin);
}

void privFunc_deselect(list_servo*this){
	box(this->list[this->actual].win, 0 , 0);		
	mvwprintw(this->list[this->actual].win,0,0," %s","test");
	wrefresh(this->list[this->actual].win);

	inputSelect_Actualiser(this->list[this->actual].pin);
	inputSelect_Actualiser(this->list[this->actual].pos);
}

int servoWindows_action(list_servo* this,cmd_line * cmda){
	privFunc_select(this);
	int ch = cmd_getCh(cmda);
	
		switch(ch){
			case KEY_RIGHT:
				privFunc_deselect(this);
				this->actual=(this->actual+1+nb_servo)%nb_servo;
				privFunc_select(this);	
				break;
			case KEY_LEFT:
				privFunc_deselect(this);
				this->actual=(this->actual-1+nb_servo)%nb_servo;
				privFunc_select(this);	
				
				break;
			case 'q':

				privFunc_deselect(this);
				return 0;
				break;
			case 'p':
				inputSelect_modifInput(this->list[this->actual].pin);

				break;
			case 'm':
				inputSelect_modifInput(this->list[this->actual].pos);
				break;
		}
		return 1;
}
