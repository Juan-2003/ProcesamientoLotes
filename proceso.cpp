#include <iostream>
#include "proceso.hpp"
#include "operacion.hpp"

using namespace std;

Proceso::Proceso(){}
Proceso::Proceso(string nombre, Operacion operacion, int id, int TME,
            int TT, int TR){
    setNombre(nombre);
    setOperacion(operacion);
    setId(id);
    setTME(TME);
    setTME(TT);
    setTME(TR);
}
Proceso::Proceso(string nombre, Operacion operacion, int id, int TME){
    setNombre(nombre);
    setOperacion(operacion);
    setId(id);
    setTME(TME);
    TT = 0;
    TR = 0;
}

//SETTERS
void Proceso::setNombre(string nombre){
    this->nombre = nombre;
}

void Proceso::setOperacion(Operacion operacion){
    this->operacion = operacion;
}

void Proceso::setId(int id){
    this->id = id;
}

void Proceso::setTME(int TME){
    this->TME = TME;
}

void Proceso::setTT(int TT){
    this->TT = TT;
}

void Proceso::setTR(int TR){
    this->TR = TR;
}

//GETTERS
string Proceso::getNombre(){
    return nombre;
}

Operacion Proceso::getOperacion(){
    return operacion;
}

int Proceso::getId(){
    return id;
}

int Proceso::getTME(){
    return TME;
}

int Proceso::getTR(){
    return TR;
}

int Proceso::getTT(){
    return TT;
}

string Proceso::loteActual(){
    return "ID: " + to_string(id) + "\n"+
            "TME: "+ to_string(TME)+ "\n";
}

string Proceso::terminados(){
    return to_string(id) + " " + operacion.getOperacion() + " = " + 
            to_string(operacion.getResultado());
}

string Proceso::toString(){
    return "Nombre: " + nombre+ "\n"+
        "Operacion: "+operacion.toString()+ "\n"+
        "ID: "+to_string(id)+ "\n"+
        "TME: "+to_string(TME)+ "\n"+
        "TT: "+to_string(TT)+ "\n"+
        "TR: "+to_string(TR)+ "\n";
}