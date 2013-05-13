#ifndef __BaseVistas_
#define __BaseVistas_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../Modelo/Modelo.h"


class BaseVistas
{
public:
    BaseVistas(void);
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

    Modelo* modelo;
    bool jaqueMate();

    bool iniciaVentana();
    int getFPS();
    void capture();
    Ogre::RenderWindow* getVentana();

    bool configuraGraficos(const char *desiredRenderer);



    //OIS Input devices
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
    OIS::InputManager* mInputManager;

private:

 //bool salir;

};




#endif
