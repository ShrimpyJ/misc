CC=gcc
NAME=chip8
CFLAGS=`sdl2-config --cflags ` -g -W -I `sdl2-config --prefix`/include/

LDFLAGS=`sdl2-config --libs`

OBJS=main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

chip8: main.o
	gcc $(CFLAGS) -o chip8 main.o -L $(LDFLAGS)

clean:
	rm -f *.o
