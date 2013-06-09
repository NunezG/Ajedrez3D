#ifndef __ModeloVista_
#define __ModeloVista_

#include "JugadorArtificial.h"
#include "JugadorHumano.h"


class  ModeloVista
{
public:
    ModeloVista();
    ~ModeloVista(void);

    int getNumPantalla();
    void setNumPantalla(int pantalla);
    void setSalir(bool salir);
    bool getSalir(); 
    bool getApagar();
    void setApagar(bool apaga);

    bool iniciaModeloAjedrez();
    bool generaJugadores();
    bool creaModeloTablero();
    void cambiaPantalla(int pantallaNueva);
    bool botonIzquierdo();
    int* traduceTablero();
    bool seleccionaFichaEnPosicion(CEGUI::Vector2 pos);
    bool reiniciaVista();
    bool preparaEscena();
    void creaJugador(bool blancas, bool humano);
    void miraCambios();
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
