#ifndef data_modelfile_include
#define data_modelfile_include
#include "data_Sequence.h"
#include "../interface/ncurses_MessageBox.h"

struct stock{
long ret;
char* cont;
};

typedef struct{
	struct  stock* dataRead;//info: size of cont = 20 by file_init
	char * name;
	int  file;	
}file_struct; 

file_struct * file_init(char * name,char * path,int opt);
void  file_save(file_struct* this,list_sequence * tosave,MessBox * messBox );
void file_exit(file_struct*  this);
void  file_charge(file_struct * this,list_sequence* seq,MessBox * messBox );
#endif
