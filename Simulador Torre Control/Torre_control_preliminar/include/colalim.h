#ifndef COLALIM_H
#define COLALIM_H

#include <deque>

#include "globales.h"
#include "msg.h"


template <typename T>
class ColaLim
{
    std::deque<T> mCola;
    int mTamMax;
public:
    ColaLim(int nTam):mTamMax(nTam) {}

    std::deque<T> getDeque(void){return mCola;}
    void put(T nElem);
    T pop(void);
    bool empty(){return mCola.empty();}
    int size(){return mCola.size();}
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
    if(mCola.size()>= mTamMax)
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


#endif // COLALIM_H
