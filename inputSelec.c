#include "inputSelec.h"
#include "ncurcesInterface.h"
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>

int assignValeur(struct input_panel * panel,int ch);
void selectedInput(struct input_panel * panel);
void	privFunc_passChar_To_Array(struct input_panel * panel);
void changeByte(struct input_panel * panel,unsigned char ch,int nb);
void deselectedInput(struct input_panel * panel);
struct input_panel * inputSelect_init(unsigned char * pval,int y,int x,int min,int max,int nbByte){	
	struct input_panel * locale=NULL;
	locale= malloc(sizeof(struct input_panel));
	locale->tab= malloc(sizeof(char)*nbByte);
	locale->val=pval;
	locale->min=min;
	locale->max=max;		
	locale->byte=nbByte;
	locale->pos = newwin(1, nbByte, y, x);
		
	inputSelect_set(locale,*pval);	
	privFunc_passChar_To_Array(locale);
	inputSelect_Actualiser(locale);
	return locale;
}

void inputSelect_Actualiser_recursive(struct input_panel * enumvarpanel ,int pval ,int byteNum){
	unsigned int var = pval / (int) pow(10,byteNum-1);
	mvwaddch( enumvarpanel->pos,0,enumvarpanel->byte-byteNum,(var+48)| A_BOLD | A_UNDERLINE);
	if(byteNum!=1){
		inputSelect_Actualiser_recursive( enumvarpanel ,pval-var*pow(10,byteNum-1),byteNum-1);
	}

}
void inputSelect_Actualiser(struct input_panel * enumvarpanel){
	inputSelect_Actualiser_recursive( enumvarpanel,*(enumvarpanel->val),enumvarpanel->byte );
	wrefresh(enumvarpanel->pos);	
}

void inputSelect_set(struct input_panel * panel ,unsigned char pval){
	if (pval<panel->min) {
		*(panel->val) = panel->min;
		return;
	}
	if (pval>panel->max) {
		*(panel->val) = panel->max;
		return;
	}
	*(panel->val) = pval;
}

void inputSelect_modifInput(struct input_panel * panel){
	int exit = 1;
	int ch = '0';
	selectedInput(panel);
	wmove(panel->pos,0,0);
	while(exit){
		ch = wgetch(panel->pos);	
		if((ch&0xFF)>47 && (ch&0xFF)<58){
			exit = assignValeur(panel,ch);						
		}
		if(ch == 'q'){
			exit =0;	
		}	


	}
	deselectedInput(panel);
}

int assignValeur(struct input_panel * panel,int ch){
	int x,y,nb;
	getyx(panel->pos,y,x);
	changeByte(panel,ch,panel->byte-x);		
	if(x+1==panel->byte)
		return 0;		
	wmove(panel->pos,y,x+1);
	return 1;		

}

void changeByte(struct input_panel * panel,unsigned char ch,int nb){
	unsigned int rang = (unsigned int ) pow(10,nb-1);
	unsigned char valeurDeLaCible = *(panel->val);
	unsigned char byteDi =(valeurDeLaCible/rang)%10;
	unsigned char newVal = valeurDeLaCible
		-byteDi * rang 
		+(ch-48)*rang; 

	inputSelect_set(panel , newVal);
	newVal = *panel->val;
	unsigned char var = (newVal/rang)%10;
	waddch( panel->pos,(var+48)| A_BOLD | A_UNDERLINE);
}


void selectedInput(struct input_panel * panel){
	wattron(panel->pos,A_REVERSE);
	inputSelect_Actualiser(panel);
}

void deselectedInput(struct input_panel * panel){
	wattroff(panel->pos,A_REVERSE);
	inputSelect_Actualiser(panel);
}

void inputSelect_changeCible(struct input_panel * panel , unsigned char * pval){
	panel->val = pval;
}



void	privFunc_passChar_To_Array(struct input_panel * panel){
	int i;
	unsigned char *  tab = panel->tab;
	for(i = 0; i<panel->byte;i++)
		tab[i]=(*(panel->val)/(int)pow(10,panel->byte-i-1))%10;	



}
