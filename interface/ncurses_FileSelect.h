#include "ncurses_InputString.h"
#include "../data/data_modelFile.h"
#include "../data/data_modelUart.h"
#include <ncurses.h>


typedef struct {
	ncu_inputString *input;
	union{
		uart_struct * uart;
		file_struct * file;		
	};
	WINDOW* win;
}ncu_fileSelect;


ncu_fileSelect* ncu_fileSelect_init(int sizeX,int sizeY,int startX,int startY);
void ncu_fileSelect_createUart(ncu_fileSelect * this,cmd_line * cmdp);

void ncu_fileSelect_getFIle();