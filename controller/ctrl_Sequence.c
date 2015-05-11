#include "../include/ctrl.h"
#include "../interface/ncurses_CmdLine.h"
#include "../interface/ncurses_Menu.h"
#include "../interface/ncurses_Frame.h"

#include "../interface/ncurses_ListSequence.h"
#include "../data/data_ListMenu.h"

menu_panel * menu_seq;
ncu_sequence * interface_seq;
ncu_list_servo * serv;
ncu_frame * frame;

int Cseq_init(){
	char** menu= menu_list_init(20,8);
	menu[0] ="cree";
	menu[1] ="modifier";
	menu[2] ="suprimer";
	menu[3] ="jouer";
	menu[4] ="ouvrir";
	menu[5] ="sauvegarder";
	menu[6] ="help";
	menu_seq = menu_init(1,1,20,9,menu,7);
	interface_seq = ncu_sequence_init(seqa,1,10,20,30);
	frame = frame_init(24,15);
	return 0;
	}


int Cseq_lauch(){

	menu_refrech(menu_seq);	
	while(1)
	switch(menu_action(menu_seq,cmda)){
		case 0:
		ncu_sequence_new_elem(interface_seq,cmda);
			break;
		case 1: 
		if(seqa->first == NULL)
			break;
		if(seqa->curent == NULL)
			break;
	
		ncu_sequence_action(interface_seq,cmda);
		frame_change(frame,seqa->curent->seq);
		frame_action(frame,cmda);	
			
		
		
		
			break;
		case 2:
			ncu_sequence_action(interface_seq,cmda);
			ncu_sequence_del(interface_seq);
			break;
		case -1:return 0;
			break;
	}

}
