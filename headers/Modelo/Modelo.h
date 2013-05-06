#ifndef __Modelo_
#define __Modelo_
#include <Ogre.h>
//#include "EscenaAjedrez.h"
#include "ModeloMenu.h"


#include "../Vistas/EscenaAjedrez.h"


class Modelo
{
public:

    std::string resolucion;
    bool salirPulsado;

    ModeloMenu* menu;

    int modoJuego;

    int numJugadores;
    std::vector<Jugador*> jugadores;
    Jugador* jugadorActual;


    void mueveFicha(float time);
    void creaJugador(bool blancas, bool humano);

    bool getApagar();
    int getNumPantalla();
    void setNumPantalla(int pantalla);

//    EscenaAjedrez* escena;

    void construyeMenu();

    //Singleton
    static Modelo* getSingletonPtr();


    bool getSalir();

    void setSalir(bool salir);


    void destruyeMenu();




  EscenaAjedrez* escenaAjedrez;


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
