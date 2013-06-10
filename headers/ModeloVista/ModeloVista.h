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


    bool botonIzquierdo();
    bool seleccionaFichaEnPosicion(CEGUI::Vector2 pos);
    bool generaJugadores();
    bool creaModeloTablero();

    Jugador* JugadorActivo;
    EscenaAjedrez* escena;
    Modelo* modelo;
    std::string resolucion;

private:   

    int* traduceTablero();
    void creaJugador(bool blancas, bool humano);
    bool aplicaCambio();

    std::vector<Jugador*> jugadores;
    bool pantallaCompleta;
    int numJugadores;
    bool mShutDown;
    int mPantalla;
    bool reiniciar;
};

#endif
