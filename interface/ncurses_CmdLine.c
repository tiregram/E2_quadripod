#include <ncurses.h>
#include <stdlib.h>
#include "ncurses_CmdLine.h" 



cmd_line *  cmd_init(){
	cmd_line * this = malloc(sizeof(cmd_line));	
	
	int x,y;
	getmaxyx(stdscr,y,x);	
	this->win = newwin(1,x,y-1,0);
	mvwhline(this->win,0,0,' '|A_REVERSE,x);
	keypad(this->win, TRUE);		
	wattron(this->win,A_REVERSE);
	wrefresh(this->win);	
	return this;

}

void cmd_addfunction(cmd_line * this, void* command, char * mathString){
	if(this->nbOfFunction>=100){return;} 
	// déclare des fonction dans les void *
	// permet de les apeler quand une des chaine mathSting mathch
	// Exemeple la commande "send" execute la function send();
}


int cmd_getCh(cmd_line * this){
	return	wgetch(this->win);
}
