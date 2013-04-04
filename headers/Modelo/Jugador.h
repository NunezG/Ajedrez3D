#ifndef __Jugador_
#define __Jugador_
#include "Tablero.h"



class Jugador
{
public:
    ~Jugador(void);
    Jugador();

   // TableroPrueba tableroInicial;

protected:

    virtual void mueveFicha() = 0;

    Tablero miTablero;

private:
};

#endif
