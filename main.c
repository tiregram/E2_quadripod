#include "interface/ncurses_Interface.h"
#include "data/data_struct.h"
#include <unistd.h>

int main(){
	 circular_vector * data = struct_init();	
	interface_init(data);
		while(1){
	

	interface_action();
	}
	sleep(3);
	return 0;
}
