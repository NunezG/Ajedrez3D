#ifndef __BaseVistas_
#define __BaseVistas_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIWindow.h>
#include <CEGUI/CEGUIMinizipResourceProvider.h>
#include <CEGUI/CEGUIEventSet.h>

#include <CEGUI/CEGUI.h>


//#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

#include "../ModeloVista/EscenaAjedrez.h"
#include "../ModeloVista/ModeloVista.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>


class BaseVistas: public OIS::KeyListener, public OIS::MouseListener, public Ogre::FrameListener
{
public:
    BaseVistas(ModeloVista* modeloV, std::string label);
    ~BaseVistas(void);

   // int modoJuego;

  //  virtual bool mueveCamara(float frecuencia) = 0;
    //Unattach OIS before window shutdown (very important under Linux)
    //Ogre::WindowEventListener
    void windowClosed();
    void windowResized();

    //virtual bool salir() = 0;



    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

   // virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;

   // EscenaAjedrez* escena;

    bool iniciaOIS();
    int getFPS();
    void capture();
    Ogre::RenderWindow* getVentana();

    bool configuraGraficos(const char *desiredRenderer);
    bool iniciaCEGUI();

    void empieza();
    bool CEGUIResources();

    ModeloVista* modeloVista;

    //OIS Input devices
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
    OIS::InputManager* mInputManager;

    CEGUI::OgreRenderer* renderer;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
    CEGUI::System* sys;

    Ogre::Root *mRoot;
    Ogre::RenderWindow* mWindow;

private:

 //bool salir;

};




#endif
