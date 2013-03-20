#ifndef __Modelo_
#define __Modelo_
#include <Ogre.h>
#include "Tablero.h"

class Modelo
{
public:
    bool getApagar();
    int getNumPantalla();
    ~Modelo(void);

    bool creaFichas();

    Tablero* tablero;
    bool construyeArbol();
    bool generaMovimientos();


private:  

    bool mShutDown;
    int mPantalla;

    unsigned long mLastStatUpdateTime;    // The last time the stat text were updated

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::Root *mRoot;
    Ogre::SceneManager* mSceneMgr;

};

#endif
