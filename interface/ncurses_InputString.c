#include "ncurses_InputString.h"
#include "ncurses_CmdLine.h"
#include <ncurses.h>
#include <stdlib.h>

inputString * inputString_init(int startX,int startY,int sizeX){
	inputString* this =  malloc(sizeof(inputString));
	this->win = newwin(1,sizeX,startY,startX); 
	this->sizeTab = sizeX;
	this->option = 0;//no option 
	inputString_changeFunctionChar(this,NULL);
	return this;
}



inputString * inputString_init_NewString(int startX,int startY,int sizeOfString){
	inputString * this = inputString_init(startX,startY,sizeOfString);
	this->tab = malloc(sizeof(char)*sizeOfString);
	for(int i=0;i<this->sizeTab;i++){
		this->tab[i]= ' ';
	}
	return this;
}


inputString * inputString_init_justPointer(int startX,int startY,char * pointOn,int size){
	inputString * this = inputString_init(startX,startY,size);
	this->tab = pointOn;
	return this;

}
void inputString_changeCible(inputString * this, char * pointOn, int size){
	this->tab = pointOn;
	this->sizeTab = size;
}

void inputString_clean_string(inputString * this){

	for(int i = 0;i<this->sizeTab;i++){
		this->tab[i]=' ';	
	
	}	

}





void inputString_select(inputString * this){
	for(int i = 0; i<this->sizeTab;i++){

		mvwaddch(this->win,0,i,this->tab[i]|A_REVERSE);
	}
	wrefresh(this->win);
}

void inputString_deselect(inputString * this){

	for(int i = 0; i<this->sizeTab;i++){
		mvwaddch(this->win,0,i,this->tab[i]);
	}
	wrefresh(this->win);
}



void inputString_mvCursor(inputString * this ,int at){
	if(at < 0)
		wmove(this->win,0,this->sizeTab-1);
	else 
	if(at < this->sizeTab)	
		wmove(this->win,0,at);
	else
		wmove(this->win,0,0);				
	

		wrefresh(this->win);
}
	

void inputString_setOneChar(inputString * this,int at , char theCaract ){
	this->tab[at] = theCaract;
	mvwaddch(this->win,0,at,this->tab[at]|A_REVERSE);
	inputString_mvCursor(this,at+1);
}


int inputString_action(inputString * this , cmd_line * cmda){
	inputString_select(this);
	int k;
	int i = 0;
	inputString_mvCursor(this,0);
	while(1){
		k = cmd_getCh(cmda);
	switch(k){
		
		case 127:
			inputString_setOneChar(this,i,' ');
				
			inputString_mvCursor(this,(i!=0)?--i:0);
			i =(i+this->sizeTab) % this->sizeTab;
			break;
		case '\n':
			this->tab[i]='\0';
			inputString_deselect(this);
			return 1;
		break;
		
		case KEY_LEFT:
		inputString_mvCursor(this,--i);
			i =(i+this->sizeTab) % this->sizeTab;
		break;
			
		case KEY_RIGHT:
			inputString_mvCursor(this,++i);
			i =(i+this->sizeTab) % this->sizeTab;
		break;

		default: 
		if((*(this->verifFuncChar))(k)){

			inputString_setOneChar(this,i++,k);	
			i =(i+this->sizeTab) % this->sizeTab;

		}

		break;	
			
	}
}		

}


int inputString_accept_only_aplhabet(char k){
	return ((k>='A'&& k<='Z')||(k>='a'&& k<='z'));
}

void inputString_changeFunctionChar(inputString* this ,int (*func)(char) ){
	if(func != NULL){
		this->verifFuncChar = func;
	}else {
		this->verifFuncChar = &inputString_accept_only_aplhabet;
	}
	
	}  

