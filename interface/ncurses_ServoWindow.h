#ifndef servowindow 
#define servowindow
#include "../data/data_struct.h"
#include "ncurses_CmdLine.h"
typedef struct {
	struct input_panel* pos;
	struct input_panel* pin;
	WINDOW * win;
} ncu_servo;

typedef struct {
	ncu_servo list[8];
	int actual;		
} ncu_list_servo;

ncu_list_servo * servoWindows_init(int posx , int posy/*,t_mouv * mouv*/);
void servoWindows_refrechWindows( ncu_list_servo * servos);
void  servoWindows_change(ncu_list_servo* l_servo,t_mouv * mouv);
int servoWindows_action(ncu_list_servo*  , cmd_line * cmda);

void servoWindows_hide(ncu_list_servo * this);
void servoWindows_show(ncu_list_servo * this);
#endif
