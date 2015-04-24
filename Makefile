CC=gcc
CFLAGS=-Wextra -Wall -std=gnu99 
LDFLAGS=
MATH= -lm
NCURSES = -lncurses
COLOR = -fdiagnostics-color=auto

DATA  = data_struct.o 
INTERFACE =  ncurses_inputSelect.o ncurses_ServoWindow.o



all: princ


princ: $(DATA) $(INTERFACE)  
	@$(CC) -o lauch ncurses_inputSelect.o data_struct.o ncurses_Interface.o main.c $(LDFLAGS) $(COLOR) $(NCURSES) $(MATH) 

data_struct.o:
	@$(CC) -o data/data_struct.o -c data/data_struct.c $(CFLAGS) $(COLOR)

ncurses_Interface.o: 
	@$(CC) -o interface/ncurses_Interface.o -c interface/ncurses_Interface.c  $(CFLAGS) $(COLOR)

ncurses_inputSelect.o:
	@$(CC) -o interface/ncurses_inputSelect.o -c interface/ncurses_inputSelect.c $(CFLAGS) $(COLOR)

ncurses_ServoWindow.o: 
	@$(CC) -o interface/ncurses_ServoWindow.o -c interface/ncurses_ServoWindow.c $(CFLAGS) $(COLOR)
	
debug: $(DATA) $(INTERFACE) 
	@$(CC) -o lauch-debug interface/ncurses_ServoWindow.o interface/ncurses_inputSelect.o data/data_struct.o $(CFLAGS) $(COLOR)


clean:
	@rm -rf *.o
	@rm -rf lauch
