#ifndef data_UartSender_include
#define data_UartSender_include


#define SAY_ON			0
#define SAY_AVANCE 		1
#define SAY_RECULE 		2
#define SAY_RIGHT 		3
#define SAY_LEFT 		4

#define SAY_MOUV_1 		5
#define SAY_MOUV_2 		6
#define SAY_MOUV_3 		7
#define SAY_MOUV_4 		8

#define NUMBER_OF_ACTION 9




typedef struct{
	int file;
	int (*ping)(int);
	int (*play)(int,char);
	int *listOfAction;
}data_UartSender;


#endif
