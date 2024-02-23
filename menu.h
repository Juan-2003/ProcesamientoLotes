#include <vector>
#include <string>
#include "lote.h"
#include "proceso.h"

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


class Menu{
    private:
        static char elegirOperador(int opcionOperador);
        static void mostrarInfo(std::vector<Lote>& listaLotes);
        static void fin(std::vector<Proceso>& terminados);
        static void comandos(std::vector<Proceso>&listaEjecucion, std::vector<Proceso>&listaActual,char tecla);
    public:
        static void iniciarMenu();
};

#endif // MENU_H_INCLUDED
