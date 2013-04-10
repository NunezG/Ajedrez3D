#ifndef __Casilla_
#define __Casilla_

#include <Ogre.h>

#include "ObjetoOgre.h"


struct posicion{
    int Fila;
    int Columna;

};


class Casilla : public ObjetoOgre
{


    //struct testCasilla{
      //  Ogre::String posicion;
       // Ficha* fichaAsociada;


    //};


public:


    posicion getPosicion();

    bool esNegra;
    ~Casilla(void);
    Casilla(std::string nombre);


    void trasladarAPunto();

    void setPosicion(int posFila, int posCol);

protected:

    posicion posCasilla;




private:
};

#endif
