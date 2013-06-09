#ifndef __Jugador_
#define __Jugador_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>

#include "../Modelo/Modelo.h"
#include "EscenaAjedrez.h"

#include "../Modelo/Movimientos.h"



class Jugador
{
public:
    ~Jugador();
    Jugador(EscenaAjedrez* miEscena, Modelo* modelo);

    virtual bool esHumano() = 0;

   // ModeloTablero tableroInicial;

    virtual void mueveFicha() = 0;
//bool esperaEleccion;
    //virtual void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada) = 0;
    int aplicaSeleccion();

    std::string getNombre();
    void setNombre( std::string unNombre);


    void promocionaPeon();


    bool activaMovimiento();

    virtual bool casillaSobrevolada(const std::string nombreCasilla);


    void esperaJugador();


    Modelo* modelo;
    bool jugadorNegras;





protected:
   EscenaAjedrez* escena;
 //  Tablero* tablero;

    std::string nombre;
    int* resgistroTablero;
    int alPaso;
  //  bool turnoNegras;

private:
};

#endif
