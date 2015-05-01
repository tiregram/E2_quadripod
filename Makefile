CC=gcc
CFLAGS=-Wextra -Wall -std=gnu99 
LDFLAGS=
MATH= -lm
NCURSES = -lncurses
COLOR = -fdiagnostics-color=auto

DATA  = data_struct.o 
INTERFACE =  ncurses_Interface.o ncurses_inputSelect.o ncurses_ServoWindow.o ncurses_MessageBox.o ncurses_Frame.o ncurses_CmdLine.o



all: princ


princ: $(DATA) $(INTERFACE)  
	@$(CC) -o lauch  main.c $(LDFLAGS) $(COLOR) $(NCURSES) $(MATH) $(INTERFACE) $(DATA)
data_struct.o:
	@$(CC) -o data_struct.o -c data/data_struct.c $(CFLAGS) $(COLOR)

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
	
ncurses_CmdLine.o:
	@$(CC) -o ncurses_CmdLine.o -c interface/ncurses_CmdLine.c $(CFLAGS) $(COLOR)
	
debug: $(DATA) $(INTERFACE) 
	@$(CC) -o lauch-debug interface/debug/ncurses_test.c $(INTERFACE) $(DATA) $(CFLAGS) $(COLOR) $(NCURSES) $(MATH) 



clean:
	@rm -rf *.o
	@rm -rf lauch
