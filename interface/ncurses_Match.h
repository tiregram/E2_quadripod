#ifndef ncu_match_include
#define ncu_match_include

#include "ncurses_CmdLine.h"
#include "../data/data_modelUart.h"
#include "../data/data_UartSender.h"
#include "ncurses_ListSequence.h"

typedef struct {
	WINDOW * win;
	data_UartSender * send;
	int select;
}ncu_match ;


ncu_match* ncu_match_init(data_UartSender * sende);

void
ncu_match_refrechlist(ncu_match* this);


int ncu_match_action(ncu_match* this,ncu_cmdLine * cmd ,ncu_sequence * seqs );


void
ncu_match_dest(ncu_match * this);




#endif
