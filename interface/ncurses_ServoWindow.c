#include <ncurses.h>
#include <stdlib.h>
#include "ncurses_ServoWindow.h"
#include "ncurses_inputNumber.h"
#include "ncurses_CmdLine.h"
#include "../include/basic.h"



void 	pricFunc_refrechWindow( ncu_servo * servo);
ncu_servo * privFunc_new(int x , int y/*,t_mouv val*/);
void  	pricFunc_destroy_win(WINDOW *local_win);
void 	privFunc_refrechWindow(ncu_servo * servo);


ncu_list_servo* ncu_servoWindows_init(int posx , int posy/*,t_mouv * mouv*/){
	ncu_list_servo * locale = malloc(sizeof(ncu_list_servo));
	
	for(int i = 0;i<nb_servo;i++){
		locale->list[i] = *privFunc_new(posx+1+20*(i%4),posy+1+8*(i/4)/*,mouv[i]*/); 	
	}
	return locale;
}


void ncu_servoWindows_dest(ncu_servo * this){
	delwin(this->win);
	ncu_inputSelect_dest(this->pin);
	ncu_inputSelect_dest(this->pos);
	free(this);
}


void ncu_listServo_dest(ncu_list_servo * this){
	
	for(int i = 0; i<nb_servo ; i++)
		ncu_servoWindows_dest(&this->list[i]);
	free(this);
	return;	
}



void ncu_servoWindows_refrechWindows(ncu_list_servo * servos){
	int i = 0;
	for(i = 0 ; i<nb_servo;i++){
		privFunc_refrechWindow(&servos->list[i]);
	}
}

WINDOW * privFunc_create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);

	return local_win;
}


ncu_servo * privFunc_new(int x , int y/*,t_mouv val*/){
	
	ncu_servo * loc=malloc(sizeof(ncu_servo));
       	loc->win=privFunc_create_newwin(6,20,y,x);
	getbegyx(loc->win,y,x);
	loc->pos = ncu_inputSelect_init(NULL,y+4,x+9,1,255,3);	
	loc->pin = ncu_inputSelect_init(NULL,y+2,x+9,1,20,2);	

	return loc; 
}

void ncu_servoWindows_change(ncu_list_servo* l_servo,t_mouv * mouv){
	for(int i=0; i<nb_servo;i++)
	{
		ncu_inputSelect_changeCible(l_servo->list[i].pin,&mouv[i].pin);
		ncu_inputSelect_changeCible(l_servo->list[i].pos,&mouv[i].pos);
		ncu_inputSelect_Actualiser(l_servo->list[i].pos);
		ncu_inputSelect_Actualiser(l_servo->list[i].pin);
	}

}

void ncu_servoWindows_hide(ncu_list_servo * this){
	for(int i = 0; i<nb_servo;i++)
	{
		werase(this->list[i].win);
		wrefresh(this->list[i].win);
	}
	return;
}


void  ncu_servoWindows_show(ncu_list_servo * this){

	for(int i = 0; i<nb_servo;i++){
		box(this->list[i].win, 0 , 0);		
		wprintw(this->list[i].win," %s","test");
		mvwprintw(this->list[i].win, 2, 2, "pin:");
		mvwprintw(this->list[i].win, 4, 2, "pos:");
		wrefresh(this->list[i].win);
	}
	return ;
}


void privFunc_refrechWindow(ncu_servo * this){
		wrefresh(this->win);	
		ncu_inputSelect_Actualiser(this->pin);
		ncu_inputSelect_Actualiser(this->pos);	
}

void  privFunc_destroy_win(WINDOW *local_win)
{	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

void privFunc_select(ncu_list_servo* this){
	int a = A_REVERSE;
	wattron(this->list[this->actual].win,a);
	box(this->list[this->actual].win, 0 , 0);	
	mvwprintw(this->list[this->actual].win,0,0," %s","test");
	wattroff(this->list[this->actual].win,a);
	wrefresh(this->list[this->actual].win);
	ncu_inputSelect_Actualiser(this->list[this->actual].pos);
	ncu_inputSelect_Actualiser(this->list[this->actual].pin);
}

void privFunc_deselect(ncu_list_servo*this){
	box(this->list[this->actual].win, 0 , 0);		
	mvwprintw(this->list[this->actual].win,0,0," %s","test");
	wrefresh(this->list[this->actual].win);

	ncu_inputSelect_Actualiser(this->list[this->actual].pin);
	ncu_inputSelect_Actualiser(this->list[this->actual].pos);
}

int ncu_servoWindows_action(ncu_list_servo* this,ncu_cmdLine * cmda){
	privFunc_select(this);
	int ch = ncu_cmd_getCh(cmda);
	
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
				ncu_inputSelect_modifInput(this->list[this->actual].pin);

				break;
			case 'm':
				ncu_inputSelect_modifInput(this->list[this->actual].pos);
				break;
		}
		return 1;
}
