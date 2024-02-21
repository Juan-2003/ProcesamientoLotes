#include <iostream>
#include <string>

#ifndef OPERACION_HPP
#define OPERACION_HPP
class Operacion{
    private:
        float operando1;
        float operando2;
        char operador;
        float resultado;

    public:
        Operacion();
        Operacion(float, float, char);

        void setOperando1(float);
        void setOperando2(float);
        void setOperador(char);
        void setResultado(float);

        float getOperador1();
        float getOperador2();
        char getOperador();
        float getResultado();
        std::string getOperacion();

        float crearResultado(float, float, char);
        std::string toString();
};

#endif