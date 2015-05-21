#ifndef input_char_define
#define input_char_define
#include <ncurses.h>
#include "ncurses_CmdLine.h"
typedef struct{
	char * tab;
	int sizeTab;
	int option;//option pas encore definie mais il y en a 32 de dispo dans un int
	//on peuxm etere
	WINDOW* win;
	int (*verifFuncChar)(char); 
} inputString;


inputString * inputString_init(int startX,int startY,int sizeX);
void inputString_refresh(inputString * this);
inputString * inputString_init_NewString(int startX,int startY,int sizeOfString);

void inputString_select(inputString * this);
int inputString_action(inputString * this, cmd_line * cmda);


void inputString_changeCible(inputString * this, char * pointOn, int size);


void inputString_changeFunctionChar(inputString* this ,int (*func)(char) );


void inputString_clean_string(inputString * this);



#endif
