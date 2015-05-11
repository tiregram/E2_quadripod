#include <unistd.h>
#include "controller/ctrl_Base.h"


int main(){
	int ret;
	ret = Cbase_init();
	ret = Cbase_lauch();
	ret = Cbase_destr();
	return 0;
}
