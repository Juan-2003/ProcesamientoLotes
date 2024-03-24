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


int contadorGlobal = -1;
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



void Menu::comandos(set<Proceso*>&listaProcesosTotales, vector<Proceso*>&listaListos, vector<Proceso*>& listaActual, vector<Proceso*>& listaEjecucion, vector<Proceso*>& listaBloqueados, vector<Proceso*>& listaTerminados, char tecla) {
    char otraTecla;
    switch(tecla) {
        case 'w': //Interrupcion
            listaEjecucion[0]->getOperacion().setResultado("ERROR      "); 
            listaEjecucion[0]->setEstadoActual("Error T");
            break;
        case 'p': //Pausa
            do {
                if(_kbhit()) {
                    otraTecla = _getch(); //Se guarda la tecla seleccionada
                }
            } while(otraTecla != 'c'); //El programa seguira pausado mientras no se haga click en 'c'
            break;

        case 'e': //El proceso se va a Bloqueados
            listaBloqueados.insert(listaBloqueados.end(),listaEjecucion[0]);
            listaBloqueados[listaBloqueados.size()-1]->setEstadoActual("Bloqueado"); //Se establece a la ultima posicion del vector el estado actual de 'Bloqueado'
            listaEjecucion.pop_back();
            break;

        case 'n':
            if((listaActual.size() + listaEjecucion.size() + listaBloqueados.size()) < 4 ){//En caso que listaActual tenga menos de 4 el proceso entrara directamente
                listaActual.push_back(crearProceso());
            }else{//Si LActual tiene 4 o mas, el proceso se va a listos.
                listaListos.push_back(crearProceso());
            }

            break;

        case 'b':
            mostrarBCP(listaProcesosTotales);
            do {
                if(_kbhit()) {
                    otraTecla = _getch(); //Se guarda la tecla seleccionada
                }
            } while(otraTecla != 'c'); //El programa seguira pausado mientras no se haga click en 'c'
            break;
    }
}

