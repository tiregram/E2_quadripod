#include <stdio.h>
#define debug 1 
#include "../data_struct.h"

int main(){
	printf("Debug On");
	circular_vector* addr = struct_init();
	unsigned long pin[8] = {8,7,6,5,4,3,2,1};
	unsigned long pos[8] = {42,42,42,42,42,42,42,42};
	struct_new(addr,STRUCT_AVANT);

	struct_next(addr);
	struct_set_From_Array(addr,pin,pos);	
	

	struct_list(addr);

	struct_free_circular_vector(addr);

}
