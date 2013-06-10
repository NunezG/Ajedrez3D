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
    virtual bool casillaSobrevolada(const std::string nombreCasilla);
    virtual bool esHumano() = 0;
    int aplicaSeleccion();
    void promocionaPeon();
    bool jugadorNegras;

protected:
    Jugador(EscenaAjedrez* miEscena, Modelo* modelo);

    Modelo* modelo;
   EscenaAjedrez* escena;
private:


    std::string getNombre();
    void setNombre( std::string unNombre);


    std::string nombre;
    int* resgistroTablero;
    int alPaso;

};

#endif
