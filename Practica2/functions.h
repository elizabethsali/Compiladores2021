const int SIZE = 100;

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

    //int transiciones[][];
    
    /*char* alfabeto;
    char* palabra;
    
    void leerPalabra( char* palabra );
    
    void transicion(char caracter);
    
    void setEstado(int e);
    int getEstado();
    void setEstadoActual(int e);
    int getEstadoActual();
    void setEstadoFinal(int e);
    int getEstadoFinal();*/
};

void generateAFN(char * regularExpresion);
int isTransition(char c);
AFN readExpresion(AFN automata, int length, char * regularExpresion);
AFN validateParentesis(AFN automata, int length, char * regularExpresion);
AFN transicion(AFN automata,char caracter);