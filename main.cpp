#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <iomanip>
#include "lote.hpp"
#include "proceso.hpp"
#include "operacion.hpp"

using namespace std;

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

bool comprobarId(int id, vector<Lote>&listaLotes){ //Se comparara si ya existe un id igual
    for(int i = 0; i < listaLotes.size(); i++){ //Itera segun la cantidad de lotes
        vector<Proceso>listaTMP = listaLotes[i].getListaProcesos(); //Apartir de un Lote en especifico se obtiene la lista de Procesos que tenga
        for(int j = 0; j < listaTMP.size(); j++){//Itera segun la cantidad de procesos
            if(id == listaTMP[j].getId()){//Se obtiene el id especifico de cada lote
                cout<<endl<<"ESE ID YA HA SIDO SELECCIONADO\nINGRESE OTRO"<<endl;
                return true;//En caso que el id sea igual se retorna 'true' para que el bucle 'do - while' continue
            }
        }
    }
    return false;//En caso que no se encuentre un id igual, se retorna 'false'
}

void mostrarInfo(vector<Lote>&listaLotes){
    int intervalo = 5; // Intervalo en segundos
    int lotes_pendientes = 10; // Número inicial de lotes pendientes
    while (true) { // Bucle infinito para imprimir repetidamente
        // Limpiar la pantalla
        cout << "\033[2J\033[1;1H";

        // Imprimir toString de todos los lotes
        for(int i = 0; i < listaLotes.size(); i++) {
            vector<Proceso>listaTMP = listaLotes[i].getListaProcesos();
            for(int j = 0; j < listaTMP.size(); j++) {
                cout<<endl<<"Lote Actual"<<endl;
                cout<<listaTMP[i].loteActual()<<endl;
                cout<<"Ejecucion"<<endl;
                cout<<listaTMP[i].toString()<<endl;
                cout<<"Terminados"<<endl;
                cout<<listaTMP[i].terminados()<<"  "<<listaLotes[i].getIdLote();
                cout<<endl<<endl;
            }
        }
       

        // Esperar el intervalo especificado
        this_thread::sleep_for(chrono::seconds(intervalo));
    }
}

int main(){
    vector<Lote>listaLotes;
    vector<Proceso>listaProcesos;
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
                    verificarId = comprobarId(id, listaLotes);
                }while(verificarId);//Mientras comprobarID regrese 'true', no saldra del bucle

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
                Proceso proceso = Proceso(nombre, operacion, id, TME);//Se crea un objeto tipo 'Proceso'
                //Lote lote = Lote(i+1); //Se crea un objeto tipo 'Lote'
                lote.agregarProceso(proceso);//Al lote acutal se le agrega un proceso
                //listaLotes.push_back(lote);//A la lista de lotes se añade el lote actual
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

