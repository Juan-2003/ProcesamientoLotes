#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iomanip>
#include <cstdlib>
#include <set>
#include "lote.h"
#include "proceso.h"
#include "operacion.h"
#include "menu.h"

using namespace std;

int contadorGlobal = 0;
char Menu::elegirOperador(int opcionOperador){  //Servira para poder elegir el operador segun la opcion del usuario
    char operador;
    switch(opcionOperador){
        case 1: operador = '+';
                break;
        case 2: operador = '-';
                break;
        case 3: operador = '*';
                break;
        case 4: operador = '/';
                break;
        case 5: operador = '%';
                break;
        default:
            cout<<"Signo no disponible";
    }
    return operador;
}

void Menu::fin(vector<Proceso>& terminados){
    contadorGlobal--;
    system("cls");
    cout << endl << "       LOTE ACTUAL" << endl;
    cout<<endl<<endl;
    cout << "       EJECUCION" << endl;
    cout<<endl<<endl;
    cout<<"                Contador: "<<contadorGlobal;
    cout<<"\n\n       TERMINADO"<<endl;
    cout<<"ID        OPE                RES        NL"<<endl;
    for(int z = 0; z < terminados.size();z++){
                cout<<terminados[z].terminados()<<endl;
                if((z+1) % 4 == 0){
                    cout<<"------------------------------------------------------------------"<<endl;
                }
            }
    cout<<"Presione enter para continuar.....";
    cin.get();
    system("cls");

}

void Menu::mostrarInfo(vector<Proceso>& listaListos) {
    int TME_cont;
    int TT_cont;
    int actualTR;


    vector<Proceso> listaActual(listaListos.begin(),listaListos.begin()+4);
    vector<Proceso> listaEjecucion;
    vector<Proceso> listaTerminados;
    vector<Proceso> listaBloqueados;
    listaListos.erase(listaListos.begin(),listaListos.begin()+4);
        for (int j = 0; listaActual.size() != 0; j++) {
            system("cls");
            cout<<"J: "<<j<<endl;
            cout<<"Nuevos: "<<listaListos.size()<<endl;

            // -------------  LOTE ACTUAL -----------------------
            cout << endl << "       LOTE ACTUAL" << endl;
            TME_cont = listaActual[0].getTME();//Se toma TME del proceso actual
            TT_cont = listaActual[0].getTT();//SE TOMA TT del proceso actual

            for(int x=0;x<listaActual.size();x++){
                cout<<listaActual[x].loteActual()<<endl;
            }
            listaEjecucion.push_back(listaActual[0]);
            listaActual.erase(listaActual.begin()); //Se esta eliminando el primer elemento de la lista


            // ---------------- EJECUCION -----------------------------
            cout << "       EJECUCION" << endl;
            cout<<listaEjecucion[0].toString() << endl;

            // Bucle para decrementar TR y mostrar su valor
            char tecla;
            bool bandera= false;
            actualTR = listaEjecucion[0].getTR();
            while (actualTR >=0) {
                cout << "\rTME: " << TME_cont << " TR: " << actualTR << " TT: " << TT_cont << " Contador: "<< contadorGlobal<< flush;
                Sleep(1000);
                --actualTR;
                ++TT_cont;// Incrementa TT
                contadorGlobal++;


                if(_kbhit()){ //Mientras los contadores avanzan se verifica si se tecleo algo
                    tecla = _getch(); //Lo que se tecleo lo guardo en tecla
                    comandos(listaEjecucion, listaBloqueados, tecla);
                    /* En la funcion "comandos" se esta haciendo pop a la lista de ejecucion cuando se usa
                        'e' y se inserta ese proceso en listaActual, por lo que para establecer bien los valores
                        del proceso, se toma la ultima posicion de la listaActual
                    */
                    if(tecla == 'e'){
                        /*listaActual[listaActual.size()-1].setTR(actualTR);
                        listaActual[listaActual.size()-1].setTT(TT_cont);*/
                        listaBloqueados[0].setTR(actualTR);
                        listaBloqueados[0].setTT(TT_cont);
                        bandera = true;
                    }
                    else if(tecla == 'w'){
                        listaEjecucion[0].setTR(actualTR);
                        listaEjecucion[0].setTT(actualTR);
                        break;
                    }
                }
                for(int i = 0; i < listaBloqueados.size(); i++){
                    listaBloqueados[i].setTTbloqueado(listaBloqueados[i].getTTbloqueado()+1);
                    if(listaBloqueados[i].getTTbloqueado()==8){
                        listaActual.push_back(listaBloqueados[i]);
                        listaBloqueados[i].setTTbloqueado(0);
                        listaBloqueados.pop_back();
                    }
                }
            }

            cout <<endl<< "       BLOQUEADOS" << endl;
            cout<<"ID"<<"   "<<"TT"<<endl;
            for(int i = 0; i < listaBloqueados.size(); i++){
                cout<<listaBloqueados[i].bloqueado()<<endl;
            }


            if(!bandera){//Si no se ha presionado la tecla 'e', se quitara lo que hay en la lista de ejecucion
                listaEjecucion.pop_back();
                listaTerminados.push_back(listaEjecucion[0]);
                listaActual.push_back(listaListos[0]);
            }


            cout<<"\n\n       TERMINADO"<<endl;
            cout<<"ID        OPE                RES        NL"<<endl;
            for(int z=0;z<listaTerminados.size();z++){
                cout<<listaTerminados[z].terminados()<<endl;
                if((z+1) % 4 == 0){
                    cout<<"--------------------------"<<endl;
                }
            }
            system("PAUSE");
            Sleep(1000);

        }

    fin(listaTerminados);
}