void Menu::mostrarInfo(set<Proceso*>& listaProcesosTotales, vector<Proceso*>& listaListos, vector<Proceso*>& listaActual, vector<Proceso*>& listaEjecucion, vector<Proceso*>& listaBloqueados, vector<Proceso*>& listaTerminados){
    int TME_cont;
    int TT_cont;
    int actualTR;
    static bool jala1=true;

    if(!listaListos.empty()){
        for(int i=0;i<listaListos.size();i++){
            listaProcesosTotales.insert(listaListos[i]);
        }
    }

    if(jala1){
        if(listaListos.size() > 4){//Cuando la lista tenga mas de 4 procesos
            listaActual.assign(listaListos.begin(),listaListos.begin()+4);
            listaListos.erase(listaListos.begin(),listaListos.begin() + 4);
        }else{//Cuando la lista tenga menos de 4 procesos
            listaActual.assign(listaListos.begin(),listaListos.end());
            listaListos.erase(listaListos.begin(),listaListos.end());
        }
        jala1=false;
    }


    for (int j = 0; listaActual.size() != 0; j++) {
        system("cls");
        cout<<"Nuevos: "<<listaListos.size()<<endl;

        // -------------  LOTE ACTUAL -----------------------
        cout << endl << "       LOTE ACTUAL" << endl;
        for(int x=0;x<listaActual.size();x++){
            cout<<listaActual[x]->loteActual()<<endl;
            listaActual[x]->setEstadoActual("Listo    "); //A cada proceso se le aasigna el estado en el que esta 'Listo'.
            if(listaActual[x]->getTLL() == -1){
                (contadorGlobal == -1)? listaActual[x]->setTLL(contadorGlobal+1) : listaActual[x]->setTLL(contadorGlobal);
            }
        }

        if(listaEjecucion.empty()){
            listaEjecucion.push_back(listaActual[0]);
            listaActual.erase(listaActual.begin()); //Se esta eliminando el primer elemento de la lista
        }


        // ---------------- EJECUCION -----------------------------
        cout << "       EJECUCION" << endl;
        listaEjecucion[0]->setEstadoActual("Ejecucion");//Se le asigna el estado acutal de 'Ejecucion'
        cout<<listaEjecucion[0]->ejecucion() << endl;
        TME_cont = listaEjecucion[0]->getTME();//Se toma TME del proceso actual
        TT_cont = listaEjecucion[0]->getTT();//SE TOMA TT del proceso actual

        // Bucle para decrementar TR y mostrar su valor
        char tecla;
        bool bandera= false;
        bool bandera2 = false;
        actualTR = listaEjecucion[0]->getTR();
        int tiempoEspera = 0;
        listaEjecucion[0]->setTRespuesta(contadorGlobal+1);
        while (actualTR >=0) {
            contadorGlobal++;
            cout << "\rTME: " << TME_cont << " TR: " << actualTR << " TT: " << TT_cont << " Contador: "<< contadorGlobal<< flush;
            Sleep(1000);
            --actualTR;
            ++TT_cont;// Incrementa TT
            tiempoEspera++;


            if(_kbhit()){ //Mientras los contadores avanzan se verifica si se tecleo algo
                tecla = _getch(); //Lo que se tecleo lo guardo en tecla
                comandos(listaProcesosTotales,listaListos,listaActual, listaEjecucion, listaBloqueados, listaTerminados, tecla);
                /*En la funcion "comandos" se esta haciendo pop a la lista de ejecucion cuando se usa
                    'e' y se inserta ese proceso en listaActual, por lo que para establecer bien los valores
                    del proceso, se toma la ultima posicion de la listaActual*/
                if(tecla == 'e'){
                    listaBloqueados[listaBloqueados.size() - 1]->setTR(actualTR);
                    listaBloqueados[listaBloqueados.size() - 1]->setTT(TT_cont);
                    listaBloqueados[listaBloqueados.size() - 1]->setEstadoActual("Bloqueado");
                    listaBloqueados[listaBloqueados.size() - 1]->setTTbloqueado(0);
                    bandera = true;
                    bandera2 = true;
                    break;
                }
                else if(tecla == 'w'){
                    listaEjecucion[0]->setTR(actualTR);
                    listaEjecucion[0]->setTT(TT_cont);
                    for(int i = 0; i < listaActual.size(); i++){
                        listaActual[i]->setTEspera(listaActual[i]->getTEspera() + tiempoEspera);
                    }
                    break;
                }
                else if(tecla == 'n'){
                    listaEjecucion[0]->setTR(actualTR);
                    listaEjecucion[0]->setTT(TT_cont);
                    system("pause");
                    bandera = true;
                    bandera2 = true;
                    break;
                }
                else if(tecla == 'b'){
                    bandera = true;
                    bandera2 = true;
                    break;
                }
            }
            bool bandera3 = false;
            for(int i = 0; i < listaBloqueados.size(); i++){
                listaBloqueados[i]->setTTbloqueado(listaBloqueados[i]->getTTbloqueado()+1);
                if(listaBloqueados[i]->getTTbloqueado()==8){
                    listaBloqueados[i]->setTTbloqueado(-1);
                    listaEjecucion[0]->setTR(actualTR);
                    listaEjecucion[0]->setTT(TT_cont);
                    listaActual.push_back(listaBloqueados[i]);
                    listaBloqueados.erase(listaBloqueados.begin());
                    bandera2 = true;
                    bandera3 = true;//Esta bandera es para cortar el bucle de 'Ejecucion'
                    break;
                }
            }
            if(bandera3){//Corta el bucle de ejecucion
                break;
            }

        }

        cout <<endl<< "       BLOQUEADOS" << endl;
        cout<<"ID"<<"   "<<"TT"<<endl;
        for(int i = 0; i < listaBloqueados.size(); i++){
            cout<<listaBloqueados[i]->bloqueado()<<endl;
        }

        if(bandera2){//Esta bandera corta todo el bucle. Es para poder actualizar lo que se ve en pantalla
            break;
        }
        if(!bandera){//Si no se ha presionado la tecla 'e', se quitara lo que hay en la lista de ejecucion
            //listaEjecucion[0].setTRespuesta(contadorGlobal - listaEjecucion[0].getTME());//Se establece el tiempo de llegada
            listaEjecucion[0]->setTFinalizacion(contadorGlobal);
            listaEjecucion[0]->setTRetorno(listaEjecucion[0]->getTFinalizacion() - listaEjecucion[0]->getTLL());
            //listaEjecucion[0]->setTServicio(listaEjecucion[0]->getTME());
            listaEjecucion[0]->setTEspera(listaEjecucion[0]->getTRetorno() - listaEjecucion[0]->getTServicio());
            listaTerminados.push_back(listaEjecucion[0]);
            listaEjecucion.pop_back();
            if(listaListos.size() > 0){//Cuando se saque a un proceso de listaEjecucion, se a�adira uno nuevo a la lista actual siempre y cuando lista listos aun tenga procesos
                listaActual.push_back(listaListos[0]);
                listaListos.pop_back();
            }

        }

        if(listaTerminados[listaTerminados.size() - 1]->getEstadoActual() != "Error T"){
            listaTerminados[listaTerminados.size() - 1]->setEstadoActual("Terminado"); //A la ultima posicion se le asigna el estado de 'Terminado'
        }
        cout<<"\n\n       TERMINADO"<<endl;
        cout<<"ID        OPE                RES"<<endl;
        for(int z=0;z<listaTerminados.size();z++){
            cout<<listaTerminados[z]->terminados()<<endl;
            if((z+1) % 4 == 0){
                cout<<"--------------------------"<<endl;
            }
        }
        Sleep(1000);
    }
    if(listaActual.size() == 0){//Cuando la lista actual este vacia, se mostrara la informacion correspondiente
        mostrarBCP(listaProcesosTotales);

    }else{//Mientras que el tama�o de la lista actual sea mayor que 0, la funcion se llamara asi misma para actualizar lo que se ve en pantalla
        mostrarInfo(listaProcesosTotales,listaListos, listaActual, listaEjecucion, listaBloqueados, listaTerminados);
    }
}

