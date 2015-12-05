#include "ncurses_inputNumber.h"
#include "ncurses_Interface.h"
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>
int privFunc_assignValeur(ncu_inputNumber* this,int ch);
void privFunc_changeByte(ncu_inputNumber* this, char ch,int nb);

void privFunc_selectedInput(ncu_inputNumber* this);
void privFunc_deselectedInput(ncu_inputNumber* this);

void privFunc_passArray_To_Char(ncu_inputNumber* this);
void privFunc_passChar_To_Array	(ncu_inputNumber* this);


ncu_inputNumber * ncu_inputSelect_init(unsigned long * pval,int y,int x,unsigned long  min,unsigned long  max,int nbByte){	
	ncu_inputNumber * this = malloc(sizeof(ncu_inputNumber));
	this->tab= malloc(sizeof(char)*nbByte);
	this->val=pval;
	this->min=min;
	this->max=max;		
	this->byte=nbByte;
	this->win = newwin(1, nbByte, y, x);
	if(pval != NULL){	
	ncu_inputSelect_set(this,*pval);	
	ncu_inputSelect_Actualiser(this);
	}
	return this;
}


void ncu_inputSelect_dest(ncu_inputNumber * this){
	delwin(this->win);
	free(this);
}

void ncu_inputSelect_Actualiser(ncu_inputNumber * this){
	int i = 0;
	char * tab = this->tab;
	for(i=0; i<this->byte; i++){
		mvwaddch( this->win,0,i,(tab[i]+48)| A_BOLD | A_UNDERLINE);
	}
	wrefresh(this->win);
	
}

void ncu_inputSelect_set(ncu_inputNumber * this ,unsigned long pval){
	if (pval<this->min) {
		*(this->val) =this->min;
	}
	else if (pval>this->max) {
		*(this->val) =this->max;
	}else {
		*(this->val) = pval;
	}

	privFunc_passChar_To_Array(this);
}

void ncu_inputSelect_modifInput(ncu_inputNumber * this){
	int exit = 1;
	int ch = '0';
	privFunc_selectedInput(this);
	wmove(this->win,0,0);
	while(exit){
		ch = wgetch(this->win);	
		if(ch>47 && ch<58){
			exit = privFunc_assignValeur(this,ch);
		}else 
		if(ch == 'q'){
			exit =0;	
		}else 
		if(ch==KEY_UP){
		
		}else
		if(ch==KEY_DOWN){
		
		}else
		if(ch==KEY_DOWN){
		
		}else 
		if(ch==KEY_DOWN){
		
		}



	}
	privFunc_deselectedInput(this);
}





int privFunc_assignValeur(ncu_inputNumber * this,int ch){
	int x,y;
	getyx(this->win,y,x);
	privFunc_changeByte(this,ch,x);	
	if(x+1==this->byte)
		return 0;		
	wmove(this->win,y,x+1);
	return 1;		

}


void 	privFunc_changeByte(ncu_inputNumber * this, char ch,int nb){
	this->tab[nb]=ch-48;
	privFunc_passArray_To_Char(this);


	waddch( this->win,(this->tab[nb]+48)| A_BOLD | A_UNDERLINE);
}


void 	privFunc_selectedInput(ncu_inputNumber * this){
	wattron(this->win,A_REVERSE);
	ncu_inputSelect_Actualiser(this);
}

void 	privFunc_deselectedInput(ncu_inputNumber *this){

	wattroff(this->win,A_REVERSE);
	ncu_inputSelect_Actualiser(this);
}

void 	ncu_inputSelect_changeCible(ncu_inputNumber * this , unsigned long * pval){
	this->val = pval;
	ncu_inputSelect_set(this,*pval);	
}



void 	privFunc_passArray_To_Char(ncu_inputNumber * this){
	int i;
	char *  tab = this->tab;
	char *  tabTemp = malloc(sizeof(char)* this->byte);
	for(i = 0; i<this->byte;i++)
		tabTemp[i]=tab[i]+48;
	
	ncu_inputSelect_set(this,atol(tabTemp));

	free(tabTemp);
		
}

void	privFunc_passChar_To_Array(ncu_inputNumber * this){

	int i;
	char *  tab = this->tab;
	for(i = 0; i<this->byte;i++)
		tab[i]=(int)((*this->val)/pow(10,this->byte-i-1))%10;	


}
