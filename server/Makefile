OBJS	= server.o serverFuncs.o
SOURCE	= server.c serverFuncs.c
HEADER	= server.h
OUT	= server
CC	 = gcc
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

server.o: server.c
	$(CC) $(FLAGS) server.c 

serverFuncs.o: serverFuncs.c
	$(CC) $(FLAGS) serverFuncs.c 


clean:
	rm -f $(OBJS) $(OUT)
