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

	for(i = 0; i < length; i++){
		if(isTransition(regularExpresion[i]) == 1){
			characters[idC] = regularExpresion[i];
			estadosIniciales[idC] = id;
			id++;
			estadosFinales[idC] = id;
			idC++;
			id++;
		}
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

void readRegularExpresion(char * regularExpresion, int length){
	int i = 0;

	for(i = 0; i < length; i++){
		if(regularExpresion[i] == '('){
			readParentesis(regularExpresion, length, i + 1);
		}else if(regularExpresion[i] == ')'){
			
		}

	}
}

int readParentesis(char * regularExpresion, int length, int pos){
	int i = 0;

	for(i = pos; i < length; i++){
		if(regularExpresion[i] == '('){
			readParentesis(regularExpresion, length, i + 1);
		}else if(regularExpresion[i] == ')'){
			return 0;
		}

	}

	return 0;
}

