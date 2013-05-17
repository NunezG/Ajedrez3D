#ifndef __Jugador_
#define __Jugador_

//#include "ModeloTablero.h"

#include "../Modelo/Autorizaciones.h"

class Jugador
{
public:
    ~Jugador(void);
    Jugador(ModeloTablero* tablero);

    virtual bool esHumano() = 0;

   // ModeloTablero tableroInicial;
    bool jugadorNegras;

    virtual void mueveFicha() = 0;
//bool esperaEleccion;
    //virtual void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada) = 0;
    int* mueveTablero( int filaSel, int colSel, int filaNueva, int colNueva );

protected:


   ModeloTablero* miTablero;

private:
};

#endif
