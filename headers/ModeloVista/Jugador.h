#ifndef __Jugador_
#define __Jugador_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>

#include "../Modelo/Modelo.h"
#include "../Modelo/Movimientos.h"
#include "EscenaAjedrez.h"

class Jugador
{
public:
    ~Jugador();
    Jugador(EscenaAjedrez* miEscena, Modelo* modelo);

    std::string getNombre();
    void setNombre( std::string unNombre);

    virtual bool esHumano() = 0;
    virtual void mueveFicha() = 0;
    int aplicaSeleccion();
    void promocionaPeon();
    bool activaMovimiento();
    virtual bool casillaSobrevolada(const std::string nombreCasilla);
    void esperaJugador();

    Modelo* modelo;
    bool jugadorNegras;

protected:
   EscenaAjedrez* escena;
    std::string nombre;
    int* resgistroTablero;
    int alPaso;

private:
};

#endif
