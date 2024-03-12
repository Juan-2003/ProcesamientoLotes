#include <string>
#include "operacion.h"


#ifndef PROCESO_H_INCLUDED
#define PROCESO_H_INCLUDED

class Proceso{
    private:
        std::string nombre;
        Operacion operacion;
        int id;
        int idLote;
        int TME;  //Tiempo total estimado
        int TT;   //Tiempo total
        int TR;   //Tiempo restante
        int TTbloqueado; //Tiempo total en Bloqueados

    public:
        Proceso();
        Proceso(std::string nombre,Operacion, int id, int TME, int TT, int TR);
        Proceso(std::string nombre,Operacion, int id, int TME, int idLote);
        Proceso(std::string nombre,Operacion, int id, int TME);

        void setNombre(std::string);
        void setOperacion(Operacion);
        void setId(int);
        void setTME(int);
        void setTT(int);
        void setTR(int);
        void setTTbloqueado(int);

        std::string getNombre();
        Operacion& getOperacion();
        int getId();
        int getTME();
        int getTT();
        int getTR();
        int getIdLote();
        int getTTbloqueado();

        std::string loteActual();
        std::string terminados();
        std::string bloqueado();
        std::string toString();
};
#endif
