#ifndef data_modelfile_include
#define data_modelfile_include
#include "data_Sequence.h"
typedef struct{
	char * name;
	int  file;	
}file_struct; 

file_struct * file_init(char * name,char * path);
void  file_save(file_struct* this,list_sequence * tosave);
void file_exit(file_struct*  this);
#endif
