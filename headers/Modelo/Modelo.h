#ifndef __Modelo_
#define __Modelo_

#include "Autorizaciones.h"
#include "ArbolBusqueda.h"

class Modelo
{
public:
    ~Modelo(void);
    //Singleton
    static Modelo* getSingletonPtr();

    int* mueveTablero();
    int autorizaCasilla(tipoFicha tipo);
    bool construyeArbol();

    ModeloTablero* tableroModelo;

private:
    int agregaJugada(int inicio, int fin);
   // bool jugadaAutorizada;
    bool evaluaJaque();

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);
};

#endif
