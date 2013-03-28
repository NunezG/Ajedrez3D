#ifndef __Ventana_
#define __Ventana_


#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

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


class Ventana : public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener
{
public:
    //Singleton
    static Ventana* getCEGUISingletonPtr();

     ~Ventana(void);

    //Iniciación
    bool iniciaVentana();
    void iniciaIO(void);
    bool EmpiezaCEGUI();

    //Pantallas
    bool MuestraMenu();
    bool muestraAjedrez();
    bool muestraAjedrezSolo();


    int getFPS();

    int pantallaActual();

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    Ogre::RenderWindow* getVentana();
    bool mShutDown;
    int mPantalla;

    BaseVistas* vista;

   // BaseApplication* Create(Ogre::String type);


    bool capturaRaton;

private:

    bool injectTimePulse(const Ogre::FrameEvent& evt);
    bool statUpdate(const Ogre::FrameEvent& evt);
    void capture();

    //Unattach OIS before window shutdown (very important under Linux)
    //Ogre::WindowEventListener
    void windowClosed(Ogre::RenderWindow* rw);
    void windowResized(Ogre::RenderWindow* rw);

    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


    //Singleton;
    Ventana(void);
    void operator=(const Ventana& frameListener ) ;
    Ventana(const Ventana& ventana);

    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::Root* mRoot;
    Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()

    unsigned long mLastStatUpdateTime;    // The last time the stat text were updated

    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
    CEGUI::Window *sheet;
    CEGUI::System* sys;

   // MenuInicio* menu;

    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
};


#endif
