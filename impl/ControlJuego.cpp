
#include "../headers/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego()
{
}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{
}

void ControlJuego::inicio(void){

    Ogre::Root::getSingletonPtr()->addFrameListener(this);

    punteroVentana->EmpiezaCEGUI();
    punteroVentana->MuestraMenu();

}

ControlJuego& ControlJuego::getControlSingleton()
{
    static ControlJuego miControlJuego_;
    return miControlJuego_;
}

//-------------------------------------------------------------------------------------
bool ControlJuego::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(punteroVentana->mPantalla == 1){
        if(punteroVentana->pantallaActual()==0){
            punteroVentana->muestraAjedrez();
        }
    }

    if(punteroVentana->getVentana()->isClosed()){
        return false;
    }

    if(!punteroVentana->getVentana()->isVisible()){
        return false;
    }

    if(punteroVentana->mShutDown){
        return false;
    }

    punteroVentana->frameRenderingQueued(evt);

    return true;
}
