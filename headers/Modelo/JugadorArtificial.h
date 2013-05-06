#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include "../Modelo/ModuloIA.h"


class JugadorArtificial : public Jugador
{
public:

    ~JugadorArtificial(void);
    JugadorArtificial(Tablero* tablero);

    bool esHumano();
    void mueveFicha(float time);
    //void setVentana(Ventana* obj);

    int dificultad;

private:
    void calculaMovimiento();
    int* mueveIA(int origen, int destino);






};


#endif
