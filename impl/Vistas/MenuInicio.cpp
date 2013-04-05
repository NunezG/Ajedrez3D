
#include "../../headers/Vistas/MenuInicio.h"

//-------------------------------------------------------------------------------------
MenuInicio::MenuInicio() : salirPulsado(0)
{
    iniciaVista();
}
//-------------------------------------------------------------------------------------
MenuInicio::~MenuInicio(void)
{

}

bool MenuInicio::iniciaVista()
{
   // Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro ***");

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

   // Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 2***");

   // fWnd = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

   // Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 3***");

    // fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25f, 0 ), CEGUI::UDim( 0.25f, 0 ) ) );

    //fWnd->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

    Ogre::LogManager::getSingletonPtr()->logMessage( "*** CREATE GUI dentro 3***");


    modelo->menu->creaVentana();

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 5***");


    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this), "Salir");


    Ogre::LogManager::getSingletonPtr()->logMessage("***sigue**");
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoTurnos, this),"Jugar por turnos");
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoSolo, this), "Jugar contra su puta madre");

/*
    //Boton Jugar por turnos
    mBotonJTurnos = wmgr.createWindow("TaharezLook/Button", "CEGUI/BotonJuegoPorTurnos");
    mBotonJTurnos->setText("Jugar por turnos");
    mBotonJTurnos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.4,0)));
    mBotonJTurnos->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    mBotonJTurnos->subscribeEvent(CEGUI::PushButton::EventClicked,
                                  );
*/

    /*
    //Boton Jugar contra la máquina
    mBotonJSolo = wmgr.createWindow("TaharezLook/Button", "CEGUI/BotonJuegoContraIA");
    mBotonJSolo->setText("Jugar solo");
    mBotonJSolo->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.5,0)));
    mBotonJSolo->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    mBotonJSolo->subscribeEvent(CEGUI::PushButton::EventClicked,
                              );

    */

    Ogre::LogManager::getSingletonPtr()->logMessage("***añade**");

    //Atsstaching buttons
   // fWnd->addChildWindow(quitButton);
   // fWnd->addChildWindow(mBotonJTurnos);
   // fWnd->addChildWindow(mBotonJSolo);

  //  CEGUI::System* sys = CEGUI::System::getSingletonPtr();

    //sys->getGUISheet()->addChildWindow( fWnd );
    Ogre::LogManager::getSingletonPtr()->logMessage("***acacacaba**");

    return true;
}

bool MenuInicio::salir(){
    return salirPulsado;
}

bool MenuInicio::esMenuInicio(){

    return true;
}


bool MenuInicio::keyPressed( const OIS::KeyEvent &arg ) {

}

bool MenuInicio::keyReleased( const OIS::KeyEvent &arg ){

}

bool MenuInicio::mouseMoved( const OIS::MouseEvent &arg ){

}

bool MenuInicio::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){

}

bool MenuInicio::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){

}

bool MenuInicio::frameRenderingQueued(const Ogre::FrameEvent& evt){

}



bool MenuInicio::botonSalir(const CEGUI::EventArgs &e)
{
    salirPulsado = true;
    return true;
}

bool MenuInicio::botonJuegoTurnos(const CEGUI::EventArgs &e)
{

    //modelo->modoJuego = 1;
    modoJuego = 1;
    return true;
}

bool MenuInicio::botonJuegoSolo(const CEGUI::EventArgs &e)
{
    modoJuego = 2;
    return true;
}