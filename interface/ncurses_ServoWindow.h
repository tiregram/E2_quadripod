#ifndef servowindow 
#define servowindow
#include "../data/data_struct.h"
#include "ncurses_CmdLine.h"
typedef struct {
	struct input_panel* pos;
	struct input_panel* pin;
	WINDOW * win;
} servo;

typedef struct {
	servo list[8];
	int actual;		
} list_servo;

list_servo * servoWindows_init(int posx , int posy,t_mouv * mouv);
void servoWindows_refrechWindows( list_servo * servos);
void  servoWindows_change(list_servo* l_servo,t_mouv * mouv);
int servoWindows_action(list_servo*  , cmd_line * cmda);
#endif
