#ifndef __Ventana_
#define __Ventana_


#include <iostream>

#include <Ogre.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

#include <OIS.h>
#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreConfigFile.h>

#include "MenuInicio.h"
//#include "EscenaAjedrez.h"

#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"



class Ventana : public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener,  public Ogre::FrameListener
{
public:
    Ventana(ModeloVista* modeloVista);

     ~Ventana(void);

    void loadResources(void);

    void destroyScene(void);
    //Iniciación

    bool start(void);

    bool resetOgre(void);
    bool initOgre(void);


    //Pantallas
    bool MuestraMenu();

    int pantallaActual();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

  //  int mPantalla;
    BaseVistas* vista;
   // BaseApplication* Create(Ogre::String type);


    bool ventanaCerrada();
    void destruyeVista();
    void creaVista();
    bool CEGUIResources();

    Ogre::Root *mRoot;


private:

    ModeloVista* modeloVista;


    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);


  //  Ogre::SceneManager* mSceneMgr;
  //  Ogre::Root* mRoot;
   // Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()


    CEGUI::System* sys;

   // MenuInicio* menu;

};


#endif
