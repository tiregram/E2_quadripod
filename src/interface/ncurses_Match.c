/*
 * ncurses_Match.c
 *
 *  Created on: 23 juin 2015
 *      Author: ruhtra
 */
#include "ncurses_Match.h"
#include "../data/data_UartSender.h"
#include <stdlib.h>
#include "../include/global.h"
#include "../include/structForCPP.h"
#include "../data/data_UartSender.h"
#include "ncurses_ListSequence.h"
#include "ncurses_CmdLine.h"


ncu_match *  ncu_match_init(data_UartSender * sende){


	ncu_match * this  = malloc(sizeof(ncu_match));
	this->win = newwin(30,20,2,30);
	this->send = sende;
	this->select =0;
	box(this->win,0,0);

	return this;

}

void
ncu_match_refrechlist(ncu_match* this){

for(int i= 0 ; i<NUMBER_OF_ACTION ; i++){
	if(this->select == i )
					wattron(this->win,A_REVERSE);
mvwprintw(this->win,i+1,2,"a-%10s|   %2i",SAYa[i],this->send->listOfAction[i]);
if(this->select == i )
				wattroff(this->win,A_REVERSE);

}
wrefresh(this->win);

}

int ncu_match_action(ncu_match* this,ncu_cmdLine * cmds , ncu_sequence * seqs){
	while(1){
	ncu_match_refrechlist(this);

	int action = ncu_cmd_getCh(cmds);

	switch(action){
		case 'q':

			return 0;

			break;
		case KEY_UP:
			this->select = (this->select-1+NUMBER_OF_ACTION)%NUMBER_OF_ACTION;

			break;
		case KEY_DOWN:
			this->select = (this->select+1+NUMBER_OF_ACTION)%NUMBER_OF_ACTION;
			break;

		case 'e':
			ncu_sequence_action(seqs,cmds);
			this->send->listOfAction[this->select]=seqs->seq->curent->num;

			break;
	}
	}
	return 1;



}

void
ncu_match_dest(ncu_match * this){
	free(this);

}

