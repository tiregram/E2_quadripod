#ifndef servowindow 
#define servowindow
#include "../data/data_struct.h"
#include "ncurses_CmdLine.h"
#include "ncurses_inputNumber.h"

typedef struct {
	 ncu_inputNumber* pos;
	 ncu_inputNumber* pin;
	WINDOW * win;
} ncu_servo;

typedef struct {
	ncu_servo list[8];
	int actual;		
} ncu_list_servo;

ncu_list_servo *
ncu_servoWindows_init(int posx , int posy);

void 
ncu_servoWindows_refrechWindows( ncu_list_servo * servos);

void 
ncu_servoWindows_change(ncu_list_servo* l_servo,t_mouv * mouv);

int  
ncu_servoWindows_action(ncu_list_servo*  , ncu_cmdLine * cmda);

void 
ncu_servoWindows_hide(ncu_list_servo * this);

void 
ncu_servoWindows_show(ncu_list_servo * this);

void 
ncu_listServo_dest(ncu_list_servo * this);

#endif
