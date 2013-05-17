#ifndef __Modelo_
#define __Modelo_
//#include <Ogre.h>
//#include "EscenaAjedrez.h"

//#include "ModeloTablero.h"

#include "../Modelo/JugadorArtificial.h"
#include "../Modelo/JugadorHumano.h"


//#include "../Vistas/EscenaAjedrez.h"




class Modelo
{
public:

    std::string nombreBlancas;
    std::string nombreNegras;


    int modoJuego;

    int numJugadores;
    std::vector<Jugador*> jugadores;
    Jugador* jugadorActual;


    void mueveJugador(bool turno);
    void creaJugador(bool blancas, bool humano,ModeloTablero* tablero );



//    EscenaAjedrez* escena;


    //Singleton
    static Modelo* getSingletonPtr();




 // EscenaAjedrez* escenaAjedrez;


    ~Modelo(void);


protected:


private:  

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);


    unsigned long mLastStatUpdateTime;    // The last time the stat text were updated

   // Ogre::Root *mRoot;
   // Ogre::SceneManager* mSceneMgr;

    //Tablero* tablero;


};

#endif
