#ifndef interface 
#define interface 
#include "../data/data_struct.h"
void printMessage(char * mess);
void interface_init();
void createServoWindow(char* description ,t_mouv *);
void changeServoWindows(char charParams);
void refrechWindows();
int interface_action();
void changeServoWindow(int direction);
#endif
