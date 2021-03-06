#ifndef __ModeloVista_
#define __ModeloVista_

#include "JugadorArtificial.h"
#include "JugadorHumano.h"


class  ModeloVista
{
public:
    ModeloVista();
    ~ModeloVista(void);

    void setNumPantalla(int pantalla);
    void setApagar(bool apaga);
    int getNumPantalla();
    bool getApagar();

    void generaJugadores();
    void creaEscenaYModelo();

    Jugador* JugadorActivo;
    EscenaAjedrez* escena;
    Modelo* modelo;
    std::string resolucion;
    int dificultad;
    int modoJuego;



    void aplicaCambio();

private:   
    char traduceTablero();

    std::vector<Jugador*> jugadores;
    bool pantallaCompleta;
    int numJugadores;
    bool mShutDown;
    int numPantalla;
    bool reiniciar;
};

#endif
