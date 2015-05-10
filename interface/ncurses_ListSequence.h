#ifndef listSequence
#define listSequence
#include <ncurses.h>
#include "../data/data_Sequence.h"
#include "ncurses_CmdLine.h"
#include "ncurses_InputString.h"

typedef struct{
	WINDOW * win;
	list_sequence * seq;
	inputString * inpStr;		
}ncu_sequence;



ncu_sequence * ncu_sequence_init(list_sequence * listSeq,int startX, int startY,int sizeX,int sizeY);

int ncu_sequence_action(ncu_sequence * this, cmd_line * cmda);

void  ncu_sequence_new_elem(ncu_sequence * this,cmd_line * cmda);

void  ncu_sequence_del(ncu_sequence * this,cmd_line * cmda);


#endif
