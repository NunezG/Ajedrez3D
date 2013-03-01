
#include "../headers/MenuInicio.h"

//-------------------------------------------------------------------------------------
MenuInicio::MenuInicio(CEGUIFrameListener* mFrameListener): mFrameListener(mFrameListener)
{

}
//-------------------------------------------------------------------------------------
MenuInicio::~MenuInicio(void)
{

}




void MenuInicio::createGUI()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro ***");

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 2***");

    fWnd = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 3***");


    // position a quarter of the way in from the top-left of parent.


   // fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25f, 0 ), CEGUI::UDim( 0.25f, 0 ) ) );

    // set size to be half the size of the parent
    fWnd->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );


    //Ogre::LogManager::getSingletonPtr()->logMessage(  mFrameListener->sys->);




    mFrameListener->sys->getGUISheet()->addChildWindow( fWnd );

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 5***");

    // mFrameListener. = new CEGUIFrameListener();
    std::cout << "createGUI"<<std::endl;

    //Quit button
    quitButton = wmgr.createWindow("TaharezLook/Button", "CEGUI/QuitButton");
    quitButton->setText("Quit");
    quitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2,0)));
    quitButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    quitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
                               CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this));
    //Boton Jugar por turnos
    mBotonJTurnos = wmgr.createWindow("TaharezLook/Button", "CEGUI/BotonJuegoPorTurnos");
    mBotonJTurnos->setText("Jugar");
    mBotonJTurnos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.6,0)));
    mBotonJTurnos->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    mBotonJTurnos->subscribeEvent(CEGUI::PushButton::EventClicked,
                                  CEGUI::Event::Subscriber(&MenuInicio::botonJuegoTurnos, this));

    //Atsstaching buttons
    fWnd->addChildWindow(quitButton);
    fWnd->addChildWindow(mBotonJTurnos);

  // mFrameListener-> sys->renderGUI();
std::cout << "createGUI 3"<<std::endl;
}





bool MenuInicio::botonSalir(const CEGUI::EventArgs &e)
{

    std::cout << "BOTON QUIT" << std::endl;

     mFrameListener->mShutDown = true;
    return true;
}


bool MenuInicio::botonJuegoTurnos(const CEGUI::EventArgs &e)
{

    std::cout << "BOTON ÇJUEGO TURNOS" << std::endl;
  // mModoJuego = 1;
    mFrameListener->mPantalla = 1;
    // Close the Simple Window
   std::cout << "BOTON ÇJUEGO TURNOS2" << std::endl;
    mFrameListener->sys->getGUISheet()->setVisible(false);
// fWnd->setVisible(false);
      std::cout << "BOTON ÇJUEGO TURNOS3" << std::endl;

 //   CEGUI::System::getSingleton().removeAllEvents();


     //cambiaPantalla();

      //creaTablero();


    return true;
}



