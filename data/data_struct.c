#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data_struct.h"

struct circular_vector_mouv{
	struct circular_vector_mouv * next;
	struct circular_vector_mouv * prev;
	t_mouv *  mouv;
};

void malloc_a_mouv(struct circular_vector_mouv * prec,t_mouv * val,struct circular_vector_mouv * suiv);
t_mouv* instance_mouvs();
struct circular_vector_mouv * first;
struct circular_vector_mouv * curent;

void struct_init(){
	first= malloc(sizeof(struct circular_vector_mouv));
	first->next = first;
	first->prev = first;
	first->mouv = instance_mouvs();	
	curent=first;
}


t_mouv* instance_mouvs(){
	int i;
	t_mouv * mouvs = malloc(sizeof(t_mouv)*nb_servo);	
	for(i=0;i<nb_servo;i++){
		mouvs[i].pin = i;
		mouvs[i].pos = 127;
	}
	return mouvs;
}
void malloc_a_mouv(struct circular_vector_mouv * prec,t_mouv * val,struct circular_vector_mouv * suiv)
{	
	struct circular_vector_mouv * theNew;
	theNew=malloc(sizeof(struct circular_vector_mouv));
	theNew->mouv = instance_mouvs();	

	theNew->next = suiv;
	theNew->prev=prec;
	prec->next = theNew;
	suiv->prev = theNew;
}


void new_mouvs(char av_ap,struct circular_vector_mouv * mouv){
	if(av_ap == STRUCT_AVANT){malloc_a_mouv(mouv->prev,instance_mouvs(),mouv);
	} 
	else if(av_ap == STRUCT_APRES){malloc_a_mouv(mouv,instance_mouvs(),mouv);
	
	}


} 

void new(char av_ap){
	new_mouvs(av_ap,curent);
}
void next(){
	curent = curent->next;
}

void prev(){
	curent = curent->prev;

}
t_mouv * getmouvs(){
	return curent->mouv;
}

void list(){
	char a[100]="";
	int nb = 0;
	struct circular_vector_mouv * i = curent->next;
	//printMessage("Debut");
	while(i!=curent){
		a[0] =0;
	//	sprintf(a,"n*%i, => pin=%i | pin=%i",nb++,i->mouv->pin,i->mouv->pos);
	//	printMessage(a);
		i = i->next;
	}
	//printMessage("Fin");

}

void free_all(){
	struct circular_vector_mouv * i = first->next; 
	while(i!=first){
		i = i->next;
		free(i->prev);	
	}
	free(first);		
}
