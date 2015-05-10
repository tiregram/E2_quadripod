#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../include/basic.h"
#include "../ncurses_inputSelect.h"
#include "../ncurses_ServoWindow.h"
#include "../../data/data_struct.h"
#include "../ncurses_MessageBox.h"
#include "../ncurses_Frame.h"
#include "../ncurses_Menu.h"
#include "../ncurses_ListSequence.h"
#include "../ncurses_InputString.h"
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
	//	frame_action(b,ch);	
	}
	sleep(5);
}

void testMenu(){
char *  list[20] = {"Sequence","OpenCV","help","Exit"};
	menu_panel * a = menu_init(1,1,20,6,list,4);
	cmd_line * b = cmd_init();
	int ch = menu_action(a,b);
if(ch==0){
char *  list1[20] = {"cree","modifier","suprimer","jouer","ouvrir","sauvegarder","help"};
	menu_panel * a2 = menu_init(23,1,20,9,list1,7);
	cmd_line * b2 = cmd_init();
	menu_action(a2,b2);

}
}

void testListSeq(){
	list_sequence * d = sequence_init("one",1,NULL);
	sequence_add(d,0,"deux",2,NULL);
	sequence_add(d,0,"trois",3,NULL);
	sequence_add(d,0,"quat",4,NULL);
	ncu_sequence * a = ncu_sequence_init(d,1,1,18,10);
	cmd_line * b = cmd_init();
	while(ncu_sequence_action(a,b)!=-1);
	sleep(2);
}





cmd_line * b; 
menu_panel * a;menu_panel * a1; menu_panel * a2;  
//sousMenuPrincipal
void menuInterface1(){
	menu_refrech(a1);	
	while(1)
	switch(menu_action(a1,b)){
		case 0:
			break;
		case 1: 
		case -1:return;
			break;
	}

}
void menuInterface2(){
	
	menu_refrech(a2);	

	while(1)
	switch(menu_action(a2,b)){

		case 0:
			break;
		case 1: 
		case -1:return;
			break;
	}
}



//menuPrincipal
void menuInterface(){
	b = cmd_init();
	char *  list[20] = {"Sequence","OpenCV","help","Exit"};
	a = menu_init(1,1,20,9,list,4);
	char *  list2[20] = {"openCV","Pas","Encore","fais"};
	a2 = menu_init(1,1,20,9,list2,4);
	char *  list1[20] = {"cree","modifier","suprimer","jouer","ouvrir","sauvegarder","help"};
	a1 = menu_init(1,1,20,9,list1,7);

	menu_refrech(a);
	while(1)
	switch(menu_action(a,b)){
		case 0:
			menuInterface1();
			menu_refrech(a);
			break;
		case 1: 
			menuInterface2();
			menu_refrech(a);
			break;
		case -1:return;
			break;
	}

}



void inputString_test(){
	inputString * a = inputString_init_NewString(10,10,10);
	cmd_line* b= cmd_init();
	inputString_action(a,b);


}


int main (){
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	noecho();		/* Don't echo() while we do getch */
	start_color();
	//testInputSelect();
	//testMessageBox();
	//testServoWindow();
	//testFrame();a
	//testMenu();
	//testListSeq();
	//menuInterface();
	inputString_test();
}
