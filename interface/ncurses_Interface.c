#include <ncurses.h>
#include <unistd.h>
#include "ncurses_Interface.h"
#include "ncurses_inputSelect.h"
#define debug debug

void new_frame();
void change_to_frame(char av_ar);
void create_a_frame();
void focusWindow();
void defocusWindow();
void destroy_win(WINDOW *local_win);
WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW *boxMessage;


int nbOfServo;
int servoActual;
int PinOrPos;
typedef struct servo servo;
servo listServo[20];
int decalX;
int decalY;
WINDOW* selectArea;

void  init(){
	int row,col;	
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	noecho();		/* Don't echo() while we do getch */
	start_color();
	getmaxyx(stdscr,row,col);
	boxMessage =	create_newwin(row-2*10,col-20,6*2+5,10);
	selectArea = newwin(1,col,row-1,1);
	wattron(selectArea,A_REVERSE);
	keypad(selectArea, TRUE);		/* We get F1, F2 etc..		*/
	wprintw(boxMessage,"Message");
	wrefresh(boxMessage);
	mvwhline(selectArea,0,0,' ', col);	
	wrefresh(selectArea);
	decalX= col/2-41;
	servoActual =0;
	create_a_frame();
}

void printMessage(char* mess){
	int vy ,vyMax;
	int null;
	getyx(boxMessage, vy,null);
	getmaxyx(boxMessage,vyMax,null);
	null=null;//be here to cancel the warning
	if(vy<vyMax-2){	

		mvwprintw(boxMessage,vy+1,6,mess);	
	}else{

		mvwprintw(boxMessage,3,6,"  ");

	}
	wrefresh(boxMessage);
}


int actionOnInterface(){
	
	int ch;
	mvwprintw(selectArea,0,0,"cmd:");
	wrefresh(selectArea);
       	ch= wgetch(selectArea);
	switch(ch){
		case 'q':
			return 0;		

			break;

		case KEY_LEFT:
			changeServoWindow(ch);
			break;
		case KEY_RIGHT:
			changeServoWindow(ch);	
			break;
		case 'l':
			list(STRUCT_AVANT);
			break;

		case 'n':
			change_to_frame(STRUCT_AVANT);
			break;
		case 'b':
			change_to_frame(STRUCT_APRES);	
			break;
		case 'c':
			new_frame();
			break;	
		case 'h':
			printMessage("HELP ME.... NO!");	
			break;

		case KEY_UP:
			inputSelect_modifInput(listServo[servoActual].pin);
			break;

		case KEY_DOWN:	
			inputSelect_modifInput(listServo[servoActual].pos);
			break;


	}
	return 1;

}


void changeServoWindow(int direction){

	if(servoActual>=0 && servoActual<nbOfServo){
		defocusWindow();
		if(direction==KEY_RIGHT){			
			servoActual++;
		}else if (direction==KEY_LEFT)
			servoActual--;
		servoActual = (servoActual+nbOfServo)%nbOfServo;

		focusWindow();
	}


}
void replace_one_servoWindows(int indice,t_mouv   mouv){
	inputSelect_changeCible(listServo[indice].pin,&(mouv.pin));
	inputSelect_changeCible(listServo[indice].pos,&(mouv.pos));
	inputSelect_Actualiser(listServo[indice].pos);
	inputSelect_Actualiser(listServo[indice].pin);

}


void replace_all_servoWindows(){
	int i;
	t_mouv * mouv = getmouvs();
	char a [100];
	sprintf(a,"test valeur: %ld",mouv->pos);
	printMessage(a);
	for(i= 0; i <nb_servo;i++)
		replace_one_servoWindows(i,mouv[i]);

}

void defocusWindow(){
	mvwprintw(listServo[servoActual].win_serv,1,1," ");
	wrefresh(listServo[servoActual].win_serv);
}
void focusWindow(){
	mvwprintw(listServo[servoActual].win_serv,1,1,"X");
	wrefresh(listServo[servoActual].win_serv);
}



void create_a_frame(){
	int i;
	t_mouv* mouv ;
	new(STRUCT_AVANT);
	mouv= getmouvs();
	for(i=0;i<nb_servo;i++)
	{	
		createServoWindow("test",&mouv[i]);
	}

}


void new_frame(){
	new(STRUCT_AVANT);
	change_to_frame(STRUCT_APRES);
}

void change_to_frame(char av_ar){

	if(av_ar==STRUCT_AVANT){
		next();
		printMessage("servoNext");	
	}else{
		prev();
		printMessage("servoPrec");	
	}

	replace_all_servoWindows();

}


