OBJS	= arbiter.o arbiterFuncs.o
SOURCE	= arbiter.c arbiterFuncs.c
HEADER	= arbiter.h
OUT	= arbiter
CC	 = gcc
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

arbiter.o: arbiter.c
	$(CC) $(FLAGS) arbiter.c 

arbiterFuncs.o: arbiterFuncs.c
	$(CC) $(FLAGS) arbiterFuncs.c 


clean:
	rm -f $(OBJS) $(OUT)

