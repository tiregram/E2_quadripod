#include <ncurses.h>
struct input_panel{
	unsigned long * val;
	char * tab;
	unsigned long max;
	unsigned long min;
	int byte;
	WINDOW* pos;
};

struct input_panel* inputSelect_init(unsigned long * pval,int y,int x,unsigned long  min,unsigned long  max,int nbByte);	
void 	inputSelect_modifInput(struct input_panel * panel);
void 	inputSelect_changeCible(struct input_panel * panel , unsigned long * pval);
void 	inputSelect_set(struct input_panel * panel ,unsigned long pval);
void 	inputSelect_Actualiser(struct input_panel * enumvarpanel);
