#ifndef __CreacionJuego_h_
#define __CreacionJuego_h_

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "EscenaAjedrez.h"
//#include "TutorialApplication.h"


#include "CEGUIFrameListener.h"

//#include "TutorialApplication.h"
//#include "MenuInicial.h"




class CreacionJuego : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
    CreacionJuego(void);
    ~CreacionJuego(void);

    void go(void);


    Ogre::SceneManager* mSceneMgr;
    virtual void createGUI(void) = 0;
   // void creaTablero(void);


protected:
    Ogre::RenderWindow* mWindow;
    int mModoJuego;


    virtual void createMainMenu(void) = 0; // Override me!

    void destroyScene(void);
    void setupResources(void);
    void createResourceListener(void);
    void loadResources(void);
    bool setup();
    void iniciaIO(void);
    bool configuraGraficos(const char *desiredRenderer);
    bool configureOpenGL(void);
    bool configureOgre(void);
    void chooseSceneManager(void);

 //  void createOverlay();

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    void windowClosed(Ogre::RenderWindow* rw);

    Ogre::Root *mRoot;
    //OIS Input devices
    OIS::InputManager* mInputManager;



    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

    int mPantalla;
    CEGUIFrameListener* mFrameListener;
 // CEGUI::OgreRenderer* mRenderer;



 //  InputMan::SdkCameraMan* mInputMan;

  //  Ogre::Camera* mCamera;
    bool mShutDown;
    bool statUpdate(const Ogre::FrameEvent& evt);
    Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()



 //   Ogre::OverlayContainer* mCursor;      // cursor

    // Ogre::FrameListener

    //BUCLE PRINCIPAL
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

private:


    unsigned long mLastStatUpdateTime;    // The last time the stat text were updated
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
};

#endif // #ifndef __CreacionJuego_h_
