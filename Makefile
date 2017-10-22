GCC = gcc
CFLAGS = -Wall -std=c99 -g -c -D_POSIX_C_SOURCE=200112L
LFLAGS = -lz

all: sender receiver clean test

paquet.o: paquet.c
		$(GCC) $(CFLAGS)  paquet.c  $(LFLAGS)

sender.o: sender.c
		$(GCC) $(CFLAGS) sender.c  $(LFLAGS)

receiver.o: receiver.c
		$(GCC) $(CFLAGS) receiver.c $(LFLAGS)

test.o: test.c
		$(GCC) $(CFLAGS) test.c  $(LFLAGS)

sender: paquet.o sender.o
		$(GCC) paquet.o sender.o -o sender $(LFLAGS)

receiver: paquet.o receiver.o
		$(GCC) paquet.o receiver.o -o receiver $(LFLAGS)

test: paquet.o receiver.o sender.o test.o
		$(GCC) paquet.o receiver.o sender.o test.o -o receiver $(LFLAGS)

clean:
			rm -f paquet.o sender.o receiver.o
