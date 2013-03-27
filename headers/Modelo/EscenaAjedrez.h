#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_

#include <Ogre.h>
#include "InputMan.h"
#include "Tablero.h"

class  EscenaAjedrez
{
public:
    ~EscenaAjedrez(void);

    //Singleton
    static EscenaAjedrez* getSingletonPtr();

    void createScene();

    void promocionaPeon(Ogre::SceneNode* nodoFicha);

    // void createCamera(void);

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

    bool vaIzquierda();
    bool vaDerecha();

    void noMueveCamara();

    bool esModoCamara();

    void empezarModoCamara();
    void acabarModoCamara();

    void DistanciaCamara(int distanciaRelativa);

    void rotacionCamara(Ogre::Degree angulo);
    void cambiaTurno();
    bool esTurnoNegras();

    Ogre::SceneNode* getNodoFichaSeleccionada();
    Ogre::SceneNode* getNodoCasillaSobrevolada();

    void setNodoFichaSeleccionada(Ogre::SceneNode* nodo);
    void setNodoCasillaSobrevolada(Ogre::SceneNode* nodo);
    bool FichaComestible();

    Ogre::String columnas;

    // bool creaFichas();
private:   

    void creaIluminacion();

    Ogre::SceneNode *_selectedNode;
    Ogre::SceneNode *_nodoNuevo;

    bool turnoNegras;

    InputMan::SdkCameraMan* mInputMan;

    bool mGoingLeft;
    //  bool mCambiaTurno;
    bool mGoingRight;

    bool mOrbiting;

    Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);

    //Singleton;
    EscenaAjedrez(void);
    void operator=(const EscenaAjedrez& escena ) ;
    EscenaAjedrez(const EscenaAjedrez& escena);

    Ogre::RenderWindow* mWindow;

    Ogre::SceneManager* mSceneMgr;
    Ogre::RaySceneQuery *mRaySceneQuery;

    Ogre::Camera* mCamera;

    //void creaFichas();

    Tablero* tablero;
};

#endif
