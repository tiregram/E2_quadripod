#include <ncurses.h>
struct input_panel{
	unsigned char *  val;
	unsigned char * tab;
	int max;
	int min;
	int byte;
	WINDOW* pos;
};

void inputSelect_Actualiser(struct input_panel * enumvarpanel);
struct input_panel* inputSelect_init(unsigned char * pval,int y,int x,int min,int max,int nbByte);	
void inputSelect_modifInput(struct input_panel * panel);
void inputSelect_changeCible(struct input_panel * panel , unsigned char * pval);
void inputSelect_set(struct input_panel * panel ,unsigned char pval);
