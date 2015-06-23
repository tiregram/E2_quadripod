#ifndef uart_instance_include
#define uart_instance_include 
#include "data_Sequence.h"
#include "../interface/ncurses_MessageBox.h"
typedef struct{
	int file;
	char * nom;
	int work;
} uart_struct;





uart_struct * uart_init(char *  portname );
int uart_sendNew(uart_struct * this, list_sequence * sequence,MessBox * mess);
int uart_sendModif(uart_struct * this, list_sequence* sequence,MessBox * mess);
int uart_sendJouer(uart_struct * this , list_sequence * sequence,MessBox * mess);
int uart_ping_cpp(int file);
int uart_sendModifBasic(int file,sequenc * sequence,MessBox * mess);
int uart_ping(uart_struct * this);
int uart_sendJouer_cpp(int file ,char num);
int uart_sendSet(uart_struct * this ,unsigned long pos ,unsigned long pin);

#endif
