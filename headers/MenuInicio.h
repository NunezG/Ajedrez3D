/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __MenuInicio_
#define __MenuInicio_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <Ogre.h>
//#include "Ventana.h"



class MenuInicio
{
public:
    MenuInicio();//Ventana* mFrameListener);
    ~MenuInicio(void);

  virtual CEGUI::FrameWindow* createGUI(void);
    int modoJuego;
    bool salirPulsado;


protected:


    bool botonSalir(const CEGUI::EventArgs    &e);
    bool botonJuegoTurnos(const CEGUI::EventArgs &e);


  //  Ventana* mFrameListener;

    CEGUI::Window *sheetWindow;
    CEGUI::Window *quitButton;
    CEGUI::Window *mBotonJTurnos;


    CEGUI::FrameWindow* fWnd;


};

#endif // #ifndef __TutorialApplication_h_
