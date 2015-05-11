#ifndef frame_include
#define frame_include

#include <ncurses.h>
#include "../data/data_struct.h"
#include "ncurses_ServoWindow.h"
typedef struct {
	WINDOW * con;
	WINDOW * scrool;
	ncu_list_servo * servo_panel;
	circular_vector* data;
} ncu_frame;
ncu_frame * frame_init(int x,int y/*,circular_vector* data*/);
void frame_refrechlist(ncu_frame* this);
int frame_action(ncu_frame* this,cmd_line * cmda);
void frame_change(ncu_frame *this,circular_vector *data);
#endif
