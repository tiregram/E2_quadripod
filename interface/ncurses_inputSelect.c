#include "ncurses_inputSelect.h"
#include "ncurses_Interface.h"
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>
int privFunc_assignValeur(struct input_panel * panel,int ch);
void privFunc_changeByte(struct input_panel * panel, char ch,int nb);

void privFunc_selectedInput(struct input_panel * panel);
void privFunc_deselectedInput(struct input_panel * panel);

void privFunc_passArray_To_Char(struct input_panel * panel);
void privFunc_passChar_To_Array(struct input_panel * panel);


struct input_panel * inputSelect_init(unsigned long * pval,int y,int x,unsigned long  min,unsigned long  max,int nbByte){	
	struct input_panel * locale = malloc(sizeof(struct input_panel));
	locale->tab= malloc(sizeof(char)*nbByte);
	locale->val=pval;
	locale->min=min;
	locale->max=max;		
	locale->byte=nbByte;
	locale->pos = newwin(1, nbByte, y, x);
	if(pval != NULL){	
	inputSelect_set(locale,*pval);	
	inputSelect_Actualiser(locale);
	}
	return locale;
}


void inputSelect_Actualiser(struct input_panel * panel){
	int i = 0;
	char * tab = panel->tab;
	for(i=0; i<panel->byte; i++){
		mvwaddch( panel->pos,0,i,(tab[i]+48)| A_BOLD | A_UNDERLINE);
	}
	wrefresh(panel->pos);
	
}

void inputSelect_set(struct input_panel * panel ,unsigned long pval){
	if (pval<panel->min) {
		*(panel->val) = panel->min;
	}
	else if (pval>panel->max) {
		*(panel->val) = panel->max;
	}else {
		*(panel->val) = pval;
	}

	privFunc_passChar_To_Array(panel);
}

void inputSelect_modifInput(struct input_panel * panel){
	int exit = 1;
	int ch = '0';
	privFunc_selectedInput(panel);
	wmove(panel->pos,0,0);
	while(exit){
		ch = wgetch(panel->pos);	
		if(ch>47 && ch<58){
			exit = privFunc_assignValeur(panel,ch);						
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
	privFunc_deselectedInput(panel);
}





int privFunc_assignValeur(struct input_panel * panel,int ch){
	int x,y;
	getyx(panel->pos,y,x);
	privFunc_changeByte(panel,ch,x);	
	if(x+1==panel->byte)
		return 0;		
	wmove(panel->pos,y,x+1);
	return 1;		

}


void 	privFunc_changeByte(struct input_panel * panel, char ch,int nb){
	panel->tab[nb]=ch-48;
	privFunc_passArray_To_Char(panel);


	waddch( panel->pos,(panel->tab[nb]+48)| A_BOLD | A_UNDERLINE);
}


void 	privFunc_selectedInput(struct input_panel * panel){
	wattron(panel->pos,A_REVERSE);
	inputSelect_Actualiser(panel);
}

void 	privFunc_deselectedInput(struct input_panel * panel){
	wattroff(panel->pos,A_REVERSE);
	inputSelect_Actualiser(panel);
}

void 	inputSelect_changeCible(struct input_panel * panel , unsigned long * pval){
	panel->val = pval;
	inputSelect_set(panel,*pval);	
}



void 	privFunc_passArray_To_Char(struct input_panel * panel){
	int i;
	char *  tab = panel->tab;
	char *  tabTemp = malloc(sizeof(char)*panel->byte);
	for(i = 0; i<panel->byte;i++)
		tabTemp[i]=tab[i]+48;
	
	inputSelect_set(panel,atol(tabTemp));

	free(tabTemp);
		
}

void	privFunc_passChar_To_Array(struct input_panel * panel){

	int i;
	char *  tab = panel->tab;
	for(i = 0; i<panel->byte;i++)
		tab[i]=(int)((*panel->val)/pow(10,panel->byte-i-1))%10;	


}
