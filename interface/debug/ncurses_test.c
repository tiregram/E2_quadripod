#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../include/basic.h"
#include "../ncurses_inputSelect.h"
#include "../ncurses_ServoWindow.h"
#include "../../data/data_struct.h"
#include "../ncurses_MessageBox.h"
#include "../ncurses_Frame.h"


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
	struct_set_From_Array(addr,pin,pos);
	struct_new(addr,STRUCT_AVANT);
	unsigned long pin1[8] = {8,7,6,5,4,3,2,1};
	unsigned long pos2[8] = {43,43,43,43,43,43,43,43};
	struct_next(addr);
	struct_set_From_Array(addr,pin1,pos2);
	
	sleep(2);	
	list_servo *  list = servoWindows_init(5,10,addr->first->mouv);
	servoWindows_refrechWindows(list);
	sleep(2);
	servoWindows_change(list,addr->first->next->mouv); 
	servoWindows_refrechWindows(list);
	sleep(2);
}

void testMessageBox(){
	MessBox* a  = messageBox_init(55,20,"message");
	messageBox_refrech(a);
	for(int i=0;i<10 ;i++){
	messageBox_print(a,MESBOX_ERROR,"salut %d \n",i);	
	messageBox_print(a,MESBOX_VALID,"salut %d \n",i);	
	messageBox_print(a,MESBOX_BASIC,"salut %d \n",i);
	messageBox_refrech(a);	
	}
	
}

void testFrame(){
	circular_vector *  a = struct_init();
	struct_new(a,STRUCT_AVANT);
	struct_new(a,STRUCT_AVANT);
	struct_new(a,STRUCT_AVANT);
	
	struct_new(a,STRUCT_APRES);
	struct_new(a,STRUCT_APRES);
	struct_new(a,STRUCT_APRES);
	
	ncu_frame* b = frame_init(1,20,a);
	frame_refrechlist(b);
	int ch ;
	keypad(b->scrool, TRUE);		/* We get F1, F2 etc..		*/
	while('l'!=(ch=wgetch(b->scrool))){
		frame_action(b,ch);	
	}
	sleep(5);
}


int main (){
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	noecho();		/* Don't echo() while we do getch */
	start_color();
	testInputSelect();
	//testMessageBox();
	testServoWindow();
	//testFrame();
}
