#ifndef DRONE_H
#define DRONE_H

#include <thread>
#include <deque>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "globales.h"

#include "colalim.h"
#include "msg.h"
#include "bateria.h"
#include "radomreal.h"
#include "randomentero.h"
#include "imprimir.h"

//using namespace std::chrono_literals;

class Drone
{
    private:
        int mID;
        ColaLim<Msg> *mPtr = nullptr;//Agregacion
        Bateria mBateria;//Composicion
        double mAlt = 0.;
        double mVel = 0.;
        double mHor = 0.;
        bool mDronEncendido = false;
        double mTemp = 0.;//Temperatura del dron


    public:
        Drone(int nID, ColaLim<Msg> *nPtr, Bateria nBateria, double nAlt, double nVel, double nHor, bool nDronEncendido, double nTemp);
        ColaLim<Msg>* getPtr(void){return mPtr;}
        Bateria getBat(void){return mBateria;}
        int getID(void){return mID;}
        double getAlt(void){return mAlt;}
        double getVel(void){return mVel;}
        double getHor(void){return mHor;}
        bool getDronEncendido(void){return mDronEncendido;}
        void setPtr(ColaLim<Msg>* nPtr){mPtr=nPtr;}
        void setBat(Bateria nBateria){mBateria=nBateria;}
        void setAlt(double nAlt){mAlt=nAlt;}
        void setVel(double nVel){mVel=nVel;}
        void setHor(double nHor){mHor=nHor;}
        void setDronEncendido(bool nDronEncendido){mDronEncendido=nDronEncendido;}
        //void simula_altura(int, Msg &);
        //void simula_horiz(int, Msg &);
        //Msg despegue(std::ofstream &);
        //void info_dron(std::ofstream &);

        void operator()(Imprimir<std::string> &, Imprimir<Msg> &, RandomReal &, RandomReal &, RandomReal &, RandomReal &, std::ofstream &, int, double);
        friend std::ostream & operator<<(std::ostream &, Drone &);
        friend std::ofstream & operator<<(std::ofstream &, Drone &);




};

#endif // DRONE_H
