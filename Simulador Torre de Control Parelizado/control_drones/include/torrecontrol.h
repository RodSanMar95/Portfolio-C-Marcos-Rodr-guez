#ifndef TORRECONTROL_H
#define TORRECONTROL_H
#include "colalim.h"//le da igual si es mayuscula o minuscula para identificar el fichero
#include "imprimir.h"
#include "msg.h"
#include "drone.h"
#include <vector>


class TorreControl
{
    private:                //Lo inicializamos como puntero nulo
        ColaLim<Msg> *mPtr = nullptr;//Puntero a elementos de la clase colalim
    public:
        TorreControl(ColaLim<Msg> *nPtr = nullptr):mPtr(nPtr) {};
        //Msg simula(std::ofstream &);
        void MuestraMenuComandos(void);
        char introduzca_opcion(int &);
        std::vector<Drone *> crea_drones(int ,ColaLim<Msg>* &,RandomEntero &, RandomReal &, RandomReal &, RandomReal &, RandomReal &, RandomEntero &);
        //void envia_msg(ColaLim<Msg> *, int, std::ofstream &);
};

#endif // TORRECONTROL_H
