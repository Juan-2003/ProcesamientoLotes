#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>
#include <cstdlib>
#include <set>
#include "lote.hpp"
#include "proceso.hpp"
#include "operacion.hpp"


using namespace std;


int contadorGlobal = 0;
char elegirOperador(int opcionOperador){  //Servira para poder elegir el operador segun la opcion del usuario
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

void mostrarInfo(vector<Lote>& listaLotes) {
    int intervalo = 5;
    int lotes_pendientes = 10;
    int TME_cont;
    vector<int> TR_cont;
    vector<int> TT_cont;


    vector<Proceso> listaActual;
    vector<Proceso> listaEjecucion;
    vector<Proceso> listaTerminados;

    for (int i = 0; i < listaLotes.size(); i++) {
        listaActual = listaLotes[i].getListaProcesos();
        for (int j = 0; listaActual.size() != 0; j++) {
            cout << endl << "       LOTE ACTUAL" << endl;
            TME_cont = listaActual[j].getTME();
            TR_cont.push_back(TME_cont);
            TT_cont.push_back(0);  // Inicializar TT_cont con 0
            for(int x=0;x<listaActual.size();x++){
                cout<<listaActual[x].loteActual()<<endl;
            }
            listaEjecucion.push_back(listaActual[0]);
            listaActual.erase(listaActual.begin()); //Se esta eliminando el primer elemento de la lista
            cout << "       EJECUCION" << endl;
            cout<<listaEjecucion[0].toString() << endl;

            // Bucle para decrementar TR y mostrar su valor
            while (TR_cont[j] > 0) {
                cout << "\rTME: " << TME_cont << " TR: " << TR_cont[j] << " TT: " << TT_cont[j] << " Contador: "<< contadorGlobal<< flush;
                Sleep(1000);
                --TR_cont[j];
                ++TT_cont[j];// Incrementa TT
                contadorGlobal++;
            }
            listaTerminados.push_back(listaEjecucion[0]);
            listaEjecucion.pop_back();
            cout<<"\n\n       TERMINADO"<<endl;
            cout<<"ID    OPE    RES    NL"<<endl;
            for(int z=0;z<listaTerminados.size();z++){
                cout<<listaTerminados[z].terminados()<<endl;
                if((z+1) % 4 == 0){
                    cout<<"--------------------------"<<endl;
                }
            }
            Sleep(5000);

            system("cls");
        }
        TR_cont.clear();
        TT_cont.clear();

        
    }
}


int main(){
    vector<Lote>listaLotes;
    vector<Proceso>listaProcesos;
    set<int>listaId;
    int id, opcionOperador, op1, op2, TME;
    int procesosXlote = 4, lotesTotales, contador = 0;
    float cantidadProcesos;
    bool verificarId = true;
    string nombre;
    char operador;
    cout<<"BIENVENIDO"<<endl;
    cout<<"Ingresa la cantidad de procesos que quieres realizar: ";
    cin>>cantidadProcesos;
    cin.ignore();

    lotesTotales = ceil(cantidadProcesos/procesosXlote); //Para saber cuantos lotes habra se divide la cantidad de procesos que ingreso el usuario entre
                                                        //la cantidad de procesos por lote(4) y se redondea hacia arriba.
    do{ //El 'do - while' verifica que la cantiad de procesos sean cumplidos
        Lote lote = Lote();
        for(int i = 0; i < lotesTotales; i++){//Este 'for' controla los lotes
            lote.setIdLote(i+1);
            for(int j = 0; j < 4; j++){//Este 'for' controla que por cada Lote haya 4 procesos
                cout<<"LOTE "<<i+1<<endl;
                cout<<"Nombre: ";
                getline(cin, nombre);

                do{
                    cout<<"ID: ";
                    cin>>id;
                }while(listaId.count(id));//Mientras comprobarID regrese 'true', no saldra del bucle
                listaId.insert(id);
                cout<<endl<<"Ingresa la operacion que quieres realizar"<<endl;
                cout<<"1.Suma\n2.Resta\n3.Multiplicacion\n4.Division\n5.Residuo\nOpcion: ";
                cin>>opcionOperador;

                operador = elegirOperador(opcionOperador);//Se manda a llamar la funcion 'elegirOperador'

                cout<<"Operando1: ";
                cin>>op1;

                do{
                    cout<<"Operando2: ";
                    cin>>op2;
                }while(operador == '/' && op2 == 0);//Esto evita que el usuario quiera dividir entre 0

                cout<<"TME: ";
                cin>>TME;
                cout<<endl<<endl;
                cin.ignore();

                Operacion operacion = Operacion(op1, op2, operador); //Se crea un objeto tipo 'Operacion'
                Proceso proceso = Proceso(nombre, operacion, id, TME, i+1);//Se crea un objeto tipo 'Proceso'
                //Lote lote = Lote(i+1); //Se crea un objeto tipo 'Lote'
                lote.agregarProceso(proceso);//Al lote acutal se le agrega un proceso
                //listaLotes.push_back(lote);//A la lista de lotes se a�ade el lote actual
                contador++; //Ayuda a verificar si la cantidad de procesos se ha cumplido
                if(contador == cantidadProcesos){
                    break;
                }
                verificarId = true; //Se reinicia el valor para la siguiente iteracion
            }
            listaLotes.push_back(lote);
            lote = Lote();
        }
    }while(contador != cantidadProcesos);
    mostrarInfo(listaLotes);
}