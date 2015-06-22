#ifndef ctrl_OpenCv
#define ctrl_OpenCv

#include "../interface/ncurses_FileSelect.h"

int Copencv_lauch();

int Copencv_init();
void Copencv_setFileSelector(ncu_fileSelect * fs);
int Copencv_dest();
#endif
