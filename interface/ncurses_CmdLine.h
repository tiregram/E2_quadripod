#ifndef cmd
#define cmd
#include <ncurses.h>
typedef struct {
	WINDOW * win;
	//void * cmd[100];
	//char * stringMa[100];
	int nbOfFunction;
} cmd_line;

cmd_line *  cmd_init();
void cmd_addfunction(cmd_line * this, void* command, char * mathString);
int cmd_getCh(cmd_line * this);
#endif
