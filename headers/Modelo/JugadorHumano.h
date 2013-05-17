#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"


class JugadorHumano : public Jugador
{
public:

    ~JugadorHumano(void);
    JugadorHumano(ModeloTablero* tablero);

    bool esHumano();


    //void setVentana(Ventana* obj);
    void mueveFicha();

    int aplicaSeleccion(int filaSel, int colSel, int filaNueva, int colNueva);

    int autorizaCasilla(tipoFicha tipo, int filaSel, int colSel, int filaNueva, int colNueva);

  //  void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);

protected:




private:  

   // Ventana* ventana;



};


#endif
