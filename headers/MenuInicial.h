
#ifndef __MenuInicial_
#define __MenuInicial_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI/CEGUISystem.h>
#include "CreacionJuego.h"
#include "TutorialApplication.h"



class  MenuInicial : public CreacionJuego
{
public:
    MenuInicial(void);
    virtual ~MenuInicial(void);


    bool setupMenu(void);



    virtual void createGUI(void);
    bool quit(const CEGUI::EventArgs    &e);
    bool juegoPorTurnos(const CEGUI::EventArgs &e);

protected:



//void createGUI(void);
    virtual void createMainMenu(void);

 CEGUI::Window *quitButton;
 CEGUI::Window *mBotonJTurnos;
 CEGUI::FrameWindow* fWnd;
   // CEGUI::System* mGUISystem;
    CEGUI::Window *sheet;





};

#endif // #ifndef __TutorialApplication_h_
