#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data_Sequence.h"
#include "../include/basic.h"
#include "data_modelFile.h"
#include <fcntl.h>
#include <unistd.h>



file_struct * file_init(char * name,char * path){
	file_struct * this = malloc(sizeof(file_struct));
	this->file = open(path,O_RDWR);
	//strcpy(this->name,name);
	return this;
}


void  file_save(file_struct* this,list_sequence *tosave){
	write(this->file,"test",4);
		

}

void file_charge(file_struct * this){


}

void file_exit(file_struct*  this){
	close(this->file);
	free(this);

}




