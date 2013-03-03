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

class Ventana : public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener
{
public:


    //Singleton
    static Ventana& getCEGUISingleton();


    bool iniciaVentana();

    ~Ventana(void);


    bool MuestraMenu();


    bool EmpiezaCEGUI();
   // EmpiezaCEGUI(Ogre::RenderWindow* mWindow);

    //virtual ~Ventana(void);

    //bool quit(const CEGUI::EventArgs &e);

    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


  //  void iniciaCEGUI();
    bool statUpdate(const Ogre::FrameEvent& evt);


    bool injectTimePulse(const Ogre::FrameEvent& evt);

    // CEGUI::System* mGUISystem;
    CEGUI::Window *sheet;

    CEGUI::System* sys;
Ogre::Root* mRoot22;
   // Ogre::Root *mRoot;

    // Ogre::WindowEventListener

    //Unattach OIS before window shutdown (very important under Linux)
    //Ogre::WindowEventListener
    void windowClosed(Ogre::RenderWindow* rw);
    void windowResized(Ogre::RenderWindow* rw);
   // Ogre::RenderWindow* mWindow;
    void iniciaIO(void);
    Ogre::RenderWindow* getVentana();
    void capture();


    bool mShutDown;
    int mPantalla;
private:

    //Singleton;
    //static Ventana* miFrameListener;
    void operator=(const Ventana& frameListener ) ;
    Ventana(void);
    Ventana(const Ventana& ventana);

    Ogre::RenderWindow* mWindow;
    Ogre::Root* mRoot;
    Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()


    unsigned long mLastStatUpdateTime;    // The last time the stat text were updated


    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

MenuInicio* menu;


    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

};
