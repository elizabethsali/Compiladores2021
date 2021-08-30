CC = g++
CFLAGS = -pedantic-errors -Wall -std=c++17
 
main: main.o functions.o
	$(CC) $(CFLAGS) -o main main.o functions.o
 
main.o: main.cpp functions.h
	$(CC) $(CFLAGS) -c main.cpp
 
functions.o: functions.h

clean :
	rm main main.o functions.o