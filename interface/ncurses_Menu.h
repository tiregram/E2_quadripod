#ifndef menu_n
#define menu_n
#include "ncurses_CmdLine.h"
typedef struct{
	WINDOW * win;
	char **  list;
	unsigned int nb_choix;
	unsigned int choix;

}ncu_menu_panel;



int 
ncu_menu_action(ncu_menu_panel * this,ncu_cmdLine * cmda);

ncu_menu_panel* 
ncu_menu_init(int startX, int startY, int sizeX,int  sizeY,char * * menu,unsigned int nb_choix);

void 
ncu_menu_dest(ncu_menu_panel * this);

void 
ncu_menu_refrech(ncu_menu_panel * this);
#endif
