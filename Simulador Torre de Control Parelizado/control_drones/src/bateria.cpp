#include "bateria.h"
#include "msg.h"

int Bateria::descargaBat (double vel, double t)
{
    mVelDescg = vel;
    if(mCarga > 0)
        mCarga = mCarga - static_cast<int>(mVelDescg*t);
    //std::cout<< "Carga: " <<mCarga<<" " <<int(mVelDescg*t) <<" ";
    return mCarga;
}
std::ostream & operator << (std::ostream &out, Bateria &bat)
{
    int carga = bat.getCarga();
    out<< "BATERIA:[";
    for(int i = 0; i<(carga/10); ++i)
    {
        std::cout<< "#";
    }
    for(int i = (carga/10); i < 10; ++i)
    {
        std::cout<< "-";
    }
    out<< "] ("<<carga<< "%) ";
    return out;

}
std::ofstream & operator << (std::ofstream &fout, Bateria &bat)
{
    int carga = bat.getCarga();
    fout<< "BATERIA:[";
    for(int i = 0; i<(carga/10); ++i)
    {
        fout<< "#";
    }
    for(int i = (carga/10); i < 10; ++i)
    {
        fout<< "-";
    }
    fout<< "] ("<<carga<< "%) ";
    return fout;

}
bool operator <= (Bateria &Bat, int carg)
{
    return Bat.getCarga() <= carg;
}
