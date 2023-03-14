OBJS	= client.o clientFuncs.o
SOURCE	= client.c clientFuncs.c
HEADER	= client.h
OUT	= client
CC	 = gcc
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

client.o: client.c
	$(CC) $(FLAGS) client.c 

clientFuncs.o: clientFuncs.c
	$(CC) $(FLAGS) clientFuncs.c 


clean:
	rm -f $(OBJS) $(OUT)
