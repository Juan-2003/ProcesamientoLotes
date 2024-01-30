#include <iostream>
#include "operacion.hpp"

using namespace std;

Operacion::Operacion(){}
Operacion::Operacion(int operando1, int operando2, char operador){
    setOperando1(operando1);
    setOperando2(operando2);
    setOperador(operador);
    setResultado(crearResultado(operando1, operando2, operador));

}

void Operacion::setOperando1(int operando1){
    this->operando1 = operando1;
}

void Operacion::setOperando2(int operando2){
    this->operando2 = operando2;
}

void Operacion::setOperador(char operador){
    this->operador = operador;
}

void Operacion::setResultado(int resultado){
    this->resultado = resultado;
}

int Operacion::getOperador1(){
    return operando1;
}

int Operacion::getOperador2(){
    return operando2;
}

char Operacion::getOperador(){
    return operador;
}

int Operacion::getResultado(){
    return resultado;
}

string Operacion::getOperacion(){
    return to_string(operando1) +" " + operador +" " + to_string(operando2);
}

int Operacion::crearResultado(int operando1, int operando2, char operador){
    int resultado;
    switch(operador){
        case '+': resultado = operando1 + operando2;
                break;
        case '-': resultado = operando1 - operando2;
                break;
        case '*': resultado = operando1 * operando2;
                break;
        case '/': resultado = operando1 / operando2;
                break;
        case '%': resultado = operando1 % operando2;
                break;
    }
    return resultado;
}

string Operacion::toString(){
    return to_string(operando1) +" " + operador +" " + to_string(operando2) +" = "+ to_string(resultado);
}

