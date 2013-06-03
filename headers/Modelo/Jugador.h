#ifndef __Jugador_
#define __Jugador_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>
#include "Movimientos.h"



class Jugador
{
public:
    ~Jugador(void);
    Jugador();

    virtual bool esHumano() = 0;

   // ModeloTablero tableroInicial;

    virtual void mueveFicha(ModeloTablero* tablero) = 0;
//bool esperaEleccion;
    //virtual void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada) = 0;
    int aplicaSeleccion(ModeloTablero* tablero);


    std::string getNombre();
    void setNombre( std::string unNombre);



    bool jugadorNegras;

protected:


   ModeloTablero* miTablero;

    std::string nombre;
    int* resgistroTablero;
    int alPaso;
  //  bool turnoNegras;



private:
};

#endif
