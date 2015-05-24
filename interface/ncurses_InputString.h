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
}ncu_inputString;

ncu_inputString * ncu_inputString_init(int startX,int startY,int sizeX);
void inputString_refresh(ncu_inputString * this);
ncu_inputString * ncu_inputString_init_NewString(int startX,int startY,int sizeOfString);
void ncu_inputString_select(ncu_inputString * this);
int ncu_inputString_action(ncu_inputString * this, cmd_line * cmda);
void ncu_inputString_changeCible(ncu_inputString * this, char * pointOn, int size);
void ncu_inputString_changeFunctionChar(ncu_inputString* this ,int (*func)(char) );
void ncu_inputString_clean_string(ncu_inputString * this);
void ncu_inputString_dest(ncu_inputString * this);


#endif
