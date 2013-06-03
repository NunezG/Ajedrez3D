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
    void mueveFicha(ModeloTablero* tablero);


   int autorizaCasilla(ModeloTablero* tablero, tipoFicha tipo);

  //  void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);




protected:





private:  

   // Ventana* ventana;



};


#endif
