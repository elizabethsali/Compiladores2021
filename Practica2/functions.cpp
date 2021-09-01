#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "functions.h"

using namespace std;

char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','u','v','w','x','y','z','E'};
char characters[100];
int estadosIniciales[100];
int estadosFinales[100];

void generateAFN(char * regularExpresion){

	int length = strlen(regularExpresion);
	int id = 0, idC = 0;
	int i = 0;

	/*for(i = 0; i < length; i++){
		if(isTransition(regularExpresion[i]) == 1){
			characters[idC] = regularExpresion[i];
			estadosIniciales[idC] = id;
			id++;
			estadosFinales[idC] = id;
			idC++;
			id++;
		}
	}	*/

	AFN automata;
	automata.estadoActual = 0;
	automata.estadoInicial = 0;
	automata.estadoFinal = 0;
	automata.id = 0;
	automata.posicion = 0;


	for(i = 0; i < length; i++){
		printf("Estado actual: %d\n", automata.estadoActual);
		automata = transicion(automata,regularExpresion[i]);
	}	


	ofstream myfile;
	myfile.open ("salida.dot");
	myfile << "digraph {\n";
	myfile << "	node [shape=oval]\n";

	myfile << "characters\n";
	myfile << characters;
	myfile << "\n";

	myfile << "estadosIniciales\n";
	myfile << estadosIniciales[0];
	myfile << "\n";

	myfile << "estadosFinales\n";
	myfile << estadosFinales[0];
	myfile << "\n";

	myfile << "}";
	myfile.close();
}

int isTransition(char c){
	int i = 0;
	int n = strlen(alfabeto);

	while(i < n){
		if(c == alfabeto[i]){
			return 1;
		}
		i++;
	}

	return 0;
}

AFN transicion(AFN automata,char caracter){

	int i = 0, inicialUnion = 0;

	if(caracter == '('){
		automata.estadoActual = 1;
	}else if(isTransition(caracter) == 1){
		switch(automata.estadoActual){
			case 0:
				automata.characters[automata.posicion] = caracter;
				automata.estadosIniciales[automata.posicion] = automata.id;
				automata.id++;
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.posicion++;
				automata.estadoActual = 2;
				break;
			case 1:
				automata.estadoActual = 2;
				break;
			case 2:
				automata.characters[automata.posicion] = caracter;
				automata.estadosIniciales[automata.posicion] = estadosFinales[automata.posicion - 1];
				automata.id++;
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.posicion++;
				automata.estadoActual = 2;
				break;
			case 3:
				automata.characters[automata.posicion] = caracter;
				automata.id++;
				inicialUnion = automata.id;
				automata.estadosIniciales[automata.posicion] = automata.id;
				automata.id++;
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.posicion++;

				automata.id++;
				AFN automataNew;
				automataNew.estadoActual = 2;
				automataNew.estadoInicial = automata.id;
				automataNew.estadoFinal = automata.id;
				automataNew.id = automata.id;
				automataNew.posicion = 0;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automataNew.id;
				automataNew.estadosFinales[automataNew.posicion] = automata.estadosIniciales[0];
				automataNew.posicion++;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automataNew.id;
				automataNew.id++;
				automataNew.estadosFinales[automataNew.posicion] = inicialUnion;
				automataNew.posicion++;

				i = 0;

				/*for(i = 0; i < automata.posicion; i++){

				}*/

				break;
			case 4:
				automataNew.estadoActual = 2;
				break;
		}		
	}else if(caracter == '|'){
		automata.estadoActual = 3;
	}else if(caracter == ')'){

		automata.estadoActual = 4;
	}


	return automata;
}