void Menu::mostrarBCP(set<Proceso*>&listaProcesosTotales){
    system("cls");
    cout<<setw(5)<<left<<"ID";
    cout<<setw(10)<<left<<"Estado";
    cout<<setw(20)<<left<<"TTbloqueado";
    cout<<setw(22)<<left<<"Operacion";
    cout<<setw(15)<<left<<"Resultado";
    cout<<setw(10)<<left<<"TLL";
    cout<<setw(15)<<left<<"TFinizacion";
    cout<<setw(15)<<left<<"TRetorno";
    cout<<setw(15)<<left<<"TME";
    cout<<setw(15)<<left<<"TServicio";
    cout<<setw(15)<<left<<"TRespuesta"<<endl;

    for(auto& objeto : listaProcesosTotales){
        cout<<objeto->BCP()<<endl;
    }
    /*for(int i = 0; i < listaProcesosTotales.size(); i++){
        cout<<listaProcesosTotales[i]->BCP()<<endl;
    }*/

}

Proceso* Menu::crearProceso(){
    int opcionOperador,TME;
    static int id = 0;
    float operando1, operando2;
    string nombre;
    char operador;

    id++;//Se va sumando el id
    opcionOperador = 1+rand()%(6-1);//Operador random
    operador = elegirOperador(opcionOperador);//Se manda a llamar la funcion 'elegirOperador'
    operando1 = 1+rand()%(1001-1);//operador 1
    operando2 = 1+rand()%(1001-1); //operador 2
    TME = 5+rand()%(19-5); //TME
    Operacion operacion = Operacion(operando1, operando2, operador); //Se crea un objeto tipo 'Operacion'
    Proceso* proceso = new Proceso(nombre, operacion, id, TME);//Se crea un objeto tipo 'Proceso'

    return proceso;
}


void Menu::iniciarMenu(){
    vector<Proceso*> listaActual;
    vector<Proceso*> listaEjecucion;
    vector<Proceso*> listaTerminados;
    vector<Proceso*> listaBloqueados;
    vector<Proceso*>listaProcesos;
    set<Proceso*>listaProcesosTotales;

    int cantidadProcesos;
    cout<<"BIENVENIDO"<<endl;
    cout<<"Ingresa la cantidad de procesos que quieres realizar: ";
    cin>>cantidadProcesos;
    srand(time(NULL));
            for(int j = 0; j < cantidadProcesos; j++){//Este 'for' controla que por cada Lote haya 4 procesos
                listaProcesos.push_back(crearProceso());
            }
    cin.ignore();
    mostrarInfo(listaProcesosTotales, listaProcesos, listaActual, listaEjecucion, listaBloqueados, listaTerminados);
}
