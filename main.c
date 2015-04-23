#include "interface/ncurses_Interface.h"
#include <unistd.h>

int main(){
	struct_init();	

	init();
	printMessage("HI	H for HELP ");
	while(actionOnInterface()){
	;}
	sleep(1);

	return 0;
}
