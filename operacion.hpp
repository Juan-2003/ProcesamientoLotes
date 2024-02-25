#include <iostream>
#include <string>

#ifndef OPERACION_HPP
#define OPERACION_HPP
class Operacion{
    private:
        float operando1;
        float operando2;
        char operador;
        std::string resultado;
    public:
        Operacion();
        Operacion(float, float, char);

        void setOperando1(float);
        void setOperando2(float);
        void setOperador(char);
        void setResultado(std::string);

        float getOperador1();
        float getOperador2();
        char getOperador();
        std::string getResultado();
        std::string getOperacion();

        std::string crearResultado(float, float, char);
        std::string toString();
};

#endif