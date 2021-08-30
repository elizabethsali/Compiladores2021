#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	char regularExpresion[100];
	
	printf("\nIngrese la expresion regular: ");
	cin.get(regularExpresion, 100, '\n');
	
	printf("\nEntrada: %s\n", regularExpresion);

	generateAFN(regularExpresion);

	return 0;
}