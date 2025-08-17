#include "msg.h"


std::ostream & operator<< (std::ostream &out,const Msg &msg)
{
    out << "MENSAJE: (" << msg.mAlt << "," << msg.mHor << ")"<< " Velocidad: " <<msg.mVel;
    return out;
}

std::ofstream & operator<<(std::ofstream &fout, const Msg &msg)
{
    fout << "MENSAJE: (" << msg.mAlt << "," << msg.mHor << ")"<< " Velocidad: " <<msg.mVel;
    return fout;
}

