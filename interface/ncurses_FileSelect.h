#include "ncurses_InputString.h"
#include "../data/data_modelFile.h"
#include "../data/data_modelUart.h"
#include <ncurses.h>


typedef struct {
	inputString *input;

	union{
		uart_struct * uart;
		file_struct * file;		
	};
	WINDOW* win;
}ncu_fileSelect;


ncu_fileSelect* fileSelect_init(int sizeX,int sizeY,int startX,int startY);
void fileSelect_createUart(ncu_fileSelect * this,cmd_line * cmdp);
void fileSelect_getFIle();
