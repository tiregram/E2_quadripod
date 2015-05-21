CC=gcc
CFLAGS=-Wextra -Wall -std=gnu99 -g 
LDFLAGS=
MATH= -lm
NCURSES = -lncurses
COLOR = -fdiagnostics-color=auto

DATA      = data_struct.o data_modelFile.o data_modelUart.o data_Sequence.o data_ListMenu.o
INTERFACE =  ncurses_inputSelect.o ncurses_ServoWindow.o ncurses_MessageBox.o ncurses_Frame.o ncurses_CmdLine.o ncurses_Menu.o ncurses_ListSequence.o ncurses_inputString.o ncurses_FileSelect.o
CTRL 	  = ctrl_Base.o ctrl_Sequence.o

all: princ


princ: $(DATA) $(INTERFACE) $(CTRL) ctrl.o 
	@$(CC) -o lauch  main.c $(LDFLAGS) $(COLOR) $(NCURSES) $(MATH) $(INTERFACE) $(DATA) $(CTRL) ctrl.o




###############################################DATA##############################################
data_struct.o:
	@$(CC) -o data_struct.o -c data/data_struct.c $(CFLAGS) $(COLOR)
data_modelFile.o:
	@$(CC) -o data_modelFile.o -c data/data_modelFile.c $(CFLAGS) $(COLOR)
data_modelUart.o:
	@$(CC) -o data_modelUart.o -c data/data_modelUart.c $(CFLAGS) $(COLOR)
data_Sequence.o:
	@$(CC) -o data_Sequence.o -c data/data_Sequence.c $(CFLAGS) $(COLOR)
data_ListMenu.o:
	@$(CC) -o data_ListMenu.o -c data/data_ListMenu.c $(CFLAGS) $(COLOR)


#############################################""#CTRL###############################################
ctrl_Base.o:
	@$(CC) -o ctrl_Base.o -c controller/ctrl_Base.c $(CFLAGS) $(COLOR)
ctrl_Sequence.o:
	@$(CC) -o ctrl_Sequence.o -c controller/ctrl_Sequence.c $(CFLAGS) $(COLOR)


##############################################INTERFACE#############################################
ncurses_MessageBox.o:
	@$(CC) -o ncurses_MessageBox.o -c interface/ncurses_MessageBox.c  $(CFLAGS) $(COLOR)

ncurses_Interface.o: 
	@$(CC) -o ncurses_Interface.o -c interface/ncurses_Interface.c  $(CFLAGS) $(COLOR)

ncurses_inputSelect.o:
	@$(CC) -o ncurses_inputSelect.o -c interface/ncurses_inputSelect.c $(CFLAGS) $(COLOR)

ncurses_ServoWindow.o: 
	@$(CC) -o ncurses_ServoWindow.o -c interface/ncurses_ServoWindow.c $(CFLAGS) $(COLOR)

ncurses_Frame.o: 
	@$(CC) -o ncurses_Frame.o -c interface/ncurses_Frame.c $(CFLAGS) $(COLOR)

ncurses_Menu.o:
	@$(CC) -o ncurses_Menu.o -c interface/ncurses_Menu.c $(CFLAGS) $(COLOR)

ncurses_ListSequence.o:
	@$(CC) -o ncurses_ListSequence.o -c interface/ncurses_ListSequence.c $(CFLAGS) $(COLOR)
	
ncurses_CmdLine.o:
	@$(CC) -o ncurses_CmdLine.o -c interface/ncurses_CmdLine.c $(CFLAGS) $(COLOR)

ncurses_inputString.o:
	@$(CC) -o ncurses_inputString.o -c interface/ncurses_InputString.c $(CFLAGS) $(COLOR)

ncurses_FileSelect.o:
	@$(CC) -o ncurses_FileSelect.o -c interface/ncurses_FileSelect.c $(CFLAGS) $(COLOR)






debug: $(DATA) $(INTERFACE) $(CTRL) 
	@$(CC) -o lauch-debug interface/debug/ncurses_test.c $(INTERFACE) $(DATA) $(CFLAGS) $(COLOR) $(NCURSES) $(MATH) 


ctrl.o:
	@$(CC) -o ctrl.o -c include/ctrl.c $(CFLAGS) $(COLOR)


clean:
	@rm -rf *.o
	@rm -rf lauch
	@rm -rf lauch-debug
	@echo "the project is clean"

cleanSave:
	@rm  	/tmp/lap.save
	@touch 	/tmp/lap.save
	@echo "all saves are clean"
