CC=g++
CFLAGS=-W -Wall  -std=c++11 
LDFLAGS=
EXEC= main

all: $(EXEC)

main : euler.o  main.o 
	$(CC) -o main main.o euler.o $(LDFLAGS)

euler.o : euler.cpp
	$(CC) -o euler.o -c euler.cpp $(CFLAGS)


main.o : main.cpp euler.h
	$(CC) -o main.o -c main.cpp  $(CFLAGS)



clean:
	rm -rf *.o