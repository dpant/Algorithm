OBJS = Tree.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

Tree.o : Tree.cpp
	$(CC) $(CFLAGS) Tree.cpp

clean:
	\rm *.o *~ p1
