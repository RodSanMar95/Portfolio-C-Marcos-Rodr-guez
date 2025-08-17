#ifndef MSG_H
#define MSG_H
#include <iostream>//Necesasirio para los outs
#include <fstream>
#include "colalim.h"

//No es bueno usar el using, el espacio de nombres de la clase usa diferentes using
//using namespace std;

class Msg
{
    private:
        double mAlt;
        double mVel;
        double mHor;

    public:                                     //Esta es la implementacion del constructor
        Msg(double nAlt = 0, double nVel = 0, double nHor = 0):mAlt(nAlt), mVel(nVel), mHor(nHor) {};//metodo de declaracion privativo de los constructores
        ~Msg() {};//Esta clase cuenta con un destructor porque los mensajes son temporales
        double getAlt(void){return mAlt;}
        double getVel(void){return mVel;}
        double getHor(void){return mHor;}
        void setAlt(double nAlt){mAlt=nAlt;}
        void setVel(double nVel){mVel=nVel;}
        void setHor(double nHor){mHor=nHor;}
        friend std::ostream & operator<<(std::ostream &,const Msg &);
        friend std::ofstream & operator<<(std::ofstream &,const Msg &);




};

#endif // MSG_H
