
#include "../headers/MenuInicial.h"

//-------------------------------------------------------------------------------------
MenuInicial::MenuInicial(void) :
    CreacionJuego()
{
}
//-------------------------------------------------------------------------------------
MenuInicial::~MenuInicial(void)
{
}





void MenuInicial::createMainMenu(void)
{

    // mSceneMgr->getRootSceneNode()->addChild(nodo1);
    std::cout  << "Gestion del overlay2" << std::endl;

    //   mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
    std::cout  << "Gestion del overla22y" << std::endl;
    // Ogre::Overlay *overlay = mOverlayManager->getByName("Menu");
    std::cout  << "Gestion del overla33" << std::endl;
    // Ogre::OverlayElement* cont = mOverlayManager->getOverlayElement("instrucciones");
    // cont->setCaption("PRUEBA DE OVERLAY");
    //  overlay->show();

    std::cout  << "Gestion del overlay" << std::endl;
    // Gestion del overlay ---------------------------------------------
    //    Ogre::OverlayElement *oe;

    //    mOverlayManager-> hasOverlayElement("JuegoSolitario");
    //  oe = mOverlayManager->getOverlayElement("JuegoSolitario");
    //  oe->setCaption(textoOverlay);


    //    oe = mOverlayManager->getOverlayElement("JuegoTurnos");
    //   oe->setCaption("CAPTIOOON");

    std::cout  << "fin Gestion del overlay" << std::endl;

}


//-------------------------------------------------------------------------------------
bool MenuInicial::setupMenu(void)
{

    // Create the scene

    createMainMenu();

  //  createGUI();




    return true;
}










bool MenuInicial::quit(const CEGUI::EventArgs &e)
{

    std::cout << "BOTON QUIT" << std::endl;

     mShutDown = true;
    return true;
}


bool MenuInicial::juegoPorTurnos(const CEGUI::EventArgs &e)
{

    std::cout << "BOTON ÇJUEGO TURNOS" << std::endl;
   mModoJuego = 1;

    // Close the Simple Window
   std::cout << "BOTON ÇJUEGO TURNOS2" << std::endl;

      fWnd->setVisible(false);
      std::cout << "BOTON ÇJUEGO TURNOS3" << std::endl;

 //   CEGUI::System::getSingleton().removeAllEvents();


    //TutorialApplication ta;
      TutorialApplication* tut= new TutorialApplication(mSceneMgr);

      std::cout << "tutti" << std::endl;




      //  createViewports();

        // Create the scene
      //   createScene();


      tut->setupJuego();

      //creaTablero();


    return true;
}

void MenuInicial::createGUI()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro ***");

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 2***");

    fWnd = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 3***");


    // position a quarter of the way in from the top-left of parent.


    fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25f, 0 ), CEGUI::UDim( 0.25f, 0 ) ) );

    // set size to be half the size of the parent
    fWnd->setSize( CEGUI::UVector2( CEGUI::UDim( 0.5f, 0 ), CEGUI::UDim( 0.5f, 0 ) ) );


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
                               CEGUI::Event::Subscriber(&MenuInicial::quit, this));
    //Boton Jugar por turnos
    mBotonJTurnos = wmgr.createWindow("TaharezLook/Button", "CEGUI/BotonJuegoPorTurnos");
    mBotonJTurnos->setText("Jugar");
    mBotonJTurnos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.6,0)));
    mBotonJTurnos->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    mBotonJTurnos->subscribeEvent(CEGUI::PushButton::EventClicked,
                               CEGUI::Event::Subscriber(&MenuInicial::juegoPorTurnos, this));

    //Atsstaching buttons
    fWnd->addChildWindow(quitButton);
    fWnd->addChildWindow(mBotonJTurnos);

   mFrameListener-> sys->renderGUI();
std::cout << "createGUI 3"<<std::endl;
}




