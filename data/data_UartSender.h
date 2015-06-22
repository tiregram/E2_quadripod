
#ifndef DATA_UARTSENDER_INCLUDE
#define  DATA_UARTSENDER_INCLUDE


#include "data_Sequence.h"
#include "data_modelUart.h"
#include "../include/structForCPP.h"






data_UartSender data_UartSender_Init(sequenc seq);
void data_UartSender_loadAll(data_UartSender * this,list_sequence* sequences ,MessBox* mess);
data_UartSender * data_UartSender_passModelToSender(uart_struct * this);

void data_UartSender_setToCurrent(data_UartSender * this,int rang,list_sequence * sequences);

void data_UartSender_set(data_UartSender * this,int rang,sequenc * sequence);








#endif
