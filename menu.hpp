#include <vector>
#include <string>
#include "lote.hpp"
#include "proceso.hpp"

#ifndef MENU_HPP
#define MENU_HPP

class Menu{
    private:
        static char elegirOperador(int opcionOperador);
        static void mostrarInfo(std::vector<Lote>& listaLotes);
        static void fin(std::vector<Proceso>& terminados);
    public:
        static void iniciarMenu();
};

#endif