#ifndef uart_instance_include
#define uart_instance_include 
#include "data_struct.h"
typedef struct{
	int file;
	char * nom;
	int work;
} uart_struct;

uart_struct * uart_init(char *  portname );
int uart_sendNew(uart_struct * this, circular_vector * sequence);
void uart_sendModif(uart_struct * this, circular_vector * sequence,int indice);
void uart_sendJouer(uart_struct * this , int indice);
#endif
