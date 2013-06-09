#ifndef __Casilla_
#define __Casilla_

#include "ObjetoOgre.h"


struct posicion{
    int Fila;
    int Columna;

};


class Casilla : public ObjetoOgre
{
public:
    ~Casilla(void);
    Casilla(std::string nombre);

    void iluminaCasilla();
    void apagaCasilla();
    void trasladarAPunto();
    void setPosicion(int posFila, int posCol);
    posicion getPosicion();

    bool esNegra;

protected:

    posicion posCasilla;

private:
};

#endif
