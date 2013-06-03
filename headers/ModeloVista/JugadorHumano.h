#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:

    ~JugadorHumano();
    JugadorHumano(EscenaAjedrez* miEscena);

    bool esHumano();


    //void setVentana(Ventana* obj);
    void mueveFicha();


   int autorizaCasilla(ModeloTablero* tablero, tipoFicha tipo);

  //  void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);

   bool activaMovimiento();
   bool casillaSobrevolada(const std::string nombreCasilla);



protected:





private:  

   // Ventana* ventana;



};


#endif
