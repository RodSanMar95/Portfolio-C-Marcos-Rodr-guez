#ifndef IMPRIMIR_H
#define IMPRIMIR_H


template<typename T>
class Imprimir
{
    public:
        Imprimir() {}
        ~Imprimir() {}
        void operator()(T imp, std::ofstream &fout)//Clase functor
        {
            std::cout<<imp;
            fout<<imp;
        }
};

#endif // IMPRIMIR_H
