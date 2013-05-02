#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_




#include "../Modelo/Modelo.h"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>


#include <Ogre.h>
//#include "InputMan.h"
//#include "Tablero.h"





//#define TABLERO 1 << 3
//#define CASILLA 1 << 0  // Mascara para el escenario


class  EscenaAjedrez
{
public:

    ~EscenaAjedrez(void);

    //Singleton
    static EscenaAjedrez* getSingletonPtr();

    void createScene();

    // void createCamera(void);

    Ogre::Camera* createCamera(void);
    void createViewports(Ogre::RenderWindow* window);


    void setTarget(Ogre::SceneNode* target);

    Casilla* casillaOcupada(Casilla* nodoCasilla);

    void setSceneManager(Ogre::Root* mRoot);

    void mueveCamaraIzquierda();
    void mueveCamaraDerecha();

    bool vaIzquierda();
    bool vaDerecha();

    void noMueveCamara();

    bool esModoCamara();

    void empezarModoCamara();
    void acabarModoCamara();

    void DistanciaCamara(int distanciaRelativa);

    void rotacionCamara(Ogre::Degree angulo);


    Ogre::SceneNode* mTarget;
    Ogre::String columnas;

    //std::vector<Tablero*> HistorialMovimientos;

   Tablero* tablero;
   Ogre::SceneManager* mSceneMgr;
   Ogre::Camera* mCamera;

private:   

    //Ogre::Entity *entTablero;
     //Singleton;
     EscenaAjedrez(void);
     void operator=(const EscenaAjedrez& escena ) ;
     EscenaAjedrez(const EscenaAjedrez& escena);

    void creaIluminacion();
    void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist);


   // bool turnoNegras;

    // InputMan::SdkCameraMan* mInputMan;

    bool mGoingLeft;
    //  bool mCambiaTurno;
    bool mGoingRight;

    bool mOrbiting;

    Ogre::RenderWindow* mWindow;


    Ogre::Real mTopSpeed;

    Modelo* modelo;

};

#endif
