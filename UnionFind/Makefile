OBJS = UFInitialImplementation.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

UFInitialImplementation.o : UFInitialImplementation.cpp
	$(CC) $(CFLAGS) UFInitialImplementation.cpp

clean:
	\rm *.o *~ p1
