#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>



//#include <OgreConfigFile.h>


#include <CEGUI/CEGUIVector.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIWindow.h>
#include <CEGUI/CEGUISystem.h>


#include "Tablero.h"



//#define TABLERO 1 << 3
//#define CASILLA 1 << 0  // Mascara para el escenario


class  EscenaAjedrez
{
public:

    EscenaAjedrez();
    ~EscenaAjedrez(void);

    void createScene();

    // void createCamera(void);

    Ogre::Camera* createCamera(void);
    void createViewports(Ogre::RenderWindow* window);


    void setTarget(Ogre::SceneNode* target);

  //  Casilla* casillaOcupada(Casilla* nodoCasilla);


    void DistanciaCamara(int distanciaRelativa);

    void rotacionCamara(Ogre::Degree angulo);
    void destruyeTablero();



    Tablero* getTablero();

    Ogre::RaySceneQueryResult& executeRay(int posx, int posy, char mascara);

    bool vaIzquierda();
    bool vaDerecha();
    bool esModoCamara();
    void mueveCamaraIzquierda();
    void mueveCamaraDerecha();

    void noMueveCamara();

    void empezarModoCamara();
    void acabarModoCamara();

    std::string encuentraCasillaSobrevolada(CEGUI::Vector2 mCursorPosition);


    void apagaVentanaEmergente();

    void muestraVentanaEmergente(std::string nombreLayout);


    Ogre::SceneNode* mTarget;
    Ogre::String columnas;

    //std::vector<Tablero*> HistorialMovimientos;
    Tablero* tablero;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera* mCamera;
private:   



    //Modelo* modelo;

    Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);


    void creaIluminacion();
    void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist);




    // bool turnoNegras;

    // InputMan::SdkCameraMan* mInputMan;

    //  bool mCambiaTurno;

    CEGUI::Window *ventanaEmergente;
    Ogre::RenderWindow* mWindow;
    Ogre::RaySceneQuery *mRaySceneQuery;

    Ogre::Real mTopSpeed;
    bool mGoingLeft;

    bool mGoingRight;

    bool mOrbiting;
    //  Modelo* modelo;

};

#endif
