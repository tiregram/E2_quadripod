#include <ncurses.h>
#include <stdlib.h>
#include "../../include/basic.h"
#include "../ncurses_inputSelect.h"
#include "../ncurses_ServoWindow.h"
#include "../../data/data_struct.h"


int main (){
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	noecho();		/* Don't echo() while we do getch */
	start_color();

}
void testInputSelect(){
	unsigned long * var = malloc(sizeof(long));
	unsigned long * var2 = malloc(sizeof(long));
	*var= 10;
	struct input_panel * lap = inputSelect_init(var,2,2,1,255,3);
	struct input_panel * lap2 = inputSelect_init(var2,5,2,5,255,3);
	
 	inputSelect_modifInput(lap);
 	inputSelect_modifInput(lap2);

 	inputSelect_changeCible(lap,var2);
 	inputSelect_changeCible(lap2,var);
	
	inputSelect_Actualiser(lap);	
	inputSelect_Actualiser(lap2);	

 	inputSelect_modifInput(lap);
 	inputSelect_modifInput(lap2);
	

	free(var);
	free(var2);
}

void testServoWindow(){
	circular_vector* addr = struct_init();
	unsigned long pin[8] = {8,7,6,5,4,3,2,1};
	unsigned long pos[8] = {42,42,42,42,42,42,42,42};
	struct_new(addr,STRUCT_AVANT);

	struct_next(addr);
	struct_set_From_Array(addr,pin,pos);
		
	list_servo *  list = servoWindows_create(5,5,addr->first->mouv);
	

}
