#ifndef __Tablero_
#define __Tablero_

#include "FichaAlfil.h"
#include "FichaCaballo.h"
#include "FichaTorre.h"
#include "FichaReina.h"
#include "FichaRey.h"
#include "FichaPeon.h"


// ESTE SERÁ EL NODO USADO EN LOS ÁRBOLES
class Tablero
{
public:
    ~Tablero(void);
    Ficha* fichasNegras[16];
    Ficha* fichasBlancas[16];


    Tablero(void);


    int nivel;
private:


    Tablero* listaNodos[];


    Ogre::Entity *entTablero;

    bool verificaCamino(int inicial[2], int final[2], int camino);



    int casillas[8][8];

    bool turnoNegras;

    bool creaFichas();
};

#endif
