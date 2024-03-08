#include <string>
#include <vector>
#include "operacion.hpp"
#include "proceso.hpp"

#ifndef LOTE_HPP
#define LOTE_HPP
class Lote{
    private:
        int idLote;
        std::vector<Proceso>listaProcesos;

    public:
        Lote();
        Lote(int idLote);

        void agregarProceso(Proceso proceso); //Se agrega un nuevo proceso a la lista 'listaProcesos'
        void setIdLote(int idLote);
        int getIdLote();
        std::vector<Proceso>getListaProcesos();//Devuelve la lista de procesos de cada Lote

        std::string toString();
        //std::string terminados();
};
#endif