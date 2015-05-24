#ifndef input_select	 
#define input_select
#include <ncurses.h>

typedef struct{
	unsigned long * val;
	char * tab;
	unsigned long max;
	unsigned long min;
	int byte;
	WINDOW* win;
} ncu_inputNumber;


ncu_inputNumber*

ncu_inputSelect_init(unsigned long * pval,int y,int x,unsigned long  min,unsigned long  max,int nbByte);	

void
ncu_inputSelect_modifInput(ncu_inputNumber * panel);

void
ncu_inputSelect_changeCible(ncu_inputNumber * panel , unsigned long * pval);

void
ncu_inputSelect_set(ncu_inputNumber * panel ,unsigned long pval);

void
ncu_inputSelect_Actualiser(ncu_inputNumber * enumvarpanel);

void 
ncu_inputSelect_dest(ncu_inputNumber * this);

#endif
