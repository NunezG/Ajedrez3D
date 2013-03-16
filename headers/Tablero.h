#ifndef __Tablero_
#define __Tablero_

#include "FichaAlfil.h"
#include "FichaCaballo.h"
#include "FichaTorre.h"
#include "FichaReina.h"
#include "FichaRey.h"
#include "FichaPeon.h"



class Tablero
{
public:
    ~Tablero(void);
    Ficha* fichasNegras[16];
    Ficha* fichasBlancas[16];

private:

    Ogre::Entity *entTablero;

    bool verificaCamino(int inicial[2], int final[2], int camino);



    int casillas[8][8];

    bool turnoNegras;

    //Singleton;
    Tablero(void);
    void operator=(const Tablero& miTablero) ;
    Tablero(const Tablero& miTablero);
    bool creaFichas();
};

#endif
