#ifndef __Modelo_
#define __Modelo_

#include "Autorizaciones.h"
#include "ArbolBusqueda.h"

class Modelo
{
public:

    //Singleton
    static Modelo* getSingletonPtr();
    ModeloTablero* tableroModelo;


    int autorizaCasilla(tipoFicha tipo);

    int agregaJugada(int inicio, int fin);
    bool jugadaAutorizada;
    int* mueveTablero();

    bool evaluaJaque();

    bool construyeArbol();

    ~Modelo(void);
protected:

private:


    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);
    // unsigned long mLastStatUpdateTime;    // The last time the stat text were updated
    int autoriza(tipoFicha tipo);
    // Ogre::Root *mRoot;
    // Ogre::SceneManager* mSceneMgr;

    //Tablero* tablero;
};

#endif
