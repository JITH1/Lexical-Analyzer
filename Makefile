CC = gcc
CFLAGS = -Wall -Wextra

laxical : main.o Lexical.o Valid.o token.o
	$(CC) $(CFLAGS) main.o Lexical.o Valid.o token.o -o laxical
main.o : main.c All_Type.h 
	$(CC) $(CFLAGS) -c main.c
Lexical.o : Lexical.c All_Type.h 
	$(CC) $(CFLAGS) -c Lexical.c
Valid.o : Valid.c All_Type.h 
	$(CC) $(CFLAGS) -c Valid.c
token.o : token.c All_Type.h
	$(CC) $(CFLAGS) -c token.c	

clean :
	rm -f *.o laxical
