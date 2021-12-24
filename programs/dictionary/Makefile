CC=gcc
OBJS=dictionary.o
SRC=dictionary.c
INCDIR=/home/pete/misc/c/include
LIBDIR=/home/pete/misc/c/lib
LIB=-lfile2lines
OUT=dictionary

all:
	gcc -o $(OUT) -I$(INCDIR) $(SRC) -L$(LIBDIR) $(LIB)

make clean:
	rm *.o
