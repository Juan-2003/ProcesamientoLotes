#include <iostream>
#include <string>

#ifndef OPERACION_HPP
#define OPERACION_HPP
class Operacion{
    private:
        int operando1;
        int operando2;
        char operador;
        int resultado;
    public:
        Operacion();
        Operacion(int, int, char);

        void setOperando1(int);
        void setOperando2(int);
        void setOperador(char);
        void setResultado(int);

        int getOperador1();
        int getOperador2();
        char getOperador();
        int getResultado();
        std::string getOperacion();

        int crearResultado(int, int, char);
        std::string toString();
};

#endif