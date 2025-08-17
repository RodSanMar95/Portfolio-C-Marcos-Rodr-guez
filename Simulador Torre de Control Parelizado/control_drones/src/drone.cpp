#include "drone.h"



Drone::Drone(int nID = 0,ColaLim<Msg> *nPtr = nullptr, Bateria nBateria=Bateria(100,1.), double nAlt=0., double nVel =0., double nHor = 0., bool nDronEncendido = false, double nTemp = 0.)
{
    mID = nID;
    mPtr = nPtr;
    mBateria = nBateria;
    mAlt = nAlt;
    mVel = nVel;
    mHor = nHor;
    mDronEncendido = nDronEncendido;
    mTemp = nTemp;

}
/*void Drone::simula_altura(int tMuest, Msg &msg)
{
    mVel=msg.getVel();
    if(mAlt<msg.getAlt())
    {
        double val = mAlt + mVel*tMuest;
        mAlt=val;
    }
    else
    {
        double val = mAlt - mVel*tMuest;
        mAlt=val;
    }

    if(fabs(mAlt-msg.getAlt())<mVel*tMuest)
    {
        mAlt=msg.getAlt();
    }

}*/
/*void Drone::simula_horiz(int tMuest, Msg &msg)
{
    mVel=msg.getVel();
    if(mHor<msg.getHor())
    {
        double val = mHor + mVel*tMuest;
        mHor=val;

    }
    else
    {
        double val;
        val = mHor - mVel*tMuest;
        mHor=val;
    }

    if(fabs(mHor-msg.getHor())<mVel*tMuest)
    {
        mHor=msg.getHor();
    }

}*/
std::ostream & operator<< (std::ostream &out, Drone &drone)
{
    out << "POSICION: Vehiculo "<< drone.getID() << " (" << drone.getAlt() << "," << drone.getHor() << ")"<< " Velocidad: " << drone.getVel();
    return out;
}

std::ofstream & operator<<(std::ofstream &fout, Drone &drone)
{
    fout << "POSICION: Vehiculo "<< drone.getID() << " (" << drone.getAlt() << "," << drone.getHor() << ")"<< " Velocidad: " << drone.getVel();
    return fout;
}

