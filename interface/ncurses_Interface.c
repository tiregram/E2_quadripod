#include <ncurses.h>
#include <unistd.h>
#include "ncurses_Interface.h"
#include "ncurses_inputSelect.h"


void new_frame();
void change_to_frame(char av_ar);
void create_a_frame();
void focusWindow();
void defocusWindow();
void destroy_win(WINDOW *local_win);
WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW *boxMessage;
struct servo{
	struct input_panel* position;
	struct input_panel*  pin;
	WINDOW * win_serv;
};

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
	int vy , vx,vyMax,vxMax;
	getyx(boxMessage, vy, vx);
	getmaxyx(boxMessage,vyMax,vxMax);
	if(vy<vyMax-2){	

		mvwprintw(boxMessage,vy+1,6,mess);	
	}else{

		mvwprintw(boxMessage,3,6,"  ");

	}
	wrefresh(boxMessage);
}


int actionOnInterface(){

	mvwprintw(selectArea,0,0,"cmd:");
	wrefresh(selectArea);
	int ch = wgetch(selectArea);
	char str[100];
	sprintf(str,"a:%i:a",listServo[1].position);
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
			inputSelect_modifInput(listServo[servoActual].position);
			break;


	}
	return 1;

}


void createServoWindow(char* description ,t_mouv * mouvOfThisServo){
	int x,y;
	if(nbOfServo<20){	
		listServo[nbOfServo].win_serv= create_newwin(6,20,1+8*(nbOfServo/4),decalX+20*(nbOfServo%4)+1);
		wprintw(listServo[nbOfServo].win_serv,"n*%i %s",nbOfServo,description);

		mvwprintw(listServo[nbOfServo].win_serv, 2, 2, "pin:");
		getbegyx(listServo[nbOfServo].win_serv,y,x);		
		listServo[nbOfServo].position = inputSelect_init(&(mouvOfThisServo->pos),y+4,x+9,1,255,3);	
		listServo[nbOfServo].pin = inputSelect_init(&(mouvOfThisServo->pin),y+2,x+9,1,20,2);	

		mvwprintw(listServo[nbOfServo].win_serv, 4, 2, "pos:");

		wrefresh(listServo[nbOfServo].win_serv);
		nbOfServo++;
	}

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
	inputSelect_changeCible(listServo[indice].position,&(mouv.pos));
	inputSelect_Actualiser(listServo[indice].position);
	inputSelect_Actualiser(listServo[indice].pin);

}


void replace_all_servoWindows(){
	int i;
	t_mouv * mouv = getmouvs();
	char a [100];
	sprintf(a,"test valeur: %i",mouv);
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

void refrechWindows(){
	int i = 0;
	for(i = 0 ; i<nbOfServo ; i++){
		box(listServo[i].win_serv, 0 , 0);
		wrefresh(listServo[i].win_serv);
	}
}


WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		
	wrefresh(local_win);		

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

void create_a_frame(){
	int i;
	new(STRUCT_AVANT);
	t_mouv* mouv = getmouvs();
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


