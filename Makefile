CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
MATH= -lm
NCURSES = -lncurses


all: princ



princ: interface.o data.o
	$(CC) -o launch data.o interface.o $(LDFLAGS)
data.o:
	$(CC) -o data.o data/data_*.c data/data_*.h   $(CFLAGS)
interface.o: data.o
	$(CC) -o interface.o interface/ncurses_*.c interface/ncurses_*.h data.o $(NCURSES)   $(CFLAGS)



