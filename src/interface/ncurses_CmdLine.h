#ifndef cmd
#define cmd
#include <ncurses.h>
typedef struct {
	WINDOW * win;
	//void * cmd[100];
	//char * stringMa[100];
	int nbOfFunction;
} ncu_cmdLine;

ncu_cmdLine *  
ncu_cmd_init();

void 
ncu_cmd_addfunction(ncu_cmdLine * this, void* command, char * mathString);

int 
ncu_cmd_getCh(ncu_cmdLine * this);

#endif
