#ifndef __ModeloVista_
#define __ModeloVista_

#include "../Modelo/Modelo.h"
#include "EscenaAjedrez.h"
//#include "../Vistas/VistaAjedrez.h"


#include "JugadorArtificial.h"
#include "JugadorHumano.h"


class  ModeloVista
{
public:
    ModeloVista(Modelo* modelo);
    ~ModeloVista(void);

    //Singleton
    static ModeloVista* getSingletonPtr();
Modelo* modelo;
int numJugadores;

void cambiaPantalla(int pantallaNueva);
bool botonIzquierdo();


int getNumPantalla();
void setNumPantalla(int pantalla);

void setSalir(bool salir);
bool getSalir();

bool iniciaModeloAjedrez();


EscenaAjedrez* escena;
std::string resolucion;
bool getApagar();
void setApagar(bool apaga);


//Jugador* jugadorActual;

void cambiaTurno();

bool reiniciaVista();

bool preparaEscena();

void creaJugador(bool blancas, bool humano);

std::vector<Jugador*> jugadores;

void miraCambios();

private:   



bool mShutDown;
int mPantalla;
bool reiniciar;
};

#endif
