#include <ncurses.h>
#include "ncurses_Menu.h"
#include <stdlib.h>
#include "ncurses_CmdLine.h"
#include "../data/data_ListMenu.h"

ncu_menu_panel* ncu_menu_init(int startX, int startY, int sizeX,int  sizeY,char * *menu,unsigned int nb_choix){
	
	ncu_menu_panel * this  = malloc(sizeof(ncu_menu_panel));
	this->win = newwin(sizeY,sizeX,startY,startX);
	box(this->win,0,0);
	
	this->nb_choix= nb_choix;
	this->choix = 0;
	this->list=menu;
	return this;	
}
void ncu_menu_refrech(ncu_menu_panel * this){
	int sizeX;
	sizeX = getmaxx(this->win);

	for(unsigned int i =0 ; i<this->nb_choix;i++){
		mvwprintw(this->win,i+1,2,"%1i >",i+1);
		mvwprintw(this->win,i+1,6,"%s",this->list[i]);
		mvwprintw(this->win,i+1,sizeX-3,"<");
			
	}
	redrawwin(this->win);	
}


void ncu_menu_selected(ncu_menu_panel * this){
	wattron(this->win,A_REVERSE);
	mvwprintw(this->win,this->choix+1,6,"%s",this->list[this->choix]);
	wattroff(this->win,A_REVERSE);
	wrefresh(this->win);
}

void  ncu_menu_deselected(ncu_menu_panel * this){

	mvwprintw(this->win,this->choix+1,6,"%s",this->list[this->choix]);
}



//int menu_action(ncu_menu_panel * this, cmd_line * cmda){
int ncu_menu_action(ncu_menu_panel * this,ncu_cmdLine * cmda){	
	while(1){
	ncu_menu_selected(this);
	int ch =ncu_cmd_getCh(cmda);
	switch(ch){
	case 'q':
		return -1;
		break;
	case KEY_UP:
		ncu_menu_deselected(this);
		this->choix -= 1 ;
		break;
	case KEY_DOWN:
		ncu_menu_deselected(this);
		this->choix += 1 ;
		break;
	case '\n':
		return this->choix;		
		break;

	case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
		ncu_menu_deselected(this);
		this->choix=ch;	
		break;
	}
	this->choix = (this->choix+this->nb_choix)%this->nb_choix;
	ncu_menu_selected(this);
	}

}

void ncu_menu_dest(ncu_menu_panel * this){
	delwin(this->win);
	if(this->list != NULL){
		menu_list_free(this->list);	
	}	
	free(this);
}	
