#include <unistd.h>
#include "controller/ctrl_Base.h"


int main(){
	int ret;
	ret = Cbase_init();
	sleep(2);
	ret = Cbase_lauch();

	sleep(1);
	return 0;
}
