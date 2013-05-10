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


    //virtual bool salir() = 0;

    virtual bool keyPressed( const OIS::KeyEvent &arg ) = 0;
    virtual bool keyReleased( const OIS::KeyEvent &arg ) = 0;
    virtual bool mouseMoved( const OIS::MouseEvent &arg ) = 0;
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) = 0;
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )= 0;

   // virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;
    virtual bool esMenuInicio() = 0;

    Modelo* modelo;
    bool jaqueMate();


private:

 //bool salir;

};




#endif
