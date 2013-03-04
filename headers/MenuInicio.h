#ifndef __MenuInicio_
#define __MenuInicio_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <Ogre.h>

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

    CEGUI::Window *sheetWindow;
    CEGUI::Window *quitButton;
    CEGUI::Window *mBotonJTurnos;

    CEGUI::FrameWindow* fWnd;
};

#endif
