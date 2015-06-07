#ifndef sequence_initclude
#define sequence_initclude
#include "data_struct.h"

#define sequence_vide_oui 1
#define sequence_vide_non 0

#define SEQUENCE_AVANT 1
#define SEQUENCE_APRES 2

#define SEQUENCE_AT_END  0
#define SEQUENCE_AT_BEGIN 1
#define SEQUENCE_AT_CURENT_A 2
#define SEQUENCE_AT_CURENT_P 3



typedef struct sequenc{
	char 	* name;
	int 	 num;
	char	 send;
	circular_vector * seq;
	struct sequenc * next;
} sequenc;


typedef struct{
	unsigned int nb_total;
	sequenc * last_created;
	sequenc * last_modif;
	sequenc * curent;
	sequenc * first;
	sequenc * last;
}list_sequence;


list_sequence * sequence_init();
void sequence_add(list_sequence * this,char atend,char * name,int num ,circular_vector * cir);

void sequence_deplacement(list_sequence * this , int sens);
void sequence_del(list_sequence * this);

void sequence_tool_replace(char * replace,char when,char by);
void sequence_free(list_sequence* this);
void sequence_drop(list_sequence* this);
void sequence_export_command_all(int file_dest ,circular_vector * seque);
void sequence_export_command_one(int  file_dest,struct circular_vector_mouv * mouv);
//void Sequence_add();
//void Sequence_del();
//void Sequence_modif();
//void Sequence_view();




#endif
