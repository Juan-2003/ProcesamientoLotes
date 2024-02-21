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
#include "menu.hpp"

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

void Menu::mostrarInfo(vector<Lote>& listaLotes) {
    int lotesPendientes = listaLotes.size();
    int TME_cont;
    vector<int> TR_cont;
    vector<int> TT_cont;

    vector<Proceso> listaActual;
    vector<Proceso> listaEjecucion;
    vector<Proceso> listaTerminados;

    for (int i = 0; i < listaLotes.size(); i++) {
        listaActual = listaLotes[i].getListaProcesos();
        for (int j = 0; listaActual.size() != 0; j++) {
            system("cls");
            if(lotesPendientes > 1){
                cout<<lotesPendientes;
            }

            // -------------  LOTE ACTUAL -----------------------
            cout << endl << "       LOTE ACTUAL" << endl;
            TME_cont = listaActual[j].getTME();
            TR_cont.push_back(TME_cont);
            TT_cont.push_back(0);  // Inicializar TT_cont con 0
            for(int x=0;x<listaActual.size();x++){
                cout<<listaActual[x].loteActual()<<endl;
            }
            listaEjecucion.push_back(listaActual[0]);
            listaActual.erase(listaActual.begin()); //Se esta eliminando el primer elemento de la lista
            
            
            // ---------------- EJECUCION -----------------------------
            cout << "       EJECUCION" << endl;
            cout<<listaEjecucion[0].toString() << endl;

            // Bucle para decrementar TR y mostrar su valor
            int tecla;
            while (TR_cont[j] >= 0) {
                cout << "\rTME: " << TME_cont << " TR: " << TR_cont[j] << " TT: " << TT_cont[j] << " Contador: "<< contadorGlobal<< flush;
                Sleep(1000);
                --TR_cont[j];
                ++TT_cont[j];// Incrementa TT
                contadorGlobal++;

                if(_kbhit()){ //Mientras los contadores avanzan se verifica si se tecleo algo
                    tecla = _getch(); //Lo que se tecleo lo guardo en tecla
                    comandos(listaEjecucion, tecla); //Llamo la lista de comandos para realizar acciones necesarias
                    if(tecla == 'w'){ //Se interrumpe el programa, asi que se rompe el bucle actual
                        break;
                    }
                }
            }

            listaTerminados.push_back(listaEjecucion[0]);
            listaEjecucion.pop_back();
            cout<<"\n\n       TERMINADO"<<endl;
            cout<<"ID        OPE                RES        NL"<<endl;
            for(int z=0;z<listaTerminados.size();z++){
                cout<<listaTerminados[z].terminados()<<endl;
                if((z+1) % 4 == 0){
                    cout<<"--------------------------"<<endl;
                }
            }
            Sleep(5000);

        }
        TR_cont.clear();
        TT_cont.clear();
        lotesPendientes--;
    }
    fin(listaTerminados);
}

void Menu::comandos(vector<Proceso>&listaEjecucion,char tecla){
    switch(tecla){
        case 'w': //Interrupcion
                    listaEjecucion[0].getOperacion().setResultado(0.0);//El resultado se modifica, debe aparecer ERROR o algo asi, solo queda eso.
            break;
        case 'p': //Pausa
                    do{
                        if(_kbhit()){
                            tecla = _getch();//Se guarda la tecla seleccionada
                        }
                    }while(tecla != 'c');//El programa seguira pausado mientras no se haga click en 'c'
            break;
    } 
}

void Menu::iniciarMenu(){
    vector<Lote>listaLotes;
    vector<Proceso>listaProcesos;
    set<int>listaId;
    int id, opcionOperador,TME; 
    float op1, op2;
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
                }while(listaId.count(id));
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
                }while((operador == '/' && op2 == 0) || (operador== '%' && op2 == 0));//Esto evita que el usuario quiera dividir entre 0

                do{
                    cout<<"TME: ";
                    cin>>TME;
                }while(TME <= 0);
                cout<<endl<<endl;
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

                Operacion operacion = Operacion(op1, op2, operador); //Se crea un objeto tipo 'Operacion'
                Proceso proceso = Proceso(nombre, operacion, id, TME, i+1);//Se crea un objeto tipo 'Proceso'
                lote.agregarProceso(proceso);//Al lote acutal se le agrega un proceso
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
    cin.ignore();
    mostrarInfo(listaLotes);
}