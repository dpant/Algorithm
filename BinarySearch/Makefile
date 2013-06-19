OBJS = BinarySearch.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

BinarySearch.o : BinarySearch.cpp
	$(CC) $(CFLAGS) BinarySearch.cpp

clean:
	\rm *.o *~ p1
