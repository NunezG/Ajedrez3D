#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_

#include <Ogre.h>
#include "InputMan.h"

#define CASILLA 1 << 0  // Mascara para el escenario
#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3

class  EscenaAjedrez
{
public:
    ~EscenaAjedrez(void);

    //Singleton
    static EscenaAjedrez* getSingletonPtr();


    void createScene(Ogre::SceneManager*);

    void promocionaPeon(Ogre::SceneNode* nodoFicha);

   // void createCamera(void);

    void iluminaCasilla();
    Ogre::Camera* createCamera(void);
    void createViewports(Ogre::RenderWindow* window);
    Ogre::RaySceneQueryResult& executeRay(int posx, int posy, char mascara);
    Ogre::RaySceneQuery* createRayQuery(void);

    void iluminaCasilla(Ogre::SceneNode* casilla);
    void apagaCasilla(Ogre::SceneNode* casilla);

    Ogre::SceneNode* casillaOcupada(Ogre::SceneNode* nodoCasilla);

    void setSceneManager(Ogre::SceneManager* sceneMgr);

    void mueveCamaraIzquierda();
    void mueveCamaraDerecha();

    void noMueveCamara();


    void empezarModoCamara();
    void acabarModoCamara();
    InputMan::SdkCameraMan* mInputMan;
    bool mOrbiting;


    bool mGoingLeft;
  //  bool mCambiaTurno;
    bool mGoingRight;
private:   



    Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);

    //Singleton;
    EscenaAjedrez(void);
    void operator=(const EscenaAjedrez& escena ) ;
    EscenaAjedrez(const EscenaAjedrez& escena);


    Ogre::RenderWindow* mWindow;

    Ogre::SceneManager* mSceneMgr;
    Ogre::RaySceneQuery *mRaySceneQuery;

    Ogre::Camera* mCamera;

    void creaFichas();
    void creaCasillas();

    void creaPeones();
    void creaNobleza();
    void creaVasallos();



    Ogre::String columnas;
    Ogre::SceneNode* nodoTablero;
    Ogre::SceneNode* nodoCasillero;
};

#endif
