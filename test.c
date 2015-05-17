#include "data/data_modelFile.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	char lap[20] = {'1','2','3','4','5','6','7','8'};
	unsigned long val;
	val = strtoul(lap,NULL,0);
	printf("unsigned long: %lu",val);


}
