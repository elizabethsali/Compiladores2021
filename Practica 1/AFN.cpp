class AFN
{
    int estado;
    int estadoActual;
    int estadoFinal;
    int[][] transiciones;
    char caracter;
    
    char* alfabeto;
    char* palabra;
    
    void leerPalabra( char* palabra );
    
    void transicion(int estadoActual, char caracter);
    
    void setEstado(int e);
    int getEstado();
    void setEstadoActual(int e);
    int getEstadoActual();
    void setEstadoFinal(int e);
    int getEstadoFinal();
};