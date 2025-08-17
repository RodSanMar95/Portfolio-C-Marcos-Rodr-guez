#include "drone.h"

const int Tiempo_Muestreo = 10;

Drone::Drone(ColaLim<Msg> *nPtr = nullptr, Bateria nBateria=Bateria(100,1.), SensorAltura nAlt=SensorAltura (0.,0), SensorVelocidad nVel =SensorVelocidad(0.,0), SensorHorizontal nHor = SensorHorizontal(0.,0), bool nDronEncendido = false)
{
    mPtr = nPtr;
    mBateria = nBateria;
    mAlt = nAlt;
    mVel = nVel;
    mHor = nHor;
    mDronEncendido = nDronEncendido;

}
void Drone::simula_altura(int tMuest, Msg &msg)
{
    mVel.setValue(msg.getVel());
    if(mAlt<msg.getAlt())
    {
        double val = mAlt + mVel*tMuest;
        mAlt.setValue(val);
    }
    else
    {
        double val = mAlt - mVel*tMuest;
        mAlt.setValue(val);
    }

    if(fabs(mAlt-msg.getAlt())<mVel*tMuest)
    {
        mAlt.setValue(msg.getAlt());
    }

}
void Drone::simula_horiz(int tMuest, Msg &msg)
{
    mVel.setValue(msg.getVel());
    if(mHor<msg.getHor())
    {
        double val = mHor + mVel*tMuest;
        mHor.setValue(val);

    }
    else
    {
        double val;
        val = mHor - mVel*tMuest;
        mHor.setValue(val);
    }

    if(fabs(mHor-msg.getHor())<mVel*tMuest)
    {
        mHor.setValue(msg.getHor());
    }

}
std::ostream & operator<< (std::ostream &out, Drone &drone)
{
    out << "POSICION: (" << drone.getAlt().getValue() << "," << drone.getHor().getValue() << ")"<< " Velocidad: " << drone.getVel().getValue();
    return out;
}

std::ofstream & operator<<(std::ofstream &fout, Drone &drone)
{
    fout << "POSICION: (" << drone.getAlt().getValue() << "," << drone.getHor().getValue() << ")"<< " Velocidad: " << drone.getVel().getValue();
    return fout;
}

Msg Drone::despegue(std::ofstream &fout)
{
    double altura = 1;

    std::cout<<std::endl;
    fout<<std::endl;
    std::cout<< "El dron despeguara y ascendera 1 metro."<<std::endl;
    fout<< "El dron despeguara y ascendera 1 metro."<<std::endl;
    std::cout<<std::endl;
    fout<<std::endl;

    Msg msg(altura, 0.15, 0);

    return msg;
}
void Drone::info_dron(std::ofstream &fout)
{
    //std::vector<int> p;
    std::vector<Sensor *> v;
    Sensor *Palt = (Sensor *)&mAlt;
    v.push_back(Palt);
    Sensor *Pvel = (Sensor *)&mVel;
    v.push_back(Pvel);
    Sensor *Phor = (Sensor *)&mHor;
    v.push_back(Phor);

    std::cout<< "Identificadores de los Sensores: ";
    fout<< "Identificadores de los Sensores: ";
    for(auto elem: v)
    {
        std::cout<< elem->getID()<< " ";//POLIMORFISMO
        fout<< elem->getID()<< " ";
    }
    std::cout<<std::endl;
    fout<<std::endl;

    std::cout<< "Estado: ";
    fout<< "Estado: ";
    if(mDronEncendido)
    {
        std::cout<< "Encendido"<<std::endl;
        fout<< "Encendido"<<std::endl;
    }

    else
    {
        std::cout<< "Apagado"<<std::endl;
        fout<< "Apagado"<<std::endl;
    }

    std::cout<< "Altura: "<<mAlt.getValue()<<std::endl;
    fout<< "Altura: "<<mAlt.getValue()<<std::endl;
    std::cout<< "Ultima velocidad: "<<mVel.getValue()<<std::endl;
    fout<< "Ultima velocidad: "<<mVel.getValue()<<std::endl;
    std::cout<< "Posicion horizontal: "<<mHor.getValue()<<std::endl;
    fout<< "Posicion horizontal: "<<mHor.getValue()<<std::endl;
    std::cout<< "Numero de mensajes en cola: "<<mPtr->size()<<std::endl;
    fout<< "Numero de mensajes en cola: "<<mPtr->size()<<std::endl;

    /*std::transform(dynamic_cast<ColaLim<Msg> *>(mPtr)->rbegin(),dynamic_cast<ColaLim<Msg> *>(mPtr)->rend(), [&fout](Msg m)
    {
        std::cout<<m<<std::endl;
        fout<<m<<std::endl;
    });*/
    /*
    auto it = dynamic_cast<ColaLim<Msg> *>(mPtr)->getDeque().begin();

    int pos = mPtr->size();

    while(it != mPtr->getDeque().end())
    {
        std::cout<< pos << ": " <<*it<<std::endl;
        fout<< pos << ": " <<*it<<std::endl;
        it++;
    }
    */


}



