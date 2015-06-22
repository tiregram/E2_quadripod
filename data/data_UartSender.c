/*
 * data_UartSender.c
 *
 *  Created on: 21 juin 2015
 *      Author: ruhtra
 */
#include "../interface/ncurses_MessageBox.h"
#include "data_UartSender.h"
#include "data_modelUart.h"
#include "stdlib.h"


data_UartSender * data_UartSender_passModelToSender(uart_struct * this){

	data_UartSender* ret = malloc(sizeof(data_UartSender));
	ret->file = this->file;
	ret->ping = &uart_ping_cpp;
	ret->play = &uart_sendJouer_cpp;
	ret->listOfAction =  malloc(NUMBER_OF_ACTION*sizeof(int));
	return ret;
}


void data_UartSender_setToCurrent(data_UartSender * this,int rang,list_sequence * sequences){
	data_UartSender_set(this,rang,sequences->curent);

}

void data_UartSender_set(data_UartSender * this,int rang,sequenc * sequence){
	this->listOfAction[rang] = sequence->num;
}

void data_UartSender_loadAll(data_UartSender * this,list_sequence* sequences ,MessBox* mess){
	sequenc * loc;
	for(int i=0; i<NUMBER_OF_ACTION ;i++){
		loc=sequence_get(sequences,this->listOfAction[i]);
		uart_sendModifBasic(this->file,loc,mess);
	}
}





