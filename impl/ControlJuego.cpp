
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
    if(punteroVentana->pantallaActual() == 0)
    {
         std::cout << "PANTALLA ACTUAL ES 0" << std::endl;

        if(punteroVentana->mPantalla > 0){
            std::cout << "CAMBIA DE PANTALLA " << std::endl;

            punteroVentana->muestraAjedrez();
            std::cout << "FIN CAMBIO" << std::endl;

        }
    }

    if(punteroVentana->getVentana()->isClosed())
        return false;

    if(!punteroVentana->getVentana()->isVisible())
        return false;

    if(punteroVentana->mShutDown)
        return false;

    std::cout << "frameRenderingQueued de ventana" << std::endl;


    punteroVentana->frameRenderingQueued(evt);

    std::cout << "frameRenderingQueued de 2222222" << std::endl;

    if(punteroVentana->mPantalla == 2)
    {
        std::cout << "punteroVentana->mPantalla = 2" << std::endl;

        if (punteroVentana->vista->turnoNegras && esperaCalculo == false)
        {
            calculaMovimiento();
            esperaCalculo==true;
        }

}


    return true;
}


void ControlJuego::calculaMovimiento(){
    //INICIA LA IA PARA CALCULAR LA FICHA A MOVER









}
