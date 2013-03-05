
#include "../headers/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego(),
    esperaCalculo(false)
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
    if(punteroVentana->pantallaActual()== 0)
    {
        if(punteroVentana->mPantalla == 1)
            punteroVentana->muestraAjedrez();
        else if (punteroVentana->mPantalla == 2)
            punteroVentana->muestraAjedrezSolo();
    }

    if(punteroVentana->getVentana()->isClosed())
        return false;

    if(!punteroVentana->getVentana()->isVisible())
        return false;

    if(punteroVentana->mShutDown)
        return false;

    punteroVentana->frameRenderingQueued(evt);


    if(punteroVentana->mPantalla == 2)
        if (punteroVentana->tut->turnoNegras && esperaCalculo == false)
        {
            calculaMovimiento();
            esperaCalculo==true;
        }




    return true;
}


void ControlJuego::calculaMovimiento(){
    //INICIA LA IA PARA CALCULAR LA FICHA A MOVER






}
