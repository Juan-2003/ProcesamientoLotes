#include <vector>
#include <string>
#include "lote.h"
#include "proceso.h"

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


class Menu{
    private:
        static char elegirOperador(int opcionOperador);
        //static void mostrarInfo(std::vector<Proceso>& listaListos);
        static void fin(std::vector<Proceso>& terminados);
        static void comandos(std::vector<Proceso>& listaEjecucion, std::vector<Proceso>& listaActual, char tecla);
        static void mostrarInfo(std::vector<Proceso>& listaListos, std::vector<Proceso>& listaActual, std::vector<Proceso>& listaEjecucion, std::vector<Proceso>& listaTerminados, std::vector<Proceso>& listaBloqueados);
        static void tablaInformacion(std::vector<Proceso>& listaTerminados);
    public:
        static void iniciarMenu();
};

#endif // MENU_H_INCLUDED
