#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include "../Modelo/ArbolBusqueda.h"


class JugadorArtificial : public Jugador
{
public:
    ~JugadorArtificial();
    JugadorArtificial(EscenaAjedrez* miEscena, Modelo* modelo);
    void mueveIA();
private:
    bool esHumano();
    bool casillaSobrevolada(const std::string nombreCasilla);
    void calculaMovimiento();
    int dificultad;
};


#endif