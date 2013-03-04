
#ifndef __ControlJuego_
#define __ControlJuego_


#include <CEGUI/CEGUISystem.h>
#include "BaseJuego.h"




class  ControlJuego : public BaseJuego
{
public:

    //Destructor
    ~ControlJuego(void);

    //Singleton
    static ControlJuego& getControlSingleton();

    void inicio(void);
    bool setupMenu(void);


private:

    void cambiaPantalla();

    CEGUI::Window *sheet;

    //Singleton
    void operator=(const ControlJuego& controlJuego ) ;
    ControlJuego(const ControlJuego& control);
    ControlJuego(void);

    //BUCLE PRINCIPAL
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

};

#endif
