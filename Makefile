CC=g++
CFLAGS=-W -Wall  -std=c++11 
LDFLAGS=
EXEC= main

all: $(EXEC)

main : euler.o  main.o randomvar.o
	$(CC) -o main main.o euler.o $(LDFLAGS)

euler.o : euler.cpp
	$(CC) -o euler.o -c euler.cpp $(CFLAGS)


main.o : main.cpp euler.h randomvar.h
	$(CC) -o main.o -c main.cpp  $(CFLAGS)

randomvar.o : randomvar.h
	$(CC) -o randomvar.o -c randomvar.h $(CFLAGS)

clean:
	rm -rf *.o
