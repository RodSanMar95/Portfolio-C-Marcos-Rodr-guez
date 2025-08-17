#ifndef COLALIM_H
#define COLALIM_H

#include <deque>
#include <mutex>
#include <thread>

//#include "imprimir.h"
#include "globales.h"
#include "msg.h"


template <typename T>
class ColaLim
{
    std::deque<T> mCola;
    int mTamMax;

public:
    ColaLim(int nTam):mTamMax(nTam) {}
    std::mutex mu; //Semaforo de cola limitada
    std::deque<T> getDeque(void)
    {
        return mCola;
    }
    void put(T nElem);
    T pop(void);
    bool empty()
    {
        return mCola.empty();
    }
    int size()
    {
        return mCola.size();
    }
    void clear()
    {
        mCola.clear();
    }

    //void imprime_msg(Imprimir<std::string> &, Imprimir<Msg> &, std::ofstream &);
    //ColaLim<T> begin(){return mCola.begin();}
    //ColaLim<T> end(){return mCola.end();}
    //friend bool operator!= (ColaLim<T> &, ColaLim<T> &);
};
/*
template <typename T>
bool operator!= ((mCola.ColaLim<T>)::iterator &Cola1, (mCola.ColaLim<T>)::iterator &Cola2)
{
    return &Cola1 != &Cola2;
}
*/
template <typename T>
void ColaLim<T>::put(T nElem)
{
    if(mCola.size()>= static_cast<unsigned int>(mTamMax))
    {
        mCola.pop_back();
    }
    mCola.push_front(nElem);

}
template <typename T>
T ColaLim<T>::pop(void)
{
    T valor;

    if(mCola.empty())
        throw cola_vacia;

    valor = mCola.back();//guardamos el ultimo elemento para procesarlo
    mCola.pop_back();//eliminamos el ultimo elemento
    return valor;
}
/*
template <typename T>
void ColaLim<T>::imprime_msg(Imprimir<std::string> &pstring, Imprimir<Msg> &pmsg, std::ofstream &fout)
{
    for(auto it = mCola.begin(); it != mCola.end(); it++ )
    {

        pmsg(*it,fout);
        pstring("\n",fout);
    }
}
*/

#endif // COLALIM_H

