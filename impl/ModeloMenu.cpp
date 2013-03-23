#include "../headers/ModeloMenu.h"



ModeloMenu::ModeloMenu() : posBoton(0)

{



}

ModeloMenu::~ModeloMenu()
{


}


void ModeloMenu::creaBoton(CEGUI::Event::Subscriber evento, Ogre::String nombre)
{

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CRcfbhfbxbet***");


    CEGUI::Window* quitButton;

   CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    quitButton = wmgr.createWindow("TaharezLook/Button", nombre);
   quitButton->setText(nombre);
    quitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2*posBoton,0)));

    quitButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
   quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, evento);

   Ogre::LogManager::getSingletonPtr()->logMessage("*** casi final***");

  //  botones[posBoton] = quitButton;

    posBoton++;

   //Atsstaching buttons
   ventana->addChildWindow(quitButton);
   Ogre::LogManager::getSingletonPtr()->logMessage("***  final***");

   // CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this)
}




void ModeloMenu::creaVentana()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREdddddddddddddddddddAftghet***");


   CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


   Ogre::LogManager::getSingletonPtr()->logMessage("*** CREAftghet***");

  ventana = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

  Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUcvcfdfI dentro 5***");


    // fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25f, 0 ), CEGUI::UDim( 0.25f, 0 ) ) );

    ventana->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

    CEGUI::System* sys = CEGUI::System::getSingletonPtr();

    sys->getGUISheet()->addChildWindow( ventana );


}





ModeloMenu* ModeloMenu::getSingletonPtr()
{
    static ModeloMenu miModelo;
    static ModeloMenu* miModeloPtr = &miModelo;
    return miModeloPtr;
}
