#ifndef __Jugador_
#define __Jugador_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>



class Jugador
{
public:
    ~Jugador(void);
    Jugador();

    virtual bool esHumano() = 0;

   // ModeloTablero tableroInicial;

    virtual void mueveFicha() = 0;
//bool esperaEleccion;
    //virtual void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada) = 0;


    bool jugadorNegras;

protected:


   //ModeloTablero* miTablero;

    int* resgistroTablero;
    int alPaso;
  //  bool turnoNegras;



private:
};

#endif
