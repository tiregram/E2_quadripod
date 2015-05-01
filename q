#include <stdlib.h>
#include <ncurses.h>
#include "../data/data_struct.h"
#include "ncurses_Frame.h"


ncu_frame * frame_init(int x,int y,circular_vector* data){
	ncu_frame * this = malloc(sizeof(ncu_frame));
	this->con = newwin(25,50, y, x);
	box(this->con, 0 , 0);	
	wprintw(this->con,"Frame");
	mvwprintw(this->con,2,2,"nb of Frame %i",0);
	mvwhline(this->con,4 ,1,' '|A_REVERSE,48);
	mvwhline(this->con,23 ,1,' '|A_REVERSE,48);
	wrefresh(this->con);

	this->scrool = newwin(20,48,y+5,x+1);
	
	this->data = data;
}
void renderOneMouv(WINDOW * win){
wprintw:w²


}


void refrechlist(ncu_frame* this){	
	struct 	circular_vector_mouv*  stop = this->data->first;
	struct circular_vector_mouv* i = stop->next;
	
	while(i!=stop)
	{

	
	
	}	
	


}




