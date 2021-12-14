#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "functions.h"

using namespace std;

char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','u','v','w','x','y','z','E'};
char status[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

AFN generateAFN(char * regularExpresion){

	int length = strlen(regularExpresion);
	int i = 0;

	AFN automata;
	automata.estadoActual = 0;
	automata.estadoInicial = 0;
	automata.estadoFinal = 0;
	automata.id = 0;
	automata.posicion = 0;
	automata.lectura = 0;

	printf("\nLeyendo expresion regular.\n");
	automata = readExpresion(automata, length, regularExpresion);

	printf("Generando archivo de AFN.\n");

	char archivo[] = "AFN.dot";
	ofstream myfile;
	myfile.open (archivo);
	myfile << "digraph {\n";
	myfile << "	node [shape=circle style=filled fillcolor=white]\n";
	myfile << "	rankdir=LR\n";

	for(i = 0; i < automata.posicion; i++){

		if(i == 0)
			myfile << "\n	" << automata.estadosIniciales[i] << " [fillcolor=aquamarine shape=doublecircle]\n";

		myfile << "\n	" << automata.estadosIniciales[i] << " -> " << automata.estadosFinales[i] << " [label=" << automata.characters[i] << "]";
	}	

	myfile << "\n\n	" << automata.estadosFinales[automata.posicion - 1] << " [fillcolor=coral shape=doublecircle]\n";

	myfile << "\n}";
	myfile.close();

	printf("Salida: %s\n",archivo);

	return automata;

}

AFN readExpresion(AFN automata, int length, char * regularExpresion){

	int i = 0;

	for(i = 0; i < length; i++){

		automata.lectura = i;


		if(regularExpresion[i] == '('){

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

			automata = validateParentesis(automata,length,regularExpresion,i);

			i = automata.lectura + 1;

		}else
			automata = transicion(automata,regularExpresion[i]);


	}	

	return automata;

}

AFN validateParentesis(AFN automata, int length, char * regularExpresion, int i){

	int j = 0;

	for(j = i + 1; j < length; j++){

		automata.lectura = j;

		if(regularExpresion[j] == '('){

			automata = validateParentesis(automata,length,regularExpresion,j);

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

			break;

		}else
			automata = transicion(automata,regularExpresion[j]);

	}

	return automata;

}

int isTransition(char c){

	int i = 0;
	int n = strlen(alfabeto);

	while(i < n){

		if(c == alfabeto[i])
			return 1;
		
		i++;

	}

	return 0;

}

AFN transicion(AFN automata,char caracter){

	int i = 0, inicialUnion = 0, finalUnion = 0;
	AFN automataNew;

	if(isTransition(caracter) == 1){

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

				automataNew.estadoActual = 2;
				automataNew.estadoInicial = automata.id;
				automataNew.estadoFinal = automata.id;
				automataNew.id = automata.id;
				automataNew.posicion = 0;
				automataNew.lectura = automata.lectura;

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

		if(automata.estadoActual == 2)
			automata.estadoActual = 4;

	}else if(caracter == '*'){

		switch(automata.estadoActual){
			case 2:
				automataNew.estadoActual = 5;
				automataNew.estadoInicial = automata.id;
				automataNew.estadoFinal = automata.id;
				automataNew.id = automata.id;
				automataNew.posicion = 0;
				automataNew.lectura = automata.lectura;

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
				automataNew.lectura = automata.lectura;

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

AFD convertAFN(AFN automataN){

	AFD automataD;
	automataD.estadoActual = 0;
	automataD.estadoInicial = 0;
	automataD.estadoFinal = 0;
	automataD.id = 0;
	automataD.posicion = 0;
	automataD.lectura = 0;

	char simbolos[SIZE];
	int length = 0;
	int i = 0;
	int j = 0;

	for(i = 0; i < automataN.posicion; i++){

		if(validateLetter(simbolos, length, automataN.characters[i])){
			printf("\n%c",automataN.characters[i]);
			simbolos[length] = automataN.characters[i];
			length++;
		}

	}

	printf("\nExisten %d letras diferentes.\n",length);

	int hasE = 0;
	

	if(!validateLetter(simbolos, length, 'E')){
		char simbolosAux[SIZE];
		simbolosAux[0] = 'E';
		j = 0;
		j++;
		i = 0;
		

		for(i = 0; i < length; i++){
			if(simbolos[i] != 'E'){
				simbolosAux[j] = simbolos[i];
				j++;
			}
		}

		for(i = 0; i < length; i++)
			simbolos[i] = simbolosAux[i];

		hasE = 1;

	}

	int consecutiveFlag = 0;

	j = 0;

	for(j = 0; j < length; j++){

		
		for(i = 0; i < automataN.posicion; i++){

			if(automataN.characters[i] == 'E' && automataN.characters[i] == simbolos[j] && hasE){

				if((automataN.estadosIniciales[0] == automataN.estadosIniciales[i] || consecutiveFlag) && validateDuplicate(automataN,automataD,i)){
 
					if(i == 0){
						automataD.estadosIniciales[automataD.posicion] = automataD.id;
						automataD.characters[automataD.posicion] = automataN.characters[i];
						automataD.estadosFinales[automataD.posicion] = automataN.estadosIniciales[i];
						automataD.posicion++;
					}

					automataD.estadosIniciales[automataD.posicion] = automataD.id;
					automataD.characters[automataD.posicion] = automataN.characters[i];
					automataD.estadosFinales[automataD.posicion] = automataN.estadosFinales[i];
					automataD.posicion++;
				}
				
			}else if(automataN.characters[i] == simbolos[j] && !hasE){

				if(validateDuplicate(automataN,automataD,i)){

					automataD.estadosIniciales[automataD.posicion] = automataD.id;
					automataD.characters[automataD.posicion] = automataN.characters[i];
					automataD.estadosFinales[automataD.posicion] = automataN.estadosFinales[i];
					automataD.posicion++;
				}
				
			}

			if(i >= 1){
				if(automataN.characters[i] == automataN.characters[i-1])
					consecutiveFlag = 1;
				else
					consecutiveFlag = 0;
			}
			
		}

		automataD.id++;

	}

	printf("Generando archivo de AFD.\n");

	char archivo[] = "AFD.dot";
	ofstream myfile;
	myfile.open (archivo);
	myfile << "digraph {\n";
	myfile << "	node [shape=circle style=filled fillcolor=white]\n";
	myfile << "	rankdir=LR\n";

	for(i = 0; i < automataD.posicion; i++){

		if(i == 0)
			myfile << "\n	" << status[automataD.estadosIniciales[i]] << " [fillcolor=aquamarine shape=doublecircle]\n";

		myfile << "\n	" << status[automataD.estadosIniciales[i]] << " -> " << automataD.estadosFinales[i] << " [label=" << automataD.characters[i] << "]";
	}	

	myfile << "\n\n	" << automataD.estadosFinales[automataD.posicion - 1] << " [fillcolor=coral shape=doublecircle]\n";

	myfile << "\n}";
	myfile.close();

	printf("Salida: %s\n",archivo);

	return automataD;

}

int validateLetter(char * simbolos, int length, char c){

	int i = 0;

	for(i = 0; i < length; i++){
		if(simbolos[i] == c)
			return 0;
	}

	return 1;
}

int validateDuplicate(AFN automataN, AFD automataD, int p){
	int i = 0;

	for(i = 0; i < automataD.posicion; i++){
		if(automataD.estadosIniciales[i] == automataD.id && automataD.characters[i] == automataN.characters[p] && automataD.estadosFinales[i] == automataN.estadosFinales[p])
			return 0;
	}

	return 1;
}

AFD search(AFN automataN, AFD automataD, char c){

	int i = 0;
	int consecutiveFlag = 0;
	int changeFlag = 0;


	for(i = 0; i < automataN.posicion; i++){

		if(automataN.characters[i] == 'E' && automataN.characters[i] == c){

			if((automataN.estadosIniciales[0] == automataN.estadosIniciales[i] || consecutiveFlag) && validateDuplicate(automataN,automataD,i)){

				if(i == 0){
					automataD.estadosIniciales[automataD.posicion] = automataD.id;
					automataD.characters[automataD.posicion] = automataN.characters[i];
					automataD.estadosFinales[automataD.posicion] = automataN.estadosIniciales[i];
					automataD.posicion++;
				}

				automataD.estadosIniciales[automataD.posicion] = automataD.id;
				automataD.characters[automataD.posicion] = automataN.characters[i];
				automataD.estadosFinales[automataD.posicion] = automataN.estadosFinales[i];
				automataD.posicion++;
			}
			
		}else if(automataN.characters[i] == c){

			if(validateDuplicate(automataN,automataD,i)){

				automataD.estadosIniciales[automataD.posicion] = automataD.id;
				automataD.characters[automataD.posicion] = automataN.characters[i];
				automataD.estadosFinales[automataD.posicion] = automataN.estadosFinales[i];
				automataD.posicion++;
			}
			
		}

		if(i >= 1){
			if(automataN.characters[i] == automataN.characters[i-1])
				consecutiveFlag = 1;
			else
				consecutiveFlag = 0;

			if(automataD.estadosIniciales[i] == automataD.estadosIniciales[i-1])
					changeFlag = 0;
				else
					changeFlag = 1;
		}
		
	}
}