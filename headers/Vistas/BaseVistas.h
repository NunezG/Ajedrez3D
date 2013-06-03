#ifndef __BaseVistas_
#define __BaseVistas_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>


#include "../ModeloVista/EscenaAjedrez.h"

#include "../ModeloVista/ModeloVista.h"

class BaseVistas
{
public:
    BaseVistas(ModeloVista* modeloV, Ogre::Root* mRoot, std::string label);
    ~BaseVistas(void);


   // int modoJuego;

    virtual bool mueveCamara(float frecuencia) = 0;
    //Unattach OIS before window shutdown (very important under Linux)
    //Ogre::WindowEventListener
    void windowClosed();
    void windowResized();

    //virtual bool salir() = 0;
    Ogre::RenderWindow* mWindow;

    virtual bool keyPressed( const OIS::KeyEvent &arg ) = 0;
    virtual bool keyReleased( const OIS::KeyEvent &arg ) = 0;
    virtual bool mouseMoved( const OIS::MouseEvent &arg ) = 0;
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) = 0;
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )= 0;

   // virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;
    virtual bool esMenuInicio() = 0;

   // EscenaAjedrez* escena;

    bool iniciaOIS();
    int getFPS();
    void capture();
    Ogre::RenderWindow* getVentana();

    bool configuraGraficos(const char *desiredRenderer);

    ModeloVista* modeloVista;


    //OIS Input devices
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
    OIS::InputManager* mInputManager;

    CEGUI::OgreRenderer* renderer;

private:

 //bool salir;

};




#endif
