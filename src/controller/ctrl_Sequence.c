#include "../include/ctrl.h"
#include "../interface/ncurses_CmdLine.h"
#include "../interface/ncurses_Menu.h"
#include "../interface/ncurses_Frame.h"
#include "../interface/ncurses_FileSelect.h"
#include "../interface/ncurses_ListSequence.h"
#include "../data/data_ListMenu.h"
#include "../data/data_modelUart.h"
#include "../data/data_modelFile.h"

#include <stdlib.h> 
#include <fcntl.h>
#include <sys/stat.h>

ncu_menu_panel * menu_seq;
ncu_sequence * interface_seq;
ncu_list_servo * serv;
ncu_frame * frame;
ncu_fileSelect * file_selector;



int Cseq_init(){
	char** menu= menu_list_init(20,8);
	menu[0] ="cree";
	menu[1] ="modifier";
	menu[2] ="suprimer";
	menu[3] ="jouer";
	menu[4] ="ouvrir";
	menu[5] ="sauvegarder";
	menu[6] ="help";
	menu_seq = ncu_menu_init(1,1,20,9,menu,7);
	interface_seq = ncu_sequence_init(seqa,1,10,20,30);
	frame = ncu_frame_init(24,15);
	return 0;
}

void Cseq_setFileSelector(ncu_fileSelect * fs){
	file_selector = fs;
}

void Cseq_dest(){
	ncu_menu_dest(menu_seq);
	ncu_sequence_dest(interface_seq);		
	ncu_frame_dest(frame);
}



int Cseq_lauch(){
	ncu_menu_refrech(menu_seq);	
	while(1)
		switch(ncu_menu_action(menu_seq,cmda)){
			case 0:
				ncu_sequence_new_elem(interface_seq,cmda);
				break;
			case 1: 
				if(seqa->first == NULL)
					break;
				if(seqa->curent == NULL)
					break;

				ncu_sequence_action(interface_seq,cmda);
				seqa->curent->send=0;
				ncu_sequence_refrech(interface_seq);
				ncu_frame_change(frame,seqa->curent->seq);
				ncu_frame_action(frame,cmda);	
				break;
			case 2:
				if(seqa->first == NULL)
					break;
				if(seqa->curent == NULL)
					break;

				ncu_sequence_action(interface_seq,cmda);
				ncu_sequence_del(interface_seq);
				ncu_sequence_refrech(interface_seq);
				break;
			case 3:
				if(seqa->first == NULL)
					break;
				if(seqa->curent == NULL)
					break;
				
				ncu_sequence_action(interface_seq,cmda);
				
				ncu_fileSelect_getUart(file_selector,cmda);

				uart_sendModif(file_selector->uart, seqa,messBoxa);
				uart_sendJouer(file_selector->uart,seqa,messBoxa);

				messageBox_refrech(messBoxa);
				ncu_sequence_refrech(interface_seq);
				break;

			case 4 : 
				
				ncu_fileSelect_getFIle(file_selector,cmda,O_RDONLY);

				file_charge(file_selector->file,seqa,messBoxa);

				messageBox_refrech(messBoxa);
				file_exit(file_selector->file);	
				ncu_sequence_refrech(interface_seq);
				break;

			case 5 :
				ncu_fileSelect_getFIle(file_selector,cmda, O_WRONLY );
				file_save(file_selector->file,seqa,messBoxa);
				messageBox_refrech(messBoxa);
				file_exit( file_selector->file);
				ncu_sequence_refrech(interface_seq);
				break;		
			case -1:return 0;
				break;
		}


}
