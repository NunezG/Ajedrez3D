#ifndef __Modelo_
#define __Modelo_
#include <Ogre.h>
//#include "EscenaAjedrez.h"
#include "ModeloMenu.h"
#include "Tablero.h"


class Modelo
{
public:
    bool getApagar();
    int getNumPantalla();

//    EscenaAjedrez* escena;
    ModeloMenu* menu;

    int modoJuego;
    void construyeAjedrez();
    void construyeMenu();

    //Singleton
    static Modelo* getSingletonPtr();

    std::string* resolucion;

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

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::Root *mRoot;
    Ogre::SceneManager* mSceneMgr;

    Tablero* tablero;


};

#endif
