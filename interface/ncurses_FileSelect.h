#ifndef ncu_fileSelect_include
#define ncu_fileSelect_include
#include "ncurses_InputString.h"
#include "../data/data_modelFile.h"
#include "../data/data_modelUart.h"
#include <ncurses.h>


typedef struct {
	ncu_inputString *input;
	
		uart_struct * uart;
		file_struct * file;		
	
	WINDOW* win;
}ncu_fileSelect;


ncu_fileSelect* 
ncu_fileSelect_init(int sizeX,int sizeY,int startX,int startY);

void 
ncu_fileSelect_createUart(ncu_fileSelect * this,ncu_cmdLine * cmdp);

void 
ncu_fileSelect_getFIle(ncu_fileSelect * this, ncu_cmdLine * cmdp,int opt);

void 
ncu_fileSelect_getUart(ncu_fileSelect * this,ncu_cmdLine * cmdp);

#endif 
