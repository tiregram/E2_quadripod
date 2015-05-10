#include "data_Sequence.h"
#include <stdlib.h>
#include <string.h>



list_sequence * sequence_init(){
	list_sequence* 	this = malloc(sizeof(list_sequence));
	sequenc*  	first = malloc(sizeof(sequenc));

	this->nb_total=0;
	this->first = NULL;
	this->last = NULL;
	this->curent = NULL;
	this->last_modif = NULL;
	this->last_created = NULL;


	return this;
}

/*
#define SEQUENCE_AT_END  a la fin 
#define SEQUENCE_AT_BEGIN au debut 
#define SEQUENCE_AT_CURENT_A apres le current
*/


void sequence_add(list_sequence * this,char atPos,char * name,int num ,circular_vector * cir){
	sequenc* new = malloc(sizeof(sequenc));
	this->nb_total += 1;
	new->name = name;
	new->num  = num;
	new->send = 0;

	if(cir!=NULL)
		new->seq = cir;
	else 
		new->seq = struct_init();

	if(this->first == this->curent && atPos == SEQUENCE_AT_CURENT_P ){atPos = SEQUENCE_AT_BEGIN;}

	if(this->last == this->curent && atPos == SEQUENCE_AT_CURENT_A ){atPos = SEQUENCE_AT_END;}

	if(this->first!=NULL){	
		switch(atPos){
			case SEQUENCE_AT_BEGIN:
				new->next = this->first;	
				this->first = new;	
				break;
			case SEQUENCE_AT_END:
				this->last->next = new;
				this->last = new;
				break;
			case SEQUENCE_AT_CURENT_A:
				new->next = this->curent->next;
				this->curent->next = new;
				break;	
		}	
	}else{
		this->first  = new;
		this->last   = new;
		this->curent = new;

	}




	//modifier par le constructeur d'un circular vector
	new->next = NULL;
}

void sequence_del_by_name(list_sequence * this, char * name){
	sequenc* b;
	sequenc* a =  this->first;
	while(a==NULL || !strcmp(name,a->name)){
		b = a;	
		a = a->next;	
	}

	if(a == this->curent){
		this->curent = a->next;	
		free(a);
		return;
	}
	if(a == this->last){
		this->last=b;
		b->next=NULL;
		free(a);
		return;
	}
	if(a == this->first){
		this->first = a->next;
		free(a);
		return;
	}

	b->next = a->next;
	free(a);
	return;



}

void sequence_del_by_num(list_sequence * this,int num){




}

void sequence_deplacement(list_sequence * this , int sens){

	if(sens == SEQUENCE_AVANT){
		if(this->curent == this->last)
			this->curent = this->first;
		else 
			this->curent = this->curent->next;		
	}else if(sens == SEQUENCE_APRES){
		if(this->curent == this->first)
			this->curent = this->last;
		else{	
			sequenc *a = this->first;
			while(this->curent != a->next ){
				a = a->next;
			}
			this->curent = a;
		}
	}

}


void sequence_free(sequenc * this){
	free(this->name);
	free(this);
}


//del the current
void sequence_del(list_sequence * this){
	if(this->first == NULL){return;}


	sequenc* seqAdel = this->curent;//by default
	// on fais les cas de base
	if(this->curent == this->first && this->first == this->last){
		this->last = NULL;
		this->first = NULL;
		this->curent = NULL;
	}else
		if(this->curent == this->first ){

			this->first = this->first->next;
			this->curent = this->first;
		}else 
			if(this->curent == this->last){

				sequenc *a = this->first;
				while(this->last != a->next ){
					a = a->next;
				}
				this->last = a;
				this->curent=a;
			}else{
				sequenc *a = this->first;
				while(this->curent != a->next ){
					a = a->next;
				}
				a->next = this->curent->next;

				this->curent = this->curent->next;
			}
	sequence_free(seqAdel);	
	this->nb_total -= 1;
}






