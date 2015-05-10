#include <stdlib.h>





char ** menu_list_init(unsigned int nbCol, unsigned int nbLin){
 char** tableau;
    char* data;
       int i;
       
          if(nbLin <= 0 || nbCol <= 0)
		     {
			            return NULL;
				       }
	  
	     tableau = (char**) malloc(nbLin*nbCol*sizeof(char) + nbLin*sizeof(char*));
	        if(tableau == NULL)
		           {
			           return NULL;
			    }
      
    for(i=0,data=(char*)(tableau+nbLin); i<nbLin; i++,data+=nbCol)
    {
        tableau[i] = data;
    }	
    return tableau;

} 


void menu_list_free(char** menu_list){

	free(menu_list);
}


