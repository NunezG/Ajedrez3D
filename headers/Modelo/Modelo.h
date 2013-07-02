#ifndef __Modelo_
#define __Modelo_

//#include "ArbolBusqueda.h"
#include "Autorizaciones.h"

class Modelo
{
public:
    ~Modelo(void);
    //Singleton
    static Modelo* getSingletonPtr();

    int mueveTablero();
    int autorizaCasilla(tipoFicha tipo);

    ModeloTablero* tableroModelo;
    unsigned char jugadaElegida[2];

private:
    void agregaJugada(int inicio, int fin);

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);
};

#endif
