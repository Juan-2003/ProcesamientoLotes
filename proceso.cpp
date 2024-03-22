#include <iostream>
#include "proceso.h"
#include "operacion.h"

using namespace std;

Proceso::Proceso(){
    setTME(0);
    setTT(0);
    setTR(0);
    setTTbloqueado(0);
    setTEspera(0);
    setTLL(0);
    estadoActual = "Nuevo";
}
Proceso::Proceso(string nombre, Operacion operacion, int id, int TME,
            int TT, int TR){
    setNombre(nombre);
    setOperacion(operacion);
    setId(id);
    setTME(TME);
    setTT(TT);
    setTR(TME);
    setTTbloqueado(0);
    setTEspera(0);
    setTLL(0);
    estadoActual = "Nuevo";
}
Proceso::Proceso(string nombre, Operacion operacion, int id, int TME,
            int idLote){
    setNombre(nombre);
    setOperacion(operacion);
    setId(id);
    setTME(TME);
    this->idLote = idLote;
    setTT(0);
    setTR(TME);
    setTTbloqueado(0);
    setTEspera(0);
    setTLL(0);
    estadoActual = "Nuevo";
}

Proceso::Proceso(string nombre, Operacion operacion, int id, int TME){
    setNombre(nombre);
    setOperacion(operacion);
    setId(id);
    setTME(TME);
    setTT(0);
    setTR(TME);
    setTFinalizacion(00000);
    setTEspera(00000);
    setTTbloqueado(0);
    setTRetorno(000000);
    setTRespuesta(0000000);
    setTLL(0);
    setTServicio(TME);
    estadoActual = "Nuevo";
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

void Proceso::setTTbloqueado(int TTbloqueado){
    this->TTbloqueado = TTbloqueado;
}

void Proceso::setTLL(int TLL){
    this->TLL = TLL;
}

void Proceso::setTFinalizacion(int TFinalizacion){
    this->TFinalizacion = TFinalizacion;
}

void Proceso::setTServicio(int TServicio){
    this->TServicio = TServicio;
}

void Proceso::setTEspera(int TEspera){
    this->TEspera = TEspera;
}

void Proceso::setTRetorno(int TRetorno){
    this->TRetorno = TRetorno;
}

void Proceso::setTRespuesta(int TRespuesta){
    this->TRespuesta = TRespuesta;
}

void Proceso::setEstadoActual(string estadoActual){
    this->estadoActual = estadoActual;
}

//GETTERS
string Proceso::getNombre(){
    return nombre;
}

Operacion& Proceso::getOperacion(){
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

int Proceso::getIdLote(){
    return idLote;
}

int Proceso::getTTbloqueado(){
    return TTbloqueado;
}

int Proceso::getTLL(){
    return TLL;
}

int Proceso::getTFinalizacion(){
    return TFinalizacion;
}

int Proceso::getTServicio(){
    return TServicio;
}

int Proceso::getTEspera(){
    return TEspera;
}

int Proceso::getTRetorno(){
    return TRetorno;
}

int Proceso::getTRespuesta(){
    return TRespuesta;
}

string Proceso::getEstadoActual(){
    return estadoActual;
}

//MANERAS DISTINTAS DE MOSTRAR INFORMACION
string Proceso::loteActual(){
    return "ID: " + to_string(id) + "\n"+
            "TME: "+ to_string(TME)+ "   TT: "+to_string(TT)+ "\n";
}

string Proceso::terminados(){
    return to_string(id) + "    " + operacion.getOperacion()+ "  "+
            operacion.getResultado() +"      "+ to_string(idLote);
}

string Proceso::ejecucion(){
    return "Operacion: "+operacion.getOperacion()+ "\n"+
        "ID:         "+to_string(id);
}

string Proceso::bloqueado(){
    return to_string(id) + "    " + to_string(TTbloqueado);
}

string Proceso::BCP(){
    return to_string(id) + "    "+
            estadoActual+ "    "+
            operacion.getOperacion()+"     "+
            operacion.getResultado()+"     "+
            to_string(TLL)+"          "+
            to_string(TFinalizacion)+"              "+
            to_string(TRetorno)+"        "+
            to_string(TME)+"        "+
            to_string(TServicio)+"            "+
            to_string(TRespuesta)+ "\n";
}



string Proceso::toString(){
    return to_string(id)+ "  "+
        operacion.getOperacion()+"     "+
        operacion.getResultado()+"     "+
        to_string(TME)+"        "+
        to_string(TLL)+"          "+
        to_string(TFinalizacion)+"              "+
        to_string(TServicio)+"            "+
        to_string(TEspera)+"        "+
        to_string(TRetorno)+"        "+
        to_string(TRespuesta)+ "\n";
}
