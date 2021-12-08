CC = g++
CFLAGS = -pedantic-errors -Wall -std=c++17
 
main: main.o functions.o
	$(CC) $(CFLAGS) -o main main.o functions.o
	@echo
	@echo Compilacion completa
	@echo Para ejecutar el programa utilice el siguiente comando: ./main
	@echo Para limpieza de archivos ejecute: make clean

main.o: main.cpp functions.h
	$(CC) $(CFLAGS) -c main.cpp

functions.o: functions.h

clean :
	rm main main.o functions.o salida.dot
	@echo
	@echo Limpieza completa