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
    Tablero* getTablero();
    void setModoCamara(bool modo);
    bool getModoCamara();
    void noMueveCamara();
    bool vaIzquierda();
    bool vaDerecha();
    void mueveCamaraIzquierda();
    void mueveCamaraDerecha();

    std::string encuentraCasillaSobrevolada(CEGUI::Vector2 mCursorPosition);

    void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);
    void createScene();
    void createCamera(void);
    void createViewports(Ogre::RenderWindow* window);

    void apagaVentanaEmergente();
    void muestraVentanaEmergente(std::string nombreLayout);

    Ogre::SceneManager* mSceneMgr;
private:
    Ogre::RaySceneQueryResult& executeRay(int posx, int posy, char mascara);

    CEGUI::Window *ventanaEmergente;
    Ogre::RenderWindow* mWindow;
    bool mGoingLeft;
    bool mGoingRight;
    bool modoCamara;
    Ogre::SceneNode* mTarget;
    Ogre::Camera* mCamera;
    Tablero* tablero;
     Ogre::RaySceneQuery *mRaySceneQuery;
};

#endif
