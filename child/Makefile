OBJS	= child.o childFuncs.o
SOURCE	= child.c childFuncs.c
HEADER	= child.h
OUT	= child
CC	 = gcc
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

child.o: child.c
	$(CC) $(FLAGS) child.c 

childFuncs.o: childFuncs.c
	$(CC) $(FLAGS) childFuncs.c 


clean:
	rm -f $(OBJS) $(OUT)

