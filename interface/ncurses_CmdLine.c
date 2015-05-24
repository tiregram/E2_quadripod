#include <ncurses.h>
#include <stdlib.h>
#include "ncurses_CmdLine.h" 



ncu_cmdLine *  ncu_cmd_init(){
	ncu_cmdLine * this = malloc(sizeof(ncu_cmdLine));	
	
	int x,y;
	getmaxyx(stdscr,y,x);	
	this->win = newwin(1,x,y-1,0);
	mvwhline(this->win,0,0,' '|A_REVERSE,x);
	keypad(this->win, TRUE);		
	wattron(this->win,A_REVERSE);
	wrefresh(this->win);	
	return this;

}

/*
void ncu_cmd_addfunction(cmd_line * this, void* command, char * mathString){

	if(this->nbOfFunction>=100){return;} 
	// déclare des fonction dans les void *
	// permet de les apeler quand une des chaine mathSting mathch
	// Exemeple la commande "send" execute la function send();
}
i*/

int ncu_cmd_getCh(ncu_cmdLine * this){
	return	wgetch(this->win);
}
