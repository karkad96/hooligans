OBJS	= hooligan.o hooliganFuncs.o
SOURCE	= hooligan.c hooliganFuncs.c
HEADER	= hooligan.h
OUT	= hooligan
CC	 = gcc
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

hooligan.o: hooligan.c
	$(CC) $(FLAGS) hooligan.c 

hooliganFuncs.o: hooliganFuncs.c
	$(CC) $(FLAGS) hooliganFuncs.c 


clean:
	rm -f $(OBJS) $(OUT)
