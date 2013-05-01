#ifndef __Jugador_
#define __Jugador_
#include "Tablero.h"



class Jugador
{
public:
    ~Jugador(void);
    Jugador();

   // TableroPrueba tableroInicial;

    virtual bool esHumano() = 0;
    bool jugadorNegras;
    virtual void mueveFicha(float frecuencia) = 0;

protected:



    Tablero* tablero;

private:
};

#endif
