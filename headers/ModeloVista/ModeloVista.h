#ifndef __ModeloVista_
#define __ModeloVista_

#include "../Modelo/ModeloTablero.h"
#include "EscenaAjedrez.h"
//#include "../Vistas/VistaAjedrez.h"


#include "JugadorArtificial.h"
#include "JugadorHumano.h"


class  ModeloVista
{
public:
    ModeloVista();
    ~ModeloVista(void);


    int numJugadores;

    void cambiaPantalla(int pantallaNueva);
    bool botonIzquierdo();


    int getNumPantalla();
    void setNumPantalla(int pantalla);

    void setSalir(bool salir);
    bool getSalir();

    bool iniciaModeloAjedrez();
    bool generaJugadores();


    Modelo* modelo;
    EscenaAjedrez* escena;

    bool pantallaCompleta;
    std::string resolucion;
    bool getApagar();
    void setApagar(bool apaga);
    bool creaModeloTablero();


    //Jugador* jugadorActual;

    int* traduceTablero();

    bool seleccionaFichaEnPosicion(CEGUI::Vector2 pos);

    bool reiniciaVista();

    bool preparaEscena();

    void creaJugador(bool blancas, bool humano);

    std::vector<Jugador*> jugadores;
    Jugador* JugadorActivo;

    void miraCambios();

    //void cambiaTurno();
    bool aplicaCambio();

private:   



    bool mShutDown;
    int mPantalla;
    bool reiniciar;
};

#endif
