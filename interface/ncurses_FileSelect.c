#include "ncurses_InputString.h"
#include "../data/data_modelFile.h"
#include "../data/data_modelUart.h"
#include <ncurses.h>
#include <stdlib.h>
#include "ncurses_FileSelect.h"




int ncu_fileSelect_acceptchar(char k);

ncu_fileSelect* ncu_fileSelect_init(int sizeX,int sizeY,int startX,int startY){
	ncu_fileSelect * this  = malloc(sizeof(ncu_fileSelect));	
	this->win = newwin(sizeY,sizeX,startY,startX);
	box(this->win,0,0);	
	this->input = ncu_inputString_init_NewString(startX+1,startY+2,sizeX-2);
	ncu_inputString_changeFunctionChar(this->input , &ncu_fileSelect_acceptchar );
	return this;
}

void ncu_fileSelect_createUart(ncu_fileSelect * this,ncu_cmdLine * cmdp){
	mvwprintw(this->win,1,getmaxx(this->win)/2-2,"UART");
	wrefresh(this->win);
	ncu_inputString_action(this->input,cmdp);
	this->uart = uart_init(this->input->tab);
		
}

void ncu_fileSelect_getFIle(ncu_fileSelect * this, ncu_cmdLine * cmdp,int opt){

	char name[30];	
	char dest[30];

	mvwprintw(this->win,1,getmaxx(this->win)/2-2,"NAME");
	mvwprintw(this->win,3,getmaxx(this->win)/2-2,"DEST");
	wrefresh(this->win);
	
	mvwin(this->input->win,getbegy(this->win)+2,getbegx(this->win)+1);
	ncu_inputString_changeCible(this->input,name,30);
	ncu_inputString_clean_string(this->input);
	ncu_inputString_changeFunctionChar(this->input,NULL);
	ncu_inputString_action(this->input,cmdp);


	mvwin(this->input->win,getbegy(this->win)+4,getbegx(this->win)+1);
	ncu_inputString_changeCible(this->input,dest,30);
	ncu_inputString_clean_string(this->input);
	ncu_inputString_changeFunctionChar(this->input,&ncu_fileSelect_acceptchar);
	ncu_inputString_action(this->input,cmdp);
	
	this->file = file_init(name,dest,opt);
	


}

void ncu_fileSelect_free(ncu_fileSelect * this){
	delwin(this->win);
	free(this);	
}

int ncu_fileSelect_acceptchar(char k){
	return ((k>='A'&& k<='Z')||
		(k>='a'&& k<='z')||
		(k>='0'&& k<='9')||
		(k=='/')||
		(k=='-')||
		(k=='_')||
		(k=='.')
		);
}



