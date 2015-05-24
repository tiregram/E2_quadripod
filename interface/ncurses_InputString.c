#include "ncurses_InputString.h"
#include "ncurses_CmdLine.h"
#include <ncurses.h>
#include <stdlib.h>

ncu_inputString * inputString_init(int startX,int startY,int sizeX){
	ncu_inputString* this =  malloc(sizeof(ncu_inputString));
	this->win = newwin(1,sizeX,startY,startX); 
	this->sizeTab = sizeX;
	this->option = 0;//no option 
	ncu_inputString_changeFunctionChar(this,NULL);
	return this;
}



ncu_inputString * inputString_init_NewString(int startX,int startY,int sizeOfString){
	ncu_inputString * this = inputString_init(startX,startY,sizeOfString);
	this->tab = malloc(sizeof(char)*sizeOfString);
	for(int i=0;i<this->sizeTab;i++){
		this->tab[i]= ' ';
	}
	return this;
}


ncu_inputString * inputString_init_justPointer(int startX,int startY,char * pointOn,int size){
	ncu_inputString * this = inputString_init(startX,startY,size);
	this->tab = pointOn;
	return this;

}
void inputString_changeCible(ncu_inputString * this, char * pointOn, int size){
	this->tab = pointOn;
	this->sizeTab = size;
}

void ncu_inputString_clean_string(ncu_inputString * this){

	for(int i = 0;i<this->sizeTab;i++){
		this->tab[i]=' ';	
	
	}	

}





void ncu_inputString_select(ncu_inputString * this){
	for(int i = 0; i<this->sizeTab;i++){

		mvwaddch(this->win,0,i,this->tab[i]|A_REVERSE);
	}
	wrefresh(this->win);
}

void ncu_inputString_deselect(ncu_inputString * this){

	for(int i = 0; i<this->sizeTab;i++){
		mvwaddch(this->win,0,i,this->tab[i]);
	}
	wrefresh(this->win);
}



void ncu_inputString_mvCursor(ncu_inputString * this ,int at){
	if(at < 0)
		wmove(this->win,0,this->sizeTab-1);
	else 
	if(at < this->sizeTab)	
		wmove(this->win,0,at);
	else
		wmove(this->win,0,0);				
	

		wrefresh(this->win);
}
	

void ncu_inputString_setOneChar(ncu_inputString * this,int at , char theCaract ){
	this->tab[at] = theCaract;
	mvwaddch(this->win,0,at,this->tab[at]|A_REVERSE);
	ncu_inputString_mvCursor(this,at+1);
}


int ncu_inputString_action(ncu_inputString * this , cmd_line * cmda){
	ncu_inputString_select(this);
	int k;
	int i = 0;
	ncu_inputString_mvCursor(this,0);
	while(1){
		k = cmd_getCh(cmda);
	switch(k){
		
		case 127:
			ncu_inputString_setOneChar(this,i,' ');
				
			inputString_mvCursor(this,(i!=0)?--i:0);
			i =(i+this->sizeTab) % this->sizeTab;
			break;
		case '\n':
			this->tab[i]='\0';
			ncu_inputString_deselect(this);
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

			ncu_inputString_setOneChar(this,i++,k);	
			i =(i+this->sizeTab) % this->sizeTab;

		}

		break;	
			
	}
}		

}


int ncu_inputString_accept_only_aplhabet(char k){
	return ((k>='A'&& k<='Z')||(k>='a'&& k<='z'));
}

void ncu_inputString_changeFunctionChar(ncu_inputString* this ,int (*func)(char) ){
	if(func != NULL){
		this->verifFuncChar = func;
	}else {
		this->verifFuncChar = &ncu_inputString_accept_only_aplhabet;
	}
	
} 

void ncu_inputString_dest(ncu_inputString * this){
		delwin(this->win);	
		free(this->tab);
		free(this);
}

