class AFN
{
public:
    int estadoInicial;
    int estadoActual;
    int estadoFinal;
    char caracter;

	char characters[100];
	int estadosIniciales[100];
	int estadosFinales[100];
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
void readRegularExpresion(char * regularExpresion, int length);
int readParentesis(char * regularExpresion, int length, int pos);
AFN transicion(AFN automata,char caracter);