#include "data/data_modelFile.h"
#include <stdio.h>

int main(){
	file_struct* a = file_init("/tmp/lap","/tmp/lap");
	printf("debut");
	file_save(a,-1 );
	printf("fin");
	file_exit(a);

}
