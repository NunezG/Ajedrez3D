#ifndef __Tablero_
#define __Tablero_

#include "Ficha.h"

class Tablero
{
public:
    ~Tablero(void);

private:

    Ogre::Entity *entTablero;

    bool verificaCamino(int inicial[2], int final[2], int camino);

    Ficha* fichasNegras[16];
    Ficha* fichasBlancas[16];

    int casillas[8][8];

    bool turnoNegras;

    //Singleton;
    Tablero(void);
    void operator=(const Tablero& miTablero) ;
    Tablero(const Tablero& miTablero);

};

#endif
