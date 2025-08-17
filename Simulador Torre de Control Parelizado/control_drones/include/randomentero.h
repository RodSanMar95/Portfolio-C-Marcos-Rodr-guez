#ifndef RANDOMENTERO_H
#define RANDOMENTERO_H

#include <random>
#include <ctime>
#include <iostream>


class RandomEntero
{

        std::default_random_engine mRe {static_cast<long unsigned int>(time(0))};
        std::uniform_int_distribution<int> mDist;//distribucion uniforme de enteros
    public:
        RandomEntero(int minimo, int maximo):mDist(minimo,maximo) {}
        int operator()()
        {
            return mDist(mRe);
        }
};

#endif // RANDOMENTERO_H
