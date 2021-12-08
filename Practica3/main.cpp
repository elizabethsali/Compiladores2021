//dot -Tjpg salida.dot -o salida.jpg

//Elizabeth Salinas SIerra - 3CV16

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	char regularExpresion[SIZE];

	printf("\nCompiladores\n");
	printf("Practica 2  - Construcciones de Thompson\n");
	printf("Elizabeth Salinas Sierra - 3CV16\n");
	
	printf("\nIngrese la expresion regular: ");
	cin.get(regularExpresion, SIZE, '\n');
	
	printf("\nEntrada: %s\n", regularExpresion);

	generateAFN(regularExpresion);

	return 0;
}