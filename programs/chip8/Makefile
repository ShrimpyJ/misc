CC=gcc
OUT=chip8
SOURCE=main.c chip8.c
OBJS=main.o chip8.o
HEADER=chip8.h
FLAGS=-lSDL2 -lSDL2main -g -Wall

all:
	$(CC) $(SOURCE) $(FLAGS) -o $(OUT)

clean:
	rm -f $(OBJS)
