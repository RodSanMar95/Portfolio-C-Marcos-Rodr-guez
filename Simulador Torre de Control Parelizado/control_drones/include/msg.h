#ifndef MSG_H
#define MSG_H
#include <iostream>//Necesasirio para los outs
#include <fstream>

#include "colalim.h"
#include "bateria.h"

//No es bueno usar el using, el espacio de nombres de la clase usa diferentes using
//using namespace std;

class Msg
{
    private:
        int mID;//identificador que representa que dron recibida el mensaje
        double mAlt;
        double mVel;
        double mHor;
        Bateria mBat;
        double mTemp;

    public:                                     //Esta es la implementacion del constructor
        Msg(int nID = 0, double nAlt = 0., double nVel = 0., double nHor = 0., Bateria nBat = (100, 1.), double nTemp = 0.): mID(nID), mAlt(nAlt), mVel(nVel), mHor(nHor), mBat(nBat), mTemp(nTemp) {};//metodo de declaracion privativo de los constructores
        ~Msg() {};//Esta clase cuenta con un destructor porque los mensajes son temporales
        int getID(void){return mID;}
        double getAlt(void){return mAlt;}
        double getVel(void){return mVel;}
        double getHor(void){return mHor;}
        Bateria getBat(void){return mBat;}
        void setID(int nID){mID=nID;}
        void setAlt(double nAlt){mAlt=nAlt;}
        void setVel(double nVel){mVel=nVel;}
        void setHor(double nHor){mHor=nHor;}
        friend std::ostream & operator<<(std::ostream &, Msg &);
        friend std::ofstream & operator<<(std::ofstream &, Msg &);




};

#endif // MSG_H
