#include <vector>
#include <string>
#include "lote.hpp"

#ifndef MENU_HPP
#define MENU_HPP

class Menu{
    private:
        static char elegirOperador(int opcionOperador);
        static void mostrarInfo(std::vector<Lote>& listaLotes);
    public:
        static void iniciarMenu();
};

#endif