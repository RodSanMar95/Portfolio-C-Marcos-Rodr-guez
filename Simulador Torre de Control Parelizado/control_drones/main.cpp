#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <deque>

#include "imprimir.h"
#include "drone.h"
#include "randomentero.h"
#include "radomreal.h"
#include "globales.h"
#include "torrecontrol.h"
#include "msg.h"
#include "colalim.h"

using namespace std;

int main()
{
    Imprimir<string> pstring;
    Imprimir<Msg> pmsg;

    ofstream fich("comandos.txt");
    if(!fich)
    {
        cerr<< "ERROR. No se pudo abrir el fichero";
        exit(EXIT_FAILURE);
    }


    int numDrones;

    cout<< "------MONITORIZACION DE DRONES EN TIEMPO REAL------\n";
    cout<< "La monitorizacion de los drones de realiza durante un tiempo \n";
    cout<< "establecido por el usuario, en intervalos de tiempo de 10 segundos.\n";
    cout<<endl;

    int cent = 0;
    do
    {
        cent = 0;
        cout<< "Introduzca el numero de vehiculos a monitorizar: \n";
        cin>>numDrones;
        if(numDrones<0 || numDrones>8)
        {
            cout<<endl;
            cerr<< "ERROR. El numero de drones introducidos no es correcto o demasiado grande."<<endl;
            cent = 1;
        }

    }
    while(cent);

    vector<Drone *> vDron;
    vDron.reserve(numDrones);//reservamos el espacio a ocupar por el vector

    ColaLim<Msg> *Pcanal;
    Pcanal = new ColaLim<Msg>(10);

    TorreControl torre(Pcanal);


    RandomEntero tempID(0,100);
    RandomReal tempAlt(min_alt, max_alt);
    RandomReal tempVel(min_vel, max_vel);
    RandomReal tempHor(min_hor,max_hor);
    RandomReal tempTemp(min_temp, max_temp);
    RandomEntero tempCarga(60,100);


    vDron = torre.crea_drones(numDrones,Pcanal,tempID,tempAlt,tempVel,tempHor,tempTemp,tempCarga);

    pstring("Vehiculos a Monitorizar: ",fich);
    Imprimir<int> pint;
    for (auto elem: vDron)
    {
        pint(elem->getID(),fich);
        pstring(" ",fich);
    }
    pstring("\n", fich);



    char opcion = '0';
    int cent_comandos = 0;
    vector<thread *> vThread;
    while (opcion != '3')
    {
        do
        {
            torre.MuestraMenuComandos();
            try
            {
                opcion = torre.introduzca_opcion(cent_comandos);
            }
            catch(erroresComandos error)
            {
                if(error == comando_erroneo)
                {
                    cout<<endl;
                    cerr << "ERROR. La opcion no introducida no es correcta"<<endl;
                    cout<<endl;
                }
            }

        }
        while(!cent_comandos);

        switch(opcion)
        {
        case '1':
        {

            vThread.clear();
            double tiempo;
            cout<< "Introduce el tiempo que desea monitorizar los vehiculos en segundos: ";
            cin>>tiempo;
            cout<<endl;

            double t = tiempo;
            int iter = (static_cast<int>(t/10)+1);




            vThread.reserve(numDrones);
            thread* Pthread;
            for (int i = 0; i < numDrones; ++i)
            {
                Pthread = new thread(*vDron.at(i),ref(pstring), ref(pmsg), ref(tempTemp), ref(tempVel), ref(tempAlt), ref(tempHor), ref(fich), iter, t);
                vThread.push_back(Pthread);

            }

            break;
        }
        case '2':
        {

            vThread.clear();


            if(Pcanal->size()==0)
            {
                cerr<< "ERROR. No hay ningun mensaje en la cola"<<endl;
                exit(EXIT_FAILURE);
            }


            pstring("\n",fich);
            pstring("Extrayendo mensajes de la cola...",fich);
            pstring("\n",fich);

            Msg msg;


            //static_cast<ColaLim<Msg> *>(Pcanal)->imprime_msg(pstring,pmsg,fich);
            Imprimir<Bateria> pbat;
            deque<Msg> canal = Pcanal->getDeque();
            for(auto it = canal.begin(); it != canal.end(); it++ )
            {

                pmsg(*it,fich);
                pstring(" ",fich);
                Bateria bat = it->getBat();
                pbat(bat,fich);
                pstring("\n", fich);
            }

            Pcanal->clear();
            canal.clear();

            pstring("\n",fich);
            pstring("Los mensajes de la cola han sido procesados y eliminados con exito.",fich);
            pstring("\n",fich);

            break;
        }
        case '3':
        {
            vThread.clear();


            pstring("\n",fich);
            pstring("Finalizando el programa...",fich);
            pstring("\n",fich);
            break;
        }
        }

        for(auto &hilos: vThread)
        {
            hilos->join();
        }
        for(auto pt : vThread)
        {
            delete pt;
        }//Liberamos los hilos de memoria para la siguiente iteracion

    }

    fich.close();
    return 0;
}
