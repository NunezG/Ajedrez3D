#ifndef __Jugador_
#define __Jugador_

#include "Tablero.h"


class Jugador
{
public:
    ~Jugador(void);
    Jugador(Tablero* tablero);

    virtual bool esHumano() = 0;

   // TableroPrueba tableroInicial;
    bool jugadorNegras;

    virtual void mueveFicha(float time) = 0;
//bool esperaEleccion;

protected:


   Tablero* miTablero;

private:
};

#endif
