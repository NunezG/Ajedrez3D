#ifndef __Modelo_
#define __Modelo_
#include <Ogre.h>
//#include "EscenaAjedrez.h"

#include "ModeloTablero.h"

#include "../Modelo/JugadorArtificial.h"
#include "../Modelo/JugadorHumano.h"


//#include "../Vistas/EscenaAjedrez.h"




class Modelo
{
public:

    std::string resolucion;
    std::string nombreBlancas;
    std::string nombreNegras;

    bool salirPulsado;

    int modoJuego;

    int numJugadores;
    std::vector<Jugador*> jugadores;
    Jugador* jugadorActual;


    void mueveFicha(float time);
    void creaJugador(bool blancas, bool humano,ModeloTablero* tablero );

    bool getApagar();
    int getNumPantalla();
    void setNumPantalla(int pantalla);

//    EscenaAjedrez* escena;


    //Singleton
    static Modelo* getSingletonPtr();


    bool getSalir();

    void setSalir(bool salir);


 // EscenaAjedrez* escenaAjedrez;


    ~Modelo(void);


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

    //Tablero* tablero;


};

#endif
