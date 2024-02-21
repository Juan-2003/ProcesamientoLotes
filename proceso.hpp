#include <string>
#include "operacion.hpp"

#ifndef PROCESO_HPP
#define PROCESO_HPP
class Proceso{
    private:
        std::string nombre;
        Operacion operacion;
        int id;
        int idLote;
        int TME;  //Tiempo total estimado
        int TT;   //Tiempo total
        int TR;   //Tiempo restante

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

        std::string getNombre();
        Operacion& getOperacion();
        int getId();
        int getTME();
        int getTT();
        int getTR();
        int getIdLote();

        std::string loteActual();
        std::string terminados();
        std::string toString();
};
#endif