/*Msg Drone::despegue(std::ofstream &fout)
{
    double altura = 1;

    std::cout<<std::endl;
    fout<<std::endl;
    std::cout<< "El dron despeguara y ascendera 1 metro."<<std::endl;
    fout<< "El dron despeguara y ascendera 1 metro."<<std::endl;
    std::cout<<std::endl;
    fout<<std::endl;

    Msg msg(mID,altura, 0.15, 0);

    return msg;
}*/
/*
void Drone::info_dron(std::ofstream &fout)
{

    std::cout<< "Identificador: " << mID <<std::endl;
    fout<< "Identificador: " << mID <<std::endl;
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

    std::cout<< "Altura: "<<mAlt<<std::endl;
    fout<< "Altura: "<<mAlt<<std::endl;
    std::cout<< "Ultima velocidad: "<<mVel<<std::endl;
    fout<< "Ultima velocidad: "<<mVel<<std::endl;
    std::cout<< "Posicion horizontal: "<<mHor<<std::endl;
    fout<< "Posicion horizontal: "<<mHor<<std::endl;
    std::cout<< "Numero de mensajes en cola: "<<mPtr->size()<<std::endl;
    fout<< "Numero de mensajes en cola: "<<mPtr->size()<<std::endl;

    std::transform(dynamic_cast<ColaLim<Msg> *>(mPtr)->rbegin(),dynamic_cast<ColaLim<Msg> *>(mPtr)->rend(), [&fout](Msg m)
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



void Drone::operator()(Imprimir<std::string> &pstring, Imprimir<Msg> &pmsg, RandomReal &temperatura, RandomReal &velocidad, RandomReal &altura, RandomReal &horizontal, std::ofstream &fout, int iter, double t)
{

    double nTemp = temperatura();
    double nVel = velocidad();
    double nAlt = altura();
    double tDescarg;
    int tMuest;
    int carga;
    Imprimir<Bateria> pbat;

    for(int i = 0; i<iter; ++i)
    {
        if(t>=10)
        {
            tMuest = Tiempo_Muestreo;
        }
        else
        {
            tMuest = t;
        }
        if (mBateria <= 20) //Si la bateria esta baja descendemos
        {
            nAlt = 0;
            mVel = 0.2;
            double val = mAlt - mVel*tMuest;
            mAlt = val;
            tDescarg = (double)tMuest;


            if(fabs(mAlt-nAlt)<mVel*tMuest)
            {
                mAlt=nAlt;
                tDescarg = ((fabs(mAlt-nAlt))/mVel);
            }
            carga = mBateria.descargaBat(mVel,tDescarg);
            mBateria.setCarga(carga);

            mTemp = nTemp;
            Msg msg(mID, mAlt, mVel, mHor, mBateria.getCarga(), mTemp);

            mPtr->mu.lock();
            pmsg(msg,fout);
            pbat(mBateria,fout);//tengo que imprimir la bateria fuera del mensaje porque la instancia pmsg no sabe como imprimir un objeto de tipo bateria
            auto tim = std::chrono::system_clock::now();
            time_t fecha = std::chrono::system_clock::to_time_t(tim);
            std::cout << "Fecha actual: " << ctime(&fecha);
            fout << "Fecha actual: " << ctime(&fecha);
            mPtr->mu.unlock();

            mPtr->mu.lock();
            mPtr->put(msg);
            mPtr->mu.unlock();//Semaforo que regula el acceso a la cola
            msg.~Msg();
        }
        else
        {

            mVel=nVel;
            if(mAlt<nAlt)
            {
                double val = mAlt + mVel*tMuest;
                mAlt=val;
                tDescarg = tMuest;

            }
            else
            {
                double val = mAlt - mVel*tMuest;
                mAlt=val;
                tDescarg = tMuest;
            }


            if(fabs(mAlt-nAlt)<mVel*tMuest)
            {
                mAlt=nAlt;
                tDescarg = ((fabs(mAlt-nAlt))/mVel);

            }


            carga = mBateria.descargaBat(mVel,tDescarg);
            mBateria.setCarga(carga);



            double nHor = horizontal();

            if(mHor<nHor)
            {
                double val = mHor + mVel*tMuest;
                mHor = val;
                tDescarg = tMuest;
            }
            else
            {
                double val;
                val = mHor - mVel*tMuest;
                mHor=val;
                tDescarg = tMuest;
            }



            if(fabs(mHor-nHor)<mVel*tMuest)
            {
                mHor=nHor;
                tDescarg = ((fabs(mAlt-nAlt))/mVel);

            }


            carga = mBateria.descargaBat(mVel,tDescarg);
            mBateria.setCarga(carga);


            mTemp = nTemp;

            Msg msg(mID, mAlt, mVel, mHor, mBateria, mTemp);

            mPtr->mu.lock();
            pmsg(msg,fout);
            pbat(mBateria,fout);
            auto tim = std::chrono::system_clock::now();
            time_t fecha = std::chrono::system_clock::to_time_t(tim);
            std::cout << " Fecha actual: " << ctime(&fecha);
            fout << " Fecha actual: " << ctime(&fecha);
            mPtr->mu.unlock();

            mPtr->mu.lock();
            mPtr->put(msg);
            mPtr->mu.unlock();//Semaforo que regula el acceso a la cola
            msg.~Msg();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        t = t-10;
    }

    Imprimir<int> pint;

    mPtr->mu.lock();
    pstring("Fin del periodo de monitorizacion del vehiculo ", fout);
    pint(mID, fout);
    pstring(".", fout);
    pstring("\n", fout);
    mPtr->mu.unlock();



}




