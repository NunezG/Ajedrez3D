#ifndef __BaseJuego_h_
#define __BaseJuego_h_

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
//#include "MenuInicio.h"


#include "Ventana.h"


//#include "MenuInicial.h"
#include <OgreRoot.h>




class BaseJuego : public Ogre::FrameListener
{
public:

    ~BaseJuego(void);

    void go(void);

    Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()

    virtual void inicio(void) = 0;
   // void creaTablero(void);
    virtual void cambiaPantalla() = 0;

 //   Ventana& mFrameListener;

Ventana* punteroVentana;

protected:
    BaseJuego(void);

    int mModoJuego;
    //Adjust mouse clipping area


   // virtual void createMainMenu(void) = 0; // Override me!

    void destroyScene(void);
    void setupResources(void);
    void createResourceListener(void);
    void loadResources(void);
    bool setup();
    bool configuraGraficos(const char *desiredRenderer);
    bool configureOpenGL();
    bool configureOgre(void);
    void chooseSceneManager(void);
 //  void createOverlay();

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
  //  virtual void windowResized(Ogre::RenderWindow* rw) = 0;
    //Unattach OIS before window shutdown (very important under Linux)
  //  virtual void windowClosed(Ogre::RenderWindow* rw) = 0;

    Ogre::Root *mRoot;


    MenuInicio* menu;

    //OIS Input devices
  //  OIS::InputManager* mInputManager;
  //  OIS::Mouse*    mMouse;
  //  OIS::Keyboard* mKeyboard;

   // Ventana mFrameListener;
 // CEGUI::OgreRenderer* mRenderer;



 //  InputMan::SdkCameraMan* mInputMan;

  //  Ogre::Camera* mCamera;
 //   virtual bool statUpdate(const Ogre::FrameEvent& evt) = 0;



 //   Ogre::OverlayContainer* mCursor;      // cursor

    // Ogre::FrameListener

    //BUCLE PRINCIPAL
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg ) = 0;
    virtual bool keyReleased( const OIS::KeyEvent &arg ) = 0;
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg ) = 0;
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) = 0;
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) = 0;

private:



    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
};

#endif // #ifndef __BaseJuego_h_
