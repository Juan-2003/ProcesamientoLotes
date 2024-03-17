
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int contador1 = -1;
    int contador2 = -1;
    while (contador1 < 5 && contador2 < 5) {
        // Borramos el contenido anterior de la línea y luego imprimimos el nuevo valor
        std::cout << "\r\033[KLínea 1: " << ++contador1 << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera un segundo antes de la próxima iteración
        std::cout<<"\n";
        std::cout << "\r\033[KLínea 2: " << ++contador2 << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera un segundo antes de la próxima iteración
    }
    std::cout << std::endl; // Agrega una nueva línea después de terminar la animación
    return 0;
}


/*
#include <iostream>
#include <windows.h>

int main() {
    // Obtener el tamaño de la ventana de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int a = 0;
    int b = 0;

    while (a <= 15) {
        // Calcular las coordenadas para imprimir en la mitad de la pantalla
        COORD aCoord = { consoleWidth / 2 - 10, consoleHeight / 2 }; // Posición del contador a
        COORD bCoord = { consoleWidth / 2 - 10, consoleHeight / 2 + 1 }; // Posición del contador b

        // Mueve el cursor a la posición del contador a y lo imprime
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), aCoord);
        std::cout << "Contador a: " << a << std::flush;

        // Mueve el cursor a la posición del contador b y lo imprime
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), bCoord);
        std::cout << "Contador b: " << b << std::flush;

        ++a;
        ++b;
        Sleep(1000);
    }

    return 0;
}*/
