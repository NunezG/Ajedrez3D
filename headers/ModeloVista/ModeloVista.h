#ifndef __ModeloVista_
#define __ModeloVista_

#include "../Modelo/Modelo.h"
#include "EscenaAjedrez.h"
//#include "../Vistas/VistaAjedrez.h"





class  ModeloVista
{
public:
    ModeloVista(Modelo* modelo);
    ~ModeloVista(void);

    //Singleton
    static ModeloVista* getSingletonPtr();
Modelo* modelo;

void cambiaPantalla(int pantallaNueva);


int getNumPantalla();
void setNumPantalla(int pantalla);

void setSalir(bool salir);
bool iniciaModeloAjedrez();

EscenaAjedrez* escena;
std::string resolucion;
bool getApagar();
void setApagar(bool apaga);


//Jugador* jugadorActual;

void cambiaTurno();


bool preparaEscena();

private:   


bool mShutDown;
int mPantalla;

};

#endif
