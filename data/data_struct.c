#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/basic.h"
#include "data_struct.h"

#define out(a) printw(a)
#define PIN_INIT  {1,2,3,4,11,12,13,14}


void malloc_a_mouv(struct circular_vector_mouv * prec,struct circular_vector_mouv * suiv);
t_mouv* instance_mouvs();

circular_vector *  struct_init(){
	circular_vector * this = malloc(sizeof(circular_vector));	
	this->first = malloc(sizeof(struct circular_vector_mouv));
	this->first->next = this->first;
	this->first->prev = this->first;
	this->first->mouv = instance_mouvs();	
	this->curent=this->first;
	return this;
}

circular_vector * struct_init_empty(){
	circular_vector * this 	= malloc(sizeof(circular_vector));	
	this->first 		= NULL; 
	this->curent		= NULL;
	return this;	
}


t_mouv* instance_mouvs(){
	int i;
	int  pinInit[nb_servo] = PIN_INIT;
	t_mouv * mouvs = malloc(sizeof(t_mouv)*nb_servo);	
	for(i=0;i<nb_servo;i++){
		mouvs[i].pin =pinInit[i];
		mouvs[i].pos = 127;
	}
	return mouvs;
}
void malloc_a_mouv(struct circular_vector_mouv * prec,struct circular_vector_mouv * suiv)
{	
	struct circular_vector_mouv * theNew;
	theNew=malloc(sizeof(struct circular_vector_mouv));
	theNew->mouv = instance_mouvs();	
	theNew->delay= 500;
	theNew->next = suiv;
	theNew->prev=prec;
	prec->next = theNew;
	suiv->prev = theNew;
}


void new_mouvs(char av_ap, circular_vector * mouv){
	if(av_ap == STRUCT_AVANT){malloc_a_mouv(mouv->curent->prev,mouv->curent);
	} 
	else if(av_ap == STRUCT_APRES){malloc_a_mouv(mouv->curent,mouv->curent->next);
	}
	else if(av_ap == STRUCT_END){
		malloc_a_mouv(mouv->first->prev,mouv->first);
	}else if(av_ap == STRUCT_BEGIN){
		malloc_a_mouv(mouv->first->prev,mouv->first);
		mouv->first = mouv->first->prev;
	}


} 

void struct_new(circular_vector * this,char av_ap){
	if(this->first == NULL){
		struct circular_vector_mouv * theNew;
		theNew=malloc(sizeof(struct circular_vector_mouv));
		theNew->mouv = instance_mouvs();	
		theNew->delay= 500;
		theNew->next = theNew;
		theNew->prev = theNew;
		
		this->curent = theNew;
		this->first = theNew;	
		return;	
	}
	new_mouvs(av_ap,this);
}
void struct_next(circular_vector * this){
	this->curent = this->curent->next;
}

void struct_prev(circular_vector * this){
	this->curent = this->curent->prev;

}
t_mouv * getmouvs(circular_vector * this){
	return this->curent->mouv;
}

void struct_list(circular_vector * this ){
	char a[100]="";
	int nb = 0;
	struct circular_vector_mouv * i = this->curent;
	out("Debut\n");
	do{
		printf("Element n*%i\n",nb++);	
		a[0] =0;
		for(int j = 0; j<nb_servo;j++){
			sprintf(a,"=> pin=%3lu | pin=%2lu \n",i->mouv[j].pin,i->mouv[j].pos);
			out(a);}
		i = i->next;
	}while(i!=this->curent);
	out("Fin\n");
}

void struct_set(circular_vector * this, t_mouv *t ){
	free(this->curent->mouv);
	this->curent->mouv = t;	
}

t_mouv * struct_mouv(unsigned long * pin ,unsigned long * pos){
	t_mouv * ret  = malloc(sizeof(t_mouv)*nb_servo);  
	for(int i=0;i<nb_servo;i++){
		ret[i].pin = pin[i];
		ret[i].pos = pos[i];
	}
	return ret;
}

void struct_set_From_Array(circular_vector * this,unsigned long * pin ,unsigned long * pos,unsigned long delay){
	this->curent->delay = delay;
	for(int i=0;i<nb_servo;i++){
	this->curent->mouv[i].pin = pin[i];	
	this->curent->mouv[i].pos = pos[i];	
	}
}

void struct_create_From_Array(circular_vector * this,unsigned long * pin ,unsigned long * pos,unsigned long delay){
	struct_new(this,STRUCT_END);
	struct_set_From_Array(this, pin , pos, delay);
}







void struct_free_circular_vector(circular_vector * this ){
	struct circular_vector_mouv * p = this->first;
       	struct circular_vector_mouv * s ; 	
	int nb = 0;
	do{
		printf("lib %i\n",nb++);
		s = p->next;
		free(p->mouv);
		free(p);
		p=s;	
	}while(this->first!=s);
	free(this);	
}




