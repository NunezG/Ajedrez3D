#ifndef __ModeloTablero_
#define __ModeloTablero_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>


struct ModeloTablero
{   
    // StringClass(char *ptr);
    ModeloTablero();
    ~ModeloTablero();

    //constructor de copia
    ModeloTablero( const ModeloTablero& original );

    std::vector<ModeloTablero*> vectorMov;

    int Score;
    //  Casilla* casillas[64];
    int* casillasInt;
    int movimiento[2];
    //  int numeroHijos;

    int alPaso;
    bool turnoN;

    // Ficha* fichasNegras[16];
    // Ficha* fichasBlancas[16];
    // int casillas[8][8];
    //ModeloTablero* tableroHermano;
    //ModeloTablero* tableroHijo;
    //  std::string fichaMovida;

private:

};

ModeloTablero::ModeloTablero() :
    //numeroHijos(0),
    Score(0),
    //fichaMovida(""),
    vectorMov(0),
    turnoN(false),
    alPaso(0)
{
}

ModeloTablero::ModeloTablero( const ModeloTablero& original ):
    //  numeroHijos(0),
    Score(0),
    // fichaMovida(""),
    vectorMov(0),
    turnoN(!original.turnoN),
    alPaso(original.alPaso)
{
    // std::cout << "turnoN al copiar: "<<turnoN<<" Original: "<<original.turnoN << std::endl;
    casillasInt = new int[144];

    for(int i=0; i<144;i++)
    {
        casillasInt[i] = original.casillasInt[i];
    }
}

ModeloTablero::~ModeloTablero()
{
    for(int i = 0; i < vectorMov.size(); i++)
    {
        delete vectorMov.at(i);

        vectorMov.at(i) = NULL;
    }
    //  numeroHijos=0;
    vectorMov.clear();
}
#endif
