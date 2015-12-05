#ifndef messageBox
#define messageBox
#define MESBOX_ERROR 'E'
#define MESBOX_VALID 'V'
#define MESBOX_BASIC 'B'
#include <ncurses.h>

typedef struct {
	WINDOW * cont;
	WINDOW * mess;
} MessBox;
 

MessBox * messageBox_init(int  startX,int startY,int sizeY,int sizeX,char * titre);
void messageBox_refrech(MessBox * this );
void messageBox_print(MessBox * this,char type,char *message, ...);
#endif
