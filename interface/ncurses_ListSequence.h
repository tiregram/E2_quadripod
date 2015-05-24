#ifndef listSequence
#define listSequence
#include <ncurses.h>
#include "../data/data_Sequence.h"
#include "ncurses_CmdLine.h"
#include "ncurses_InputString.h"

typedef struct{
	WINDOW * win;
	list_sequence * seq;
	ncu_inputString * inpStr;		
}ncu_sequence;



ncu_sequence * ncu_sequence_init(list_sequence * listSeq,int startX, int startY,int sizeX,int sizeY);

int 
ncu_sequence_action(ncu_sequence * this,ncu_cmdLine * cmda);

void  
ncu_sequence_new_elem(ncu_sequence * this,ncu_cmdLine * cmda);

void  
ncu_sequence_del(ncu_sequence * this);

void 
ncu_sequence_refrech(ncu_sequence * this);

void 
ncu_sequence_dest(ncu_sequence * this);
#endif
