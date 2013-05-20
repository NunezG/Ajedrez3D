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
#endif
