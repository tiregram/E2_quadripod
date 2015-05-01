#ifndef data_struct
#define data_struct
struct one_Mouv{
	unsigned long pin;
	unsigned long pos;
};

typedef struct one_Mouv t_mouv;

struct circular_vector_mouv{
	struct circular_vector_mouv * next;
	struct circular_vector_mouv * prev;
	t_mouv *  mouv;
	unsigned long delay;
};


typedef struct {
	struct circular_vector_mouv * first;
	struct circular_vector_mouv * curent;
} circular_vector;



circular_vector * struct_init();
void struct_new(circular_vector * this,char av_ap);
void struct_prev(circular_vector * this);
void struct_next(circular_vector * this);
void struct_list(circular_vector * this);
void struct_set_From_Array(circular_vector * this,unsigned long * pin ,unsigned long * pos);
void struct_free_circular_vector(circular_vector * this);
#endif
