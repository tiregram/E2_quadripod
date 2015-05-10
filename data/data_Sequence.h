#ifndef sequence
#define sequence 
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
//void Sequence_add();
//void Sequence_del();
//void Sequence_modif();
//void Sequence_view();




#endif
