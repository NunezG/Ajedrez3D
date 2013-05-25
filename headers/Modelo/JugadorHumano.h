#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:

    ~JugadorHumano(void);
    JugadorHumano();

    bool esHumano();


    //void setVentana(Ventana* obj);
    int* mueveFicha(ModeloTablero* tablero);


   int autorizaCasilla(int* tablero, tipoFicha tipo, int filaSel, int colSel, int filaNueva, int colNueva, bool turnoNegras, int alPaso);

  //  void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);




protected:





private:  

   // Ventana* ventana;



};


#endif
