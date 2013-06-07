#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:

    ~JugadorHumano();
    JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo);

    bool esHumano();


    //void setVentana(Ventana* obj);
    void mueveFicha();


    bool activaMovimiento();

  //  void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);

   bool casillaSobrevolada(const std::string nombreCasilla);



protected:





private:  

   // Ventana* ventana;



};


#endif
