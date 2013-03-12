#ifndef __MenuInicio_
#define __MenuInicio_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <Ogre.h>
#include "BaseVistas.h"


class MenuInicio : public BaseVistas
{
public:

    MenuInicio();//Ventana* mFrameListener);
    ~MenuInicio(void);

   // CEGUI::FrameWindow* createGUI(void);
    bool salirPulsado;

    bool salir();
    bool iniciaVista();

    bool esMenuInicio();

protected:

    bool botonSalir(const CEGUI::EventArgs    &e);
    bool botonJuegoTurnos(const CEGUI::EventArgs &e);
    bool botonJuegoSolo(const CEGUI::EventArgs &e);

    CEGUI::Window *sheetWindow;
    CEGUI::Window *quitButton;
    CEGUI::Window *mBotonJTurnos;
    CEGUI::Window *mBotonJSolo;


    CEGUI::FrameWindow* fWnd;



    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

};

#endif
