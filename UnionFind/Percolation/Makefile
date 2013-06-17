OBJS = Percolation.o UnionFind.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

Percolation.o : Percolation.cpp
	$(CC) $(CFLAGS) Percolation.cpp

UnionFind.o :  ../UnionFind.cpp
	$(CC) $(CFLAGS) ../UnionFind.cpp

clean:
	\rm *.o *~ p1
