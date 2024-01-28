#include <iostream>
#include <string>

#ifndef OPERACION_HPP
#define OPERACION_HPP
class Operacion{
    private:
        int operando1;
        int operando2;
        char operador;
    public:
        Operacion();
        Operacion(int, int, char);

        void setOperando1(int);
        void setOperando2(int);
        void setOperador(char);

        int getOperador1();
        int getOperador2();
        char getOperador();

        std::string toString();
};

#endif