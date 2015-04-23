#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define nb_servo 8

/*void struct_save(struct circular_vector_mouv * saveThis){
	if(saveThis!=NULL){
		int i ;
		char finali[100]="{";
		char tempo[10];
		for(i = 0 ; i<nb_servo; i++){
			sprintf(tempo,"%i,%i",
					saveThis->mouv->pin[i],
					saveThis->mouv->pos[i]);
			strcat(finali,tempo);	
		}
		strcat(finali,"},");
		fprintf(fileSave,finali);

	}	
}*/
