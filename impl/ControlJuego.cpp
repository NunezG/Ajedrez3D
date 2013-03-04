
#include "../headers/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego()

{
    std::cout << "constructor control juego"<< std::endl;


}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{
    std::cout << "destructor control juego"<< std::endl;

}

void ControlJuego::inicio(void){


    //mFrameListener = Ventana::getCEGUISingleton();
    std::cout << "addFrameListener"<< std::endl;

    Ogre::Root::getSingletonPtr()->addFrameListener(this);
    std::cout << "iniciaIO"<< std::endl;



    Ventana& mFrameListener = Ventana::getCEGUISingleton();

    mFrameListener.EmpiezaCEGUI();





    mFrameListener.MuestraMenu();

    std::cout << "acaba MuestraMenu"<< std::endl;



}


ControlJuego& ControlJuego::getControlSingleton()
{
    static ControlJuego miControlJuego_;
    return miControlJuego_;
}




//-------------------------------------------------------------------------------------
bool ControlJuego::setupMenu(void)
{

    // Create the scene

    //  createMainMenu();

    //  createGUI();




    return true;
}


void ControlJuego::cambiaPantalla(){


    Ventana& mFrameListener = Ventana::getCEGUISingleton();


    mFrameListener.muestraAjedrez();


}



//-------------------------------------------------------------------------------------
bool ControlJuego::frameRenderingQueued(const Ogre::FrameEvent& evt)
{


    //   std::cout << "frameRenderingQueued " << std::endl;


    //mFrameListener = Ventana::getCEGUISingleton();


    Ventana& mFrameListener = Ventana::getCEGUISingleton();



    //Need to capture/update each device

    //   std::cout << "mFrameListener33333333333333 " << std::endl;



    if(mFrameListener.mPantalla == 1){
        std::cout << "PANTALLA 1" << std::endl;
        if(mFrameListener.pantallaActual()==0){

            std::cout << "CAMBIA DE PANTALLA!!!!!!!!!!!" << std::endl;

            std::cout << "CAMBIA DE PANTALLA!!!!!!!!!!!" << std::endl;

            cambiaPantalla();

        }


    }


    if(mFrameListener.getVentana()->isClosed()){

        std::cout << "VENTANA CERRADA!!!!!!!!!!!" << std::endl;

        return false;

    }


    if(!mFrameListener.getVentana()->isVisible()){
        std::cout << "BOTON CERRAR PULSADO EN CERRADA!!!!!!!!!!!" << std::endl;
        return false;
    }

    if(mFrameListener.mShutDown){
        std::cout << "BOTON CERRAR PULSADO A TRAVES DE mShutDown!!!!!!!!!!!" << std::endl;
        return false;
    }


    mFrameListener.frameRenderingQueued(evt);



    return true;




}








