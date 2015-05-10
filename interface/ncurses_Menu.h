#ifndef menu_n
#define menu_n
#include "ncurses_CmdLine.h"
typedef struct{
	WINDOW * win;
	char **  list;
	unsigned int nb_choix;
	unsigned int choix;

}menu_panel;



int menu_action(menu_panel * this,cmd_line * cmda);
menu_panel* menu_init(int startX, int startY, int sizeX,int  sizeY,char * * menu,unsigned int nb_choix);
void menu_refrech(menu_panel * this);
#endif
