#include <stdlib.h>
#include <ncurses.h>
#include "ncurses_ListSequence.h"
#include "../data/data_Sequence.h"
#include "ncurses_CmdLine.h"
#include "ncurses_InputString.h"


void ncu_sequence_refrech(ncu_sequence * this);

ncu_sequence * ncu_sequence_init(list_sequence * listSeq,int startX, int startY,int sizeX,int sizeY){
	ncu_sequence * this = malloc(sizeof(ncu_sequence));
	this->win = newwin(sizeY,sizeX,startY,startX);
	this->seq = listSeq;
	box(this->win,0,0);
	ncu_sequence_refrech(this);


	this->inpStr = inputString_init(startX,startY+sizeY-1,10); 
	return this;
}


void ncu_sequence_refrech(ncu_sequence * this){ 
	werase(this->win);
	box(this->win,0,0);
	sequenc * a = this->seq->first;
	wattron(this->win,A_UNDERLINE);
	mvwprintw(this->win,1,1,"%11s|%2s|S","name","n°");
	wattroff(this->win,A_UNDERLINE);
	if(this->seq->first != NULL){	
	for(unsigned int i = 0; i<this->seq->nb_total;i++){
		
		if(this->seq->curent == a )
			wattron(this->win,A_REVERSE);

		mvwprintw(this->win,i+2,1,">%10s|%2i|%c",a->name,a->num,(a->send==1)?'x':' ');
			
		if(this->seq->curent == a )
			wattroff(this->win,A_REVERSE);


		a = a->next;
	}	
	}
	wrefresh(this->win);
}


void ncu_sequence_deplacement(ncu_sequence * this ,char sens){
		
}

int ncu_sequence_action(ncu_sequence * this, cmd_line * cmda){

	int ch = ' ';
	while(1){
	 ch = cmd_getCh(cmda);
	switch(ch){
		case KEY_DOWN:
			sequence_deplacement(this->seq,SEQUENCE_AVANT);	
			break;
		case KEY_UP:
			sequence_deplacement(this->seq,SEQUENCE_APRES);	
			break;
		case '\n':
			return 1;
			break;
		case 'q'://quit
			return -1;
			break;
		case 'r'://refrech
			
			break;
		case 'n'://new
		
		break;
			break;
		case 's'://send
			break;

	}
	ncu_sequence_refrech(this);}

}

void  ncu_sequence_new_elem(ncu_sequence * this,cmd_line * cmda){
	int x,y;
	getbegyx(this->win,y,x);


	char * name = malloc(sizeof(char)*11);
	for(int i = 0;i<11;i++)
		name[i]= ' ';
	name[10]='\0';
	inputString_changeCible(this->inpStr,name,10);
	mvwin(this->inpStr->win,y+this->seq->nb_total+2,x+2);
	inputString_action(this->inpStr,cmda);	
			
	sequence_add(this->seq,SEQUENCE_AT_END,name,10,NULL);	
	
	ncu_sequence_refrech(this);
}


 
void  ncu_sequence_del(ncu_sequence * this,cmd_line * cmda){
	if(this->seq->first == NULL)
		return;


	sequence_del(this->seq);
	ncu_sequence_refrech(this);	

}
