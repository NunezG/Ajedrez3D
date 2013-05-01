#ifndef __Modelo_
#define __Modelo_
#include <Ogre.h>
//#include "EscenaAjedrez.h"
#include "ModeloMenu.h"
#include "Tablero.h"
#include "JugadorHumano.h"
#include "JugadorArtificial.h"

class Modelo
{
public:


    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    std::string* resolucion;
    bool salirPulsado;

    ModeloMenu* menu;

    int modoJuego;

    std::vector<Jugador*> jugadores;
    int numJugadores;
    Jugador* jugadorActual;

    void creaJugador(bool negras, bool humano);

    void mueveFicha(float frecuencia);


    bool getApagar();
    int getNumPantalla();
    void setNumPantalla(int pantalla);

//    EscenaAjedrez* escena;

    void construyeAjedrez();
    void construyeMenu();

    //Singleton
    static Modelo* getSingletonPtr();


    bool getSalir();

    void setSalir(bool salir);

    void destruyeTablero();

    void destruyeMenu();

    ~Modelo(void);
    Tablero* getTablero();


protected:


private:  

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);

    bool mShutDown;
    int mPantalla;

    unsigned long mLastStatUpdateTime;    // The last time the stat text were updated

   // Ogre::Root *mRoot;
   // Ogre::SceneManager* mSceneMgr;

    Tablero* tablero;
};

#endif
