#ifndef __Jugador_
#define __Jugador_
#include <algorithm>    // std::for_each
//#include <deque>       // std::vector
#include <iostream>
#include <string>

#include "../Modelo/Modelo.h"
#include "../Modelo/Movimientos.h"
#include "EscenaAjedrez.h"

class Jugador
{
public:
    ~Jugador();
    virtual bool casillaSobrevolada(const std::string nombreCasilla);
    virtual bool esHumano() = 0;
  //  bool jugadorNegras;
    virtual bool botonDerecho() = 0;
    virtual bool botonIzquierdo(CEGUI::Vector2 pos) = 0;

    virtual bool aplicaSeleccion();

   virtual bool iniciaTurno() = 0;

protected:
    Jugador(EscenaAjedrez* miEscena, Modelo* modelo);

    Modelo* modelo;
   EscenaAjedrez* escena;
private:
   //bool aplicaCambio();
    std::string getNombre();
    void setNombre( std::string unNombre);
    std::string nombre;
    int* resgistroTablero;
    int alPaso;

};

#endif