void Menu::comandos(vector<Proceso>& listaEjecucion, vector<Proceso>& listaBloqueados, char tecla) {
    //cout<<
    switch(tecla) {
        case 'w': //Interrupcion
            listaEjecucion[0].getOperacion().setResultado("ERROR"); //El resultado se modifica, debe aparecer ERROR o algo asi, solo queda eso.
            break;
        case 'p': //Pausa
            char otraTecla;
            do {
                if(_kbhit()) {
                    otraTecla = _getch(); //Se guarda la tecla seleccionada
                }
            } while(otraTecla != 'c'); //El programa seguira pausado mientras no se haga click en 'c'
            break;
        case 'e':
            listaBloqueados.insert(listaBloqueados.end(),listaEjecucion[0]);
            listaEjecucion.pop_back();
            break;
    }
}

void Menu::iniciarMenu(){
    vector<Proceso>listaProcesos;
    int opcionOperador,TME;
    static int id=0;
    float op1, op2;
    float cantidadProcesos;
    string nombre;
    char operador;
    cout<<"BIENVENIDO"<<endl;
    cout<<"Ingresa la cantidad de procesos que quieres realizar: ";
    cin>>cantidadProcesos;
    //cin.ignore();
    srand(time(NULL));
            for(int j = 0; j < cantidadProcesos; j++){//Este 'for' controla que por cada Lote haya 4 procesos
                id++;//Se va sumando el id
                opcionOperador = 1+rand()%(6-1);//Operador random
                operador = elegirOperador(opcionOperador);//Se manda a llamar la funcion 'elegirOperador'
                op1 = 1+rand()%(1001-1);//operador 1
                op2 = 1+rand()%(1001-1); //operador 2
                TME = 5+rand()%(19-5); //TME
                Operacion operacion = Operacion(op1, op2, operador); //Se crea un objeto tipo 'Operacion'
                Proceso proceso = Proceso(nombre, operacion, id, TME, j+1);//Se crea un objeto tipo 'Proceso'
                listaProcesos.push_back(proceso);
            }
    cin.ignore();
    mostrarInfo(listaProcesos);
}
