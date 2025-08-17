#include "torrecontrol.h"
#include "globales.h"
#include <limits>
/*
Msg TorreControl::simula(std::ofstream &fout)//Hay que poner la referencia a la clase porque estan en ficheros distintos
{
    if ((mPtr != nullptr) && !(mPtr->empty()))//Si no esta vacia la cola a la que yo accedo a traves del puntero
    {
        Msg msg = mPtr->pop();//procesamos el ultimo elemento de la cola apuntada por el puntero
        std::cout<<msg<<std::endl;
        return msg;
    }
}*/
void TorreControl::MuestraMenuComandos(void)
{
    std::cout<< "------- Menu de comandos -----\n";
    std::cout<< "1.- Monitorizacion del vehiculos\n";
    std::cout<< "2.- Mostrar mensajes en cola\n";
    std::cout<< "3.- Finalizar programa\n";


}

char TorreControl::introduzca_opcion(int &cent)
{
    char opcion;
    std::cout<< "Introduzca una opcion: ";
    std::cin>>opcion;
    if(!(opcion>48 && opcion <52))//codigos ascii entre 1 y 3
    {
        cent = 0;
        throw comando_erroneo;
    }

    cent = 1;
    return opcion;

}
std::vector<Drone* > TorreControl::crea_drones(int numDrones, ColaLim<Msg>* &Pcanal, RandomEntero &tempID, RandomReal &tempAlt, RandomReal &tempVel, RandomReal &tempHor, RandomReal &tempTemp, RandomEntero &tempCarga)
{
    std::vector<Drone *> vDron;
    int ID, flag;

    for (int i = 0; i < numDrones; ++i)
    {
        Bateria bat(tempCarga(), tempVel()*0.15);
        Drone* PtrDrone;

        do
        {
            flag = 0;
            ID = tempID();
            for(auto PDron: vDron)
            {
                if(PDron->getID()==ID)
                {
                    flag = 1;
                    break;
                }
            }
        }
        while(flag); //Bucle para que no se repitan los identificadores
        PtrDrone = new Drone(ID, Pcanal, bat,tempAlt(), tempVel(), tempHor(), true, tempTemp());
        vDron.push_back(PtrDrone);
    }//No utilizo la declaración dinámica porque sino no me deja usar el operador ()




    return vDron;

}


/*void TorreControl::envia_msg(ColaLim<Msg> *Ptr, int numDrones, std::ofstream &fout)
{
    Imprimir<std::string> pstring;
    Imprimir<Msg> pMsg;
    double altura, velocidad, horizontal;
    int cent = 0, id;
    do
    {
        std::cout<< "Introduce la id del vehiculo que recibira el mensaje: ";
        std::cin>>id;
        if(!(id>0 && id <(numDrones-1)))
        {
            cent = 1;
            std::cout<<std::endl;
            std::cerr<< "ERROR. El numero introducido no se corresponde con la identificacion de ningun vehiculo."<<std::endl;
            std::cout<<std::endl;

        }

    }while(cent);

    cent = 0;

    do
    {
        std::cout<< "Introduce la altura a la que debemos llegar: ";
        std::cin>>altura;
        if(altura<0)
        {
            cent = 1;
            std::cout<<std::endl;
            std::cerr<< "ERROR. La altura ha de ser mayor que cero."<<std::endl;
            std::cout<<std::endl;
        }
    }while(cent);

    cent = 0;
    do
    {
        std::cout<< "Introduce la velocidad de desplazamiento: ";
        std::cin>>velocidad;
        if(altura<0)
        {
            cent = 1;
            std::cout<<std::endl;
            std::cerr<< "ERROR. La velocidad ha de ser mayor que cero."<<std::endl;
            std::cout<<std::endl;
        }
    }while(cent);

    std::cout<< "Indroduce la posicion horizontal a alcanzar: ";
    std::cin>>horizontal;

    Msg mensaje(id,altura,velocidad, horizontal);

    pMsg(mensaje,fout);
    Ptr ->put(mensaje);
    pstring("Se ha enviado el mensaje a la cola de comandos con exito.", fout);
    pstring("\n", fout);

    mensaje.~Msg();

}
*/
