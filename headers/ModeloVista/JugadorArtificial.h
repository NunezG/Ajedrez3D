#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include "../Modelo/ArbolBusqueda.h"


class JugadorArtificial : public Jugador
{
public:
    ~JugadorArtificial();
    JugadorArtificial(EscenaAjedrez* miEscena, Modelo* modelo);
    bool aplicaSeleccion();
bool iniciaTurno();
private:
    bool botonIzquierdo(CEGUI::Vector2 pos);
    bool botonDerecho();
    bool mueveRaton(std::string casilla);
    bool esHumano();
    int dificultad;
};


#endif
