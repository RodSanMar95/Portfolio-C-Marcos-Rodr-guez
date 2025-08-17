#include "msg.h"


std::ostream & operator<< (std::ostream &out, Msg &msg)
{
    out << "Vehiculo "<< msg.mID << ": (" << msg.mAlt << "," << msg.mHor << ")"<< " Velocidad: " <<msg.mVel<< " Temperatura: " <<msg.mTemp<< " ";
    return out;
}

std::ofstream & operator<<(std::ofstream &fout, Msg &msg)
{
    fout << "Vehiculo "<< msg.mID << ": (" << msg.mAlt << "," << msg.mHor << ")"<< " Velocidad: " <<msg.mVel<< " Temperatura: " <<msg.mTemp<< " ";
    return fout;
}

