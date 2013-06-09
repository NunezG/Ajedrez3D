#ifndef __ModeloVista_
#define __ModeloVista_

#include "JugadorArtificial.h"
#include "JugadorHumano.h"


class  ModeloVista
{
public:
    ModeloVista();
    ~ModeloVista(void);

    void cambiaPantalla(int pantallaNueva);
    bool botonIzquierdo();


    int getNumPantalla();
    void setNumPantalla(int pantalla);

    void setSalir(bool salir);
    bool getSalir();

    bool iniciaModeloAjedrez();
    bool generaJugadores();

    bool getApagar();
    void setApagar(bool apaga);
    bool creaModeloTablero();


    //Jugador* jugadorActual;

    int* traduceTablero();

    bool seleccionaFichaEnPosicion(CEGUI::Vector2 pos);

    bool reiniciaVista();

    bool preparaEscena();

    void creaJugador(bool blancas, bool humano);


    void miraCambios();

    //void cambiaTurno();
    bool aplicaCambio();



    std::vector<Jugador*> jugadores;
    Jugador* JugadorActivo;
    Modelo* modelo;
    EscenaAjedrez* escena;

    bool pantallaCompleta;
    std::string resolucion;
    int numJugadores;

private:   



    bool mShutDown;
    int mPantalla;
    bool reiniciar;
};

#endif
