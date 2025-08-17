#ifndef RADOMREAL_H
#define RADOMREAL_H

#include <random>
#include <ctime>
#include <iostream>

class RandomReal
{
        std::default_random_engine mRe {static_cast<long unsigned int>(time(0))};//creamos un tiempo aleatorio para que no se repitan siempre los mismos numeros cada vez que inicio el programa
        //uniform_real_distribution<double> dist;//distribucion estadistica uniforme
        std::uniform_real_distribution<double> mDist; // media 0, desvest 1
    public:
        RandomReal(double minimo, double maximo):mDist(minimo,maximo) {}//imicializamos la distribucion a esos dos valores
        double operator()()
        {
            return mDist(mRe);   //sobrecargamos el operador de llamada a metodo, para que la clase sea un funtor
        }
};

#endif // RADOMREAL_H
