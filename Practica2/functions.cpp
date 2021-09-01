#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "functions.h"

using namespace std;

char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','u','v','w','x','y','z','E'};
char parentesis[SIZE];
int posiciones[SIZE];
int pos;
int posicionActual;

void generateAFN(char * regularExpresion){

	int length = strlen(regularExpresion);
	int i = 0;


	for(i = 0; i < length; i++){

		if(regularExpresion[i] == '(' || regularExpresion[i] == ')'){
			parentesis[pos] = regularExpresion[i];
			posiciones[pos] = i;
			pos++;
		}

	}	

	printf("%s\n", parentesis);


	AFN automata;
	automata.estadoActual = 0;
	automata.estadoInicial = 0;
	automata.estadoFinal = 0;
	automata.id = 0;
	automata.posicion = 0;
	int auxI = 0, auxJ = 0;


	for(i = 0; i < length; i++){
		automata = transicion(automata,regularExpresion[i]);
	}

	//automata = readExpresion(automata, length, regularExpresion);


	ofstream myfile;
	myfile.open ("salida.dot");
	myfile << "digraph {\n";
	myfile << "	node [shape=oval]\n";
	myfile << "	rankdir=LR\n";

	for(i = 0; i < automata.posicion; i++){
		myfile << "\n	" << automata.estadosIniciales[i] << " -> " << automata.estadosFinales[i] << " [label=" << automata.characters[i] << "]";
	}	

	myfile << "\n}";
	myfile.close();
}

AFN readExpresion(AFN automata, int length, char * regularExpresion){

	int i = 0;

	for(i = 0; i < length; i++){

		posicionActual = i;

		if(regularExpresion[i] == '('){

			automata = validateParentesis(automata,length, regularExpresion);

		}else{

			automata = transicion(automata,regularExpresion[i]);

		}


	}	

	return automata;

}

