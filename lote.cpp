#include <iostream>
#include "lote.hpp"
#include "operacion.hpp"
#include "proceso.hpp"

using namespace std;

Lote::Lote(){}
Lote::Lote(int idLote){
    setIdLote(idLote);
}

void Lote::agregarProceso(Proceso proceso){
    listaProcesos.push_back(proceso);
}
void Lote::setIdLote(int idLote){
    this->idLote = idLote;
}

int Lote::getIdLote(){
    return idLote;
}

vector<Proceso> Lote::getListaProcesos(){
    return listaProcesos;
}

string Lote::toString(){
    string cadena = "Lote ID: " + to_string(idLote) + "\n";
    for(int i = 0; i < listaProcesos.size(); i++){ //Se itera a traves de la lista de procesos para obtener el toString de cada uno
        cadena += listaProcesos[i].toString() + "\n";
    }
    return cadena;
}