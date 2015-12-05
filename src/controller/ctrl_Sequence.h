#ifndef ctrl_Sequence
#define ctrl_Sequence
#include "../interface/ncurses_ListSequence.h"
extern ncu_sequence * interface_seq;
int Cseq_lauch();

int Cseq_init();
void Cseq_setFileSelector(ncu_fileSelect * fs);

#endif
