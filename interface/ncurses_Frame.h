#ifndef frame_include
#define frame_include

#include <ncurses.h>
#include "../data/data_struct.h"
#include "ncurses_ServoWindow.h"
#include "ncurses_inputNumber.h"

typedef struct {
	WINDOW * con;
	WINDOW * scrool;
	ncu_list_servo * servo_panel;
	circular_vector* data;
	ncu_inputNumber* delay;
} ncu_frame;

ncu_frame * 
ncu_frame_init(int x,int y);

void 
ncu_frame_refrechlist(ncu_frame* this);

int 
ncu_frame_action(ncu_frame* this,ncu_cmdLine * cmda);

void 
ncu_frame_change(ncu_frame *this,circular_vector *data);

void 
ncu_frame_dest(ncu_frame * this);

#endif
