#include "../data/data_struct.h"
typedef struct {
	struct input_panel* pos;
	struct input_panel* pin;
	WINDOW * win;
} servo;

typedef struct {
	servo list[8];
	int actual;		
} list_servo;

list_servo * servoWindows_init(int posx , int posy,t_mouv * mouv);
void refrechWindows( list_servo * servos);
