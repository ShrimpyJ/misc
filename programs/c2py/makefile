CC = gcc

CFLAGS = -g -Wall

c2py: c2py.o lexer.o
	$(CC) $(CFLAGS) -o c2py c2py.o lexer.o

c2py.o: c2py.c lexer.c
	$(CC) $(CFLAGS) -c c2py.c

lexer.o: lexer.c
