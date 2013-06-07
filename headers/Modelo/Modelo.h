#ifndef __Modelo_
#define __Modelo_
//#include <Ogre.h>
#include "Autorizaciones.h"
//#include "ModeloTablero.h"
#include "ArbolBusqueda.h"

//#include "../Vistas/EscenaAjedrez.h"

class Modelo
{
public:
    //  std::string nombreBlancas;
    // std::string nombreNegras;
    // int modoJuego;
    //    EscenaAjedrez* escena;
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
    int autoriza(tipoFicha tipo);

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);
    // unsigned long mLastStatUpdateTime;    // The last time the stat text were updated

    // Ogre::Root *mRoot;
    // Ogre::SceneManager* mSceneMgr;

    //Tablero* tablero;
};

#endif