AFN validateParentesis(AFN automata, int length, char * regularExpresion){

	int i = 0, j = 0, auxI = 0, auxJ = 0;

	for(i = posicionActual; i < length; i++){

		if(regularExpresion[i] == '('){

			for(j = 0; j < pos; j++){

				if(j > i && parentesis[j] == ')'){

					auxI = i;
					auxJ = j;

					while(auxI <= auxJ){
						automata = transicion(automata,regularExpresion[auxI]);
						auxI++;
					}
					

				}else if(parentesis[j] == '('){

					i = j;

				}

			}


		}

	}	

	return automata;

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

	int i = 0, inicialUnion = 0, finalUnion = 0;

	if(caracter == '('){
		switch(automata.estadoActual){
			case 0:
				automata.estadoActual = 1;
				break;
			case 1:
				automata.estadoActual = 1;
				break;
			case 3:
				automata.estadoActual = 1;
				break;
			case 5:
				automata.estadoActual = 1;
				break;
		}
		
	}else if(isTransition(caracter) == 1){
		switch(automata.estadoActual){
			case 0:
				automata.characters[automata.posicion] = caracter;
				automata.estadosIniciales[automata.posicion] = automata.id;
				automata.id++;
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.id++;
				automata.posicion++;
				automata.estadoActual = 2;
				break;
			case 1:
				automata.characters[automata.posicion] = caracter;
				automata.estadosIniciales[automata.posicion] = automata.id;
				automata.id++;
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.id++;
				automata.posicion++;
				automata.estadoActual = 2;
				break;
			case 2:
				automata.characters[automata.posicion] = caracter;
				automata.estadosIniciales[automata.posicion] = automata.estadosFinales[automata.posicion - 1];
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.id++;
				automata.posicion++;
				automata.estadoActual = 2;
				break;
			case 3:
				automata.characters[automata.posicion] = caracter;
				inicialUnion = automata.id;
				finalUnion = automata.estadosFinales[automata.posicion - 1];
				automata.estadosIniciales[automata.posicion] = automata.id;
				automata.id++;
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.id++;
				automata.posicion++;

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

				for(i = 0; i < automata.posicion; i++){
					automataNew.characters[automataNew.posicion] = automata.characters[i];
					automataNew.estadosIniciales[automataNew.posicion] = automata.estadosIniciales[i];
					automataNew.estadosFinales[automataNew.posicion] = automata.estadosFinales[i];
					automataNew.posicion++;
				}

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automataNew.estadosFinales[automataNew.posicion - 1];
				automataNew.estadosFinales[automataNew.posicion] = automataNew.id;
				automataNew.posicion++;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = finalUnion;
				automataNew.estadosFinales[automataNew.posicion] = automataNew.id;
				automataNew.id++;
				automataNew.posicion++;


				automata = automataNew;

				break;
			case 4:
				automata.characters[automata.posicion] = caracter;
				automata.estadosIniciales[automata.posicion] = automata.estadosFinales[automata.posicion - 1];
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.id++;
				automata.posicion++;
				automata.estadoActual = 2;
				break;
			case 5:
				automata.characters[automata.posicion] = caracter;
				automata.estadosIniciales[automata.posicion] = automata.estadosFinales[automata.posicion - 1];
				automata.estadosFinales[automata.posicion] = automata.id;
				automata.id++;
				automata.posicion++;
				automata.estadoActual = 2;
				break;
		}		
	}else if(caracter == '|'){
		switch(automata.estadoActual){
			case 2:
				automata.estadoActual = 3;
				break;
			case 4:
				automata.estadoActual = 3;
				break;
			case 5:
				automata.estadoActual = 3;
				break;
		}	
	}else if(caracter == ')'){
		switch(automata.estadoActual){
			case 2:
				automata.estadoActual = 4;
				break;
		}		
	}else if(caracter == '*'){

		AFN automataNew;

		switch(automata.estadoActual){
			case 2:

				automataNew.estadoActual = 5;
				automataNew.estadoInicial = automata.id;
				automataNew.estadoFinal = automata.id;
				automataNew.id = automata.id;
				automataNew.posicion = 0;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automataNew.id;
				automataNew.estadosFinales[automataNew.posicion] = automata.estadosIniciales[0];
				automataNew.id++;
				automataNew.posicion++;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automata.estadosFinales[automata.posicion - 1];
				automataNew.estadosFinales[automataNew.posicion] = automataNew.id;
				automataNew.id++;
				automataNew.posicion++;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automata.estadosFinales[automata.posicion - 1];
				automataNew.estadosFinales[automataNew.posicion] = automata.estadosIniciales[0];
				automataNew.posicion++;

				i = 0;

				for(i = 0; i < automata.posicion; i++){
					automataNew.characters[automataNew.posicion] = automata.characters[i];
					automataNew.estadosIniciales[automataNew.posicion] = automata.estadosIniciales[i];
					automataNew.estadosFinales[automataNew.posicion] = automata.estadosFinales[i];
					automataNew.posicion++;
				}

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automataNew.estadosIniciales[0];
				automataNew.estadosFinales[automataNew.posicion] = automataNew.id - 1;
				automataNew.posicion++;


				automata = automataNew;

				break;
			case 4:
				

				automataNew.estadoActual = 5;
				automataNew.estadoInicial = automata.id;
				automataNew.estadoFinal = automata.id;
				automataNew.id = automata.id;
				automataNew.posicion = 0;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automataNew.id;
				automataNew.estadosFinales[automataNew.posicion] = automata.estadosIniciales[0];
				automataNew.id++;
				automataNew.posicion++;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automata.estadosFinales[automata.posicion - 1];
				automataNew.estadosFinales[automataNew.posicion] = automataNew.id;
				automataNew.id++;
				automataNew.posicion++;

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automata.estadosFinales[automata.posicion - 1];
				automataNew.estadosFinales[automataNew.posicion] = automata.estadosIniciales[0];
				automataNew.posicion++;

				i = 0;

				for(i = 0; i < automata.posicion; i++){
					automataNew.characters[automataNew.posicion] = automata.characters[i];
					automataNew.estadosIniciales[automataNew.posicion] = automata.estadosIniciales[i];
					automataNew.estadosFinales[automataNew.posicion] = automata.estadosFinales[i];
					automataNew.posicion++;
				}

				automataNew.characters[automataNew.posicion] = 'E';
				automataNew.estadosIniciales[automataNew.posicion] = automataNew.estadosIniciales[0];
				automataNew.estadosFinales[automataNew.posicion] = automataNew.id - 1;
				automataNew.posicion++;


				automata = automataNew;

				break;
		}
	}


	return automata;
}