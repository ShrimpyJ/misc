CC=gcc
OUT=mygame
SOURCE=main.c vec3.c
OBJS=main.o
HEADER=vec3.h
FLAGS=-lSDL2 -lSDL2main -g -Wall -lm

all:
	$(CC) $(SOURCE) $(FLAGS) -o $(OUT)

clean:
	rm -f $(OBJS)
