#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

#include <CEGUI/CEGUIVector.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIWindow.h>
#include <CEGUI/CEGUISystem.h>

#include "Tablero.h"

class  EscenaAjedrez
{
public:

    EscenaAjedrez();
    ~EscenaAjedrez(void);

    void setTarget(Ogre::SceneNode* target);
    Tablero* getTablero();
    bool vaIzquierda();
    bool vaDerecha();
    void empezarModoCamara();
    void acabarModoCamara();
    bool esModoCamara();
    void mueveCamaraIzquierda();
    void mueveCamaraDerecha();
    void noMueveCamara();
    void apagaVentanaEmergente();
    void muestraVentanaEmergente(std::string nombreLayout);

    void createScene();
    Ogre::Camera* createCamera(void);
    void createViewports(Ogre::RenderWindow* window);
    void destruyeTablero();

    void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);
    Ogre::RaySceneQueryResult& executeRay(int posx, int posy, char mascara);
    std::string encuentraCasillaSobrevolada(CEGUI::Vector2 mCursorPosition);

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
