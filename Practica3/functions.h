const int SIZE = 1000;

class AFN
{
public:
    int estadoInicial;
    int estadoActual;
    int estadoFinal;
    char caracter;

	char characters[SIZE];
	int estadosIniciales[SIZE];
	int estadosFinales[SIZE];
	int id;
	int posicion;

    int lectura;
};

class AFD
{
public:
    int estadoInicial;
    int estadoActual;
    int estadoFinal;
    char caracter;

	char characters[SIZE];
	int estadosIniciales[SIZE];
	int estadosFinales[SIZE];
	int id;
	int posicion;

    int lectura;
};

void generateAFN(char * regularExpresion);
int isTransition(char c);
AFN readExpresion(AFN automata, int length, char * regularExpresion);
AFN validateParentesis(AFN automata, int length, char * regularExpresion, int i);
AFN transicion(AFN automata,char caracter);

AFD convertAFN(AFN automataN);
int validateLetter(char * simbolos, char c);