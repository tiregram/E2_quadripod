#include "ncurcesInterface.h"
#include <unistd.h>

int main(){
	struct_init();	

	init();
	printMessage("HI	H for HELP ");
	while(1){
	actionOnInterface();}
	sleep(10);

	return 0;
}
