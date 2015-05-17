#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data_Sequence.h"
#include "../include/basic.h"
#include "data_modelFile.h"
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>





file_struct * file_init(char * name,char * path){
	file_struct * this = malloc(sizeof(file_struct));
	this->file = open(path,O_RDWR);
	this->name = malloc(strlen(name));
	this->dataRead = malloc(sizeof(struct stock));
	this->dataRead->ret = 0;
	this->dataRead->cont = malloc(sizeof(char)*20);
	strcpy(this->name,name);
	return this;
}


void  file_save(file_struct* this,list_sequence *tosave){
	char buf[20];
	sequenc* a  = tosave->first;
	while(a != NULL){
		write(this->file,"S",1);
		sprintf(buf,"%10s",a->name);
		write(this->file,buf,10);
		sequence_export_command_all(this->file,a->seq);
		lseek(this->file,-1,SEEK_CUR);
		write(this->file,"%",1);
		a = a->next;
	}
		write(this->file,"*",1);	
	return;
}

// no double file read at the same time !!

void file_read(file_struct *  this,int nb){
	if(nb<=0 || nb>=20)return;
	
	this->dataRead->ret = read(this->file,this->dataRead->cont,nb);		
				
}


char *	file_charge(file_struct * this,list_sequence * seq){
	sequence_drop(seq);
	seq->first = NULL;
	seq->curent = NULL;
	seq->nb_total = 0;
	seq->last =NULL;

	char * ret = malloc(sizeof(char)*20);
	lseek(this->file,0,SEEK_SET);
	int nostop;
	circular_vector *cv;
	char name[11];
	unsigned long delay;
	unsigned long pin[8];
	unsigned long pos[8];
	
	
	file_read(this,1);
	if(this->dataRead->cont[0]!='S'){
		printw("no begin");	
		refresh();		
		return NULL;}
	do{
		file_read(this,10);
		strncpy(name,this->dataRead->cont,10);
		name[10]='\n';
		do{	
			cv  =  struct_init_empty();	
			file_read(this,1);
			if(this->dataRead->cont[0]!='F'){
				printw("no F");
			refresh();
				return NULL;}
			file_read(this,7);
			delay = strtoul(this->dataRead->cont,NULL,0);
			file_read(this,1);
			if(this->dataRead->cont[0]!='P'){
				printw("no P");			
			refresh();
				return NULL;}


			for(int i = 0 ; i<nb_servo;i++){
				file_read(this,2);
				pin[i] = strtoul(this->dataRead->cont,NULL,0);

				file_read(this,3);
				pos[i] = strtoul(this->dataRead->cont,NULL,0);
			}
			struct_create_From_Array(cv,pin,pos,delay);
			
			file_read(this,1);
			if(this->dataRead->cont[0]=='#'){
				nostop = 1;	
			}else if(this->dataRead->cont[0]=='%'){
				nostop = 0;
			}else{
				printw("no stop");			
			refresh();
				return NULL;
			}
							
		}while(nostop);
			
		sequence_add(seq,SEQUENCE_AT_CURENT_A,name,-1,cv);

		

		file_read(this,1);
		if(this->dataRead->cont[0]=='S'){
			nostop = 1;	
		}else if(this->dataRead->cont[0]=='*'){
			nostop = 0;
		}else{
			printw("no stop 2");			
			refresh();
			return NULL;
		}
	}while(nostop);

	seq->last = seq->curent;	
	seq->curent = seq->first;
		

	strcpy(ret,"Chargement ok");
	return ret;
}
void file_exit(file_struct*  this){
	close(this->file);
	free(this);

}





