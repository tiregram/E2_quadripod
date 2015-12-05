#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data_Sequence.h"
#include "../include/basic.h"
#include "../interface/ncurses_MessageBox.h"
#include "data_modelFile.h"
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>





file_struct * file_init(char * name,char * path,int opt){
	file_struct * this = malloc(sizeof(file_struct));
	this->file = open(path,opt);
	this->name = malloc(strlen(name));
	this->dataRead = malloc(sizeof(struct stock));
	this->dataRead->ret = 0;
	this->dataRead->cont = malloc(sizeof(char)*20);
	strcpy(this->name,name);
	return this;
}


void  file_save(file_struct* this,list_sequence *tosave,MessBox* messBox){
	char buff[20];
	if(this->file==0){
		messageBox_print(messBox ,MESBOX_ERROR,"NO FILE");
		return;
	}

	

	lseek(this->file,0,SEEK_SET);

	sequenc* a  = tosave->first;
	if(a==NULL){
		messageBox_print(messBox,MESBOX_ERROR,"sequence est vide");
		return;
	}	
	
	
	while(a != NULL){
		write(this->file,"S",1);
		sprintf(buff,"%10s",a->name);
		write(this->file,buff,10);
		sequence_export_command_all(this->file,a->seq);
		lseek(this->file,-1,SEEK_CUR);
		write(this->file,"%",1);

		a = a->next;
	}

	messageBox_print(messBox,MESBOX_VALID,"Save:finish.\n");

		write(this->file,"*",1);	
	return;
}

// no double file read at the same time !!

void file_read(file_struct *  this,int nb){
	if(nb<=0 || nb>=20)return;
	
	this->dataRead->ret = read(this->file,this->dataRead->cont,nb);		
				
}


void file_charge(file_struct * this,list_sequence * seq,MessBox* messBox){


	if(this->file==0){
		messageBox_print(messBox ,MESBOX_ERROR,"Charge: no file, no permition %i",this->file);
		return;
	}
	
	char buff[20];
	sequence_drop(seq);
	seq->first = NULL;
	seq->curent = NULL;
	seq->nb_total = 0;
	seq->last =NULL;

	lseek(this->file,0,SEEK_SET);
	int nostop;
	circular_vector *cv;
	char name[11];
	unsigned long delay;
	unsigned long pin[8];
	unsigned long pos[8];
	


	file_read(this,1);
	if(this->dataRead->cont[0]!='S'){
		messageBox_print(messBox,MESBOX_ERROR,"Charge: No begin file\n");
		messageBox_print(messBox,MESBOX_ERROR,"Charge: Not load\n");
		return;
	}
	do{
		file_read(this,10);
		strncpy(name,this->dataRead->cont,10);
		name[10]='\0';
		cv  =  struct_init_empty();	
		do{	
			file_read(this,1);

			if(this->dataRead->cont[0]!='F'){
				messageBox_print(messBox,MESBOX_ERROR,"Charge: no \'F\'\n");
				return;}

			file_read(this,7);
			delay = strtoul(this->dataRead->cont,NULL,10);
			file_read(this,1);

			if(this->dataRead->cont[0]!='P'){
				printw("File: no \'P\'");		
				return;}


			for(int i = 0 ; i<nb_servo;i++){
				file_read(this,2);
				this->dataRead->cont[2]='\0';
				pin[i] = strtoul(this->dataRead->cont,NULL,10);
				file_read(this,3);
				this->dataRead->cont[3]='\0';
				pos[i] = strtoul(this->dataRead->cont,NULL,10);
			}
			struct_create_From_Array(cv,pin,pos,delay);

			file_read(this,1);
			if(this->dataRead->cont[0]=='#'){
				nostop = 1;	
			}else if(this->dataRead->cont[0]=='%'){
				nostop = 0;
			}else{
				messageBox_print(messBox,MESBOX_ERROR,"Charge: no END for Frame\n");
				return ;
			}

		}while(nostop);

		sequence_add(seq,SEQUENCE_AT_END,name,seq->nb_total,cv);
		sprintf(buff,"Charge: %10s is charge.\n",name);
		messageBox_print(messBox,MESBOX_VALID,buff);


		file_read(this,1);
		if(this->dataRead->cont[0]=='S'){
			nostop = 1;	
		}else if(this->dataRead->cont[0]=='*'){
			nostop = 0;
		}else{
			messageBox_print(messBox,MESBOX_ERROR,"Charge: no END for Sequence\n");
			return ;
		}
	}while(nostop);

	seq->curent = seq->first;
	

	return;

}
void file_exit(file_struct*  this){
	close(this->file);
	free(this);

}





