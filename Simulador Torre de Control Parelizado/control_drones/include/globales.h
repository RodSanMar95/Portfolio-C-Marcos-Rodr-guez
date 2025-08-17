#ifndef GLOBALES_H_INCLUDED
#define GLOBALES_H_INCLUDED

#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>

const int cola_vacia = 1;
enum erroresComandos { comando_erroneo = 1};
const double min_temp = -10.;
const double max_temp = 30.;
const double min_vel = 0.1;
const double max_vel = 0.5;
const double min_hor = -100.;
const double max_hor = 100.;
const double min_alt = 0.;
const double max_alt = 50.;
const int Tiempo_Muestreo = 10;


/*
void print_time(std::ofstream & fout)
{
    auto tim = std::chrono::system_clock::now();
    time_t fecha = std::chrono::system_clock::to_time_t(tim);
    std::cout << "Fecha actual: " << ctime(&fecha)<< std::endl;
    std::cout << std::endl;
    fout << "Fecha actual: " << ctime(&fecha)<< std::endl;
    fout << std::endl;

}*/



#endif // GLOBALES_H_INCLUDED
