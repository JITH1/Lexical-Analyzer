CC = gcc
CFLAGS = -Wall -Wextra

laxical : main.o Lexical.o Valid.o 
	$(CC) $(CFLAGS) main.o Lexical.o Valid.o -o laxical
main.o : main.c All_Type.h Flags.h Valid.h Lexical.h
	$(CC) $(CFLAGS) -c main.c
Lexical.o : Lexical.c All_Type.h Flags.h Lexical.h
	$(CC) $(CFLAGS) -c Lexical.c
Valid.o : Valid.c All_Type.h Flags.h Valid.h 
	$(CC) $(CFLAGS) -c Valid.c

clean :
	rm -f *.o laxical
