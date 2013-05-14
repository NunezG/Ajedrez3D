#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_




//#include "../Model o/Modelo.h"

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


#include "../Modelo/Tablero.h"


#include "../Modelo/JugadorArtificial.h"
#include "../Modelo/JugadorHumano.h"




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



    void DistanciaCamara(int distanciaRelativa);

    void rotacionCamara(Ogre::Degree angulo);
    void destruyeTablero();


    Ogre::SceneNode* mTarget;
    Ogre::String columnas;

    //std::vector<Tablero*> HistorialMovimientos;

   Tablero* tablero;
   Ogre::SceneManager* mSceneMgr;
   Ogre::Camera* mCamera;

   Tablero* getTablero();

   Ogre::RaySceneQueryResult& executeRay(int posx, int posy, char mascara);
   Ogre::RaySceneQuery* createRayQuery(void);



   bool vaIzquierda();
   bool vaDerecha();
 bool esModoCamara();
 void mueveCamaraIzquierda();
 void mueveCamaraDerecha();

 void noMueveCamara();

 void empezarModoCamara();
 void acabarModoCamara();
private:   
   Ogre::RaySceneQuery *mRaySceneQuery;


   Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);

    //Ogre::Entity *entTablero;
     //Singleton;
     EscenaAjedrez(void);
     void operator=(const EscenaAjedrez& escena ) ;
     EscenaAjedrez(const EscenaAjedrez& escena);

    void creaIluminacion();
    void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist);


   // bool turnoNegras;

    // InputMan::SdkCameraMan* mInputMan;

    //  bool mCambiaTurno;


    Ogre::RenderWindow* mWindow;


    Ogre::Real mTopSpeed;
    bool mGoingLeft;

    bool mGoingRight;

    bool mOrbiting;
  //  Modelo* modelo;

};

#endif
