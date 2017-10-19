GCC = gcc
CFLAGS = -Wall -std=c99 -g -c -D_POSIX_C_SOURCE=200112L
LFLAGS = -lz

all: sender receiver clean

paquet.o: paquet.c
		$(GCC) $(CFLAGS) $(LFLAGS) paquet.c

sender.o: sender.c
		$(GCC) $(CFLAGS) sender.c

receiver.o: receiver.c
		$(GCC) $(CFLAGS) receiver.c

sender: paquet.o sender.o
		$(GCC) paquet.o sender.o -o sender

receiver: paquet.o receiver.o
		$(GCC) paquet.o receiver.o -o receiver

clean:
			rm -f paquet.o sender.o receiver.o
