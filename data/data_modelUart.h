#ifndef uart_instance_include
#define uart_instance_include 
#include "data_struct.h"
typedef struct{
	int file;
	char * nom;
	int work;
} uart_instance;

uart_instance * init_uart(char *  portname );
int uart_sendNew(uart_instance * this, circular_vector * sequence);
void uart_sendModif(uart_instance * this, circular_vector * sequence,int indice);
void uart_sendJouer(uart_instance * this , int indice);
#endif
