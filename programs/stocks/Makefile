CC=gcc
LD=gcc

stockprgm: main.o stock.o linkedList.o
	cc main.o stock.o linkedList.o -o stockprgrm

main.o: main.c
	cc -c main.c
stock.o: stock.c stock.h date.h
	cc -c stock.c
linkedList.o: linkedList.c linkedList.h stock.h
	cc -c linkedList.c

clean:
	rm -f *.o $(TARGETS)
