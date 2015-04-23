#define nb_servo 8
#define STRUCT_AVANT 1
#define STRUCT_APRES 2


struct one_Mouv{
	unsigned char pin;
	unsigned char pos;
};


typedef struct one_Mouv t_mouv;
void struct_init();
void next();
void prev();
t_mouv * getmouvs();
void free_all();
void new(char av_ap);
