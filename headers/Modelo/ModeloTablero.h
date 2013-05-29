#ifndef __ModeloTablero_
#define __ModeloTablero_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>

/*
*
0 = Vacio
99 = Fuera del tablero
1 = (amiga) Peon
2 =(amiga) Caballo
3 =(amiga) Alfil
4 = (amiga) Torre
5 = (amiga) Reina
6 = (amiga) Rey

-1 = (enemiga) Peon
-2 =(enemiga) Caballo
-3 =(enemiga) Alfil
-4 = (enemiga) Torre
-5 = (enemiga) Reina
-6 = (enemiga) Rey
*/

struct ModeloTablero
{   
    // StringClass(char *ptr);
    ModeloTablero();
    ~ModeloTablero();

    //constructor de copia
    ModeloTablero( const ModeloTablero& original );

    std::vector<ModeloTablero*> vectorMov;

    //int Score;
    //  Casilla* casillas[64];
    int* casillasInt;
    int* jugada;
    //  int numeroHijos;

    int alPaso;
    bool turnoN;
    bool nodoInicial;

    // Ficha* fichasNegras[16];
    // Ficha* fichasBlancas[16];
    // int casillas[8][8];
    //ModeloTablero* tableroHermano;
    //ModeloTablero* tableroHijo;
    //  std::string fichaMovida;

private:




};
#endif
