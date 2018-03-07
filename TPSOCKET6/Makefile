# $Id$

GCC=gcc
FILES=tcp_serveur.c tcp_client.c
OBJ=$(FILES:%.c=%.o)
BIN=tcp_serveur tcp_client

all: $(OBJ)
	$(GCC) -o tcp_serveur tcp_serveur.o -lpthread 
	$(GCC) -o tcp_client tcp_client.o -lpthread 

clean:
	rm -f *~ *.o $(BIN)

.SUFFIXES: .c .o

.zf.res:
	$(GCC) -c $<
