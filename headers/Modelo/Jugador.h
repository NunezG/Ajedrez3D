#ifndef __Jugador_
#define __Jugador_

#include "ModeloTablero.h"


class Jugador
{
public:
    ~Jugador(void);
    Jugador(ModeloTablero* tablero);

    virtual bool esHumano() = 0;

   // ModeloTablero tableroInicial;
    bool jugadorNegras;

    virtual void mueveFicha(float time) = 0;
//bool esperaEleccion;
    virtual void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada) = 0;

protected:


   ModeloTablero* miTablero;

private:
};

#endif
