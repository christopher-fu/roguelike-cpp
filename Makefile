OBJS = main.o world.o view.o
CC = clang++
DEBUG = -g
CFLAGS = -c -Wall $(DEBUG)
LFLAGS = -Wall -lncurses $(DEBUG)

all: main

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o: view.h view.cpp world.h world.cpp main.cpp
	$(CC) $(CFLAGS) main.cpp

world.o: world.cpp world.h
	$(CC) $(CFLAGS) world.cpp

view.o: view.h world.h view.cpp world.cpp
	$(CC) $(CFLAGS) view.cpp

clean:
	rm *.o main
