#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana() :
    //mLastStatUpdateTime(0),

    mPantalla(0),
    sys(0),
   // mRoot(Ogre::Root::getSingletonPtr()),
    //mTimer(mRoot->getTimer()),
    //  mSceneMgr(0),
    vista(NULL)
    //capturaRaton(true)
{
    modelo = Modelo::getSingletonPtr();

}

Ventana::~Ventana()
{

    std::cout << "framelis"<< std::endl;

    delete vista;
    std::cout << "fin"<< std::endl;
    vista = NULL;
    std::cout << "remove"<< std::endl;





    std::cout << "end"<< std::endl;

}


bool areFrameStatsVisible()
{
    return true;//mFpsLabel != 0;
}

//-------------------------------------------------------------------------------------
void Ventana::iniciaIO(void)
{


}



bool Ventana::EmpiezaCEGUI()
{


    Ogre::LogManager::getSingletonPtr()->logMessage("*** EMPIEZA***");


    // Bootstrap CEGUI::System with an OgreRenderer object that uses the
    // default Ogre rendering window as the default output surface, an Ogre based
    // ResourceProvider, and an Ogre based ImageCodec.
    CEGUI::OgreRenderer& myRenderer  = CEGUI::OgreRenderer::bootstrapSystem(*vista->mWindow);

}


bool Ventana::CEGUIResources()
{   


    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** schemes***");

    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** imageset***");

    CEGUI::Font::setDefaultResourceGroup("Fonts");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** fonts***");

    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** layout***");

    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** look***");

    if (!CEGUI::SchemeManager::getSingleton().isDefined("VanillaSkin")) Ogre::LogManager::getSingletonPtr()->logMessage("*** VANILLA NO  EXISTE antes***");
    if (!CEGUI::SchemeManager::getSingleton().isDefined("TaharezLook")) Ogre::LogManager::getSingletonPtr()->logMessage("*** taha NO EXISTE antes***");

    // CEGUI::SchemeManager::getSingleton().loadScheme( (CEGUI::utf8*)"TaharezLook.scheme");
    CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** vanilla***");



       // CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");

    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** sys***");


    if (CEGUI::SchemeManager::getSingleton().isDefined("VanillaSkin")) Ogre::LogManager::getSingletonPtr()->logMessage("*** VANILLA EXISTE despues***");
    if (CEGUI::SchemeManager::getSingleton().isDefined("TaharezLook")) Ogre::LogManager::getSingletonPtr()->logMessage("*** taha  EXISTE despues***");

    sys = CEGUI::System::getSingletonPtr();

    CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");


   // sys->setDefaultFont("DejaVuSans-10");

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CARGA RATON 1***");

    sys->setDefaultMouseCursor("Vanilla-Images", "MouseArrow");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** CARGA RATON 2***");


    CEGUI::MouseCursor::getSingleton().setImage(sys->getDefaultMouseCursor());

    Ogre::LogManager::getSingletonPtr()->logMessage("*** ACABA CARGA RATON ***");

   CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet= wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    sys->setGUISheet(sheet);

   sys->renderGUI();
    Ogre::LogManager::getSingletonPtr()->logMessage("*** ACABA GUI***");



    return true;
}

bool Ventana::injectTimePulse(const Ogre::FrameEvent& evt)
{   
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    sys->injectTimePulse(evt.timeSinceLastFrame);
}

int Ventana::pantallaActual(){
    if (vista->esMenuInicio()){

        return 0;

    }else return 1;

}


bool Ventana::iniciaMenu()
{

    //Ogre::Root::getSingletonPtr()->addFrameListener(this);



    Ogre::LogManager::getSingletonPtr()->logMessage("***INICIAMENU***");



  //VistaAjedrez* miVista = static_cast<VistaAjedrez*>(vista);




}


bool Ventana::MuestraMenu()
{

  static_cast<MenuInicio*>(vista)->iniciaVentana();

 // vista->iniciaVentana();


  vista->mMouse->setEventCallback(this);
  vista->mKeyboard->setEventCallback(this);


  //Register as a Window listener
  Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);

  Ogre::LogManager::getSingletonPtr()->logMessage("***FIN  Initializing OISpuntero ***");




}

bool Ventana::ventanaCerrada()
{

    VistaAjedrez* miVista = static_cast<VistaAjedrez*>(vista);
    if (miVista->mWindow->isClosed() || !miVista->mWindow->isVisible())
    {
    //CIERRA LA VENTANA


        delete vista;
        vista = NULL;

        return true;
    }

    return false;
}

bool Ventana::keyPressed(const OIS::KeyEvent& evt)
{   
    if(mPantalla > 0){
        vista->keyPressed(evt);
    }

    sys->injectKeyDown(evt.key);
    sys->injectChar(evt.text);

    if (evt.key == OIS::KC_ESCAPE)// Pulsa Esc
    {
        modelo->setSalir(true);
    }else if (evt.key == OIS::KC_SYSRQ)   // take a screenshot
    {
       // mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }

    return true;
}

bool Ventana::keyReleased(const OIS::KeyEvent& evt)
{
    if(mPantalla > 0){
        vista->keyReleased(evt);
    }

    sys->injectKeyUp(evt.key);

    return true;
}

bool Ventana::mouseMoved( const OIS::MouseEvent &evt )
{   


    sys->injectMouseMove(evt.state.X.rel, evt.state.Y.rel);



    //  if(mPantalla > 0)
    //   {


   if (vista != NULL) vista->mouseMoved(evt);



    // Scroll wheel.
    //if (evt.state.Z.rel)
    //    sys->injectMouseWheelChange(evt.state.Z.rel / 120.0f);
    //  }



    return true;
}

//-------------------------------------------------------------------------------------
bool Ventana::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    injectTimePulse(evt);


    //  if (capturaRaton){
    //    }
   // statUpdate(evt);


  //  if (modelo->getTablero()->jugadores[modelo->getTablero()->getTurnoNegras()]->esHumano())
 //   {



    if(!(modelo->jugadores.size()>0 && !modelo->jugadores.at(modelo->escenaAjedrez->getTablero()->getTurnoNegras())->esHumano()))
    {


            vista->capture();



        if(vista != NULL && !vista->esMenuInicio())
        {

            vista->mueveCamara(evt.timeSinceLastFrame);
        }


    }

   // }
}


//BaseApplication* Ventana::Create(Ogre::String type) {
//  if ( type == "JuegoPorTurnos" ) return  VistaAjedrez(mSceneMgr, mWindow);
//   if ( type == "JuegoEnSolitario" ) return  VistaAjedrezSolo(mSceneMgr, mWindow);
//  return NULL;
//}

void Ventana::destruyeVista(){

    Ogre::WindowEventUtilities::removeWindowEventListener(vista->mWindow, this);


    std::cout << "destroy 3"<< std::endl;

    vista->windowClosed();


    delete vista;



    std::cout << "detach"<< std::endl;

   // mRoot->detachRenderTarget(vista->mWindow);

  //  std::cout << "destroy"<< std::endl;


    //mRoot->destroyRenderTarget(vista->mWindow);


  //  std::cout << "vista"<< std::endl;

    //vista->windowClosed();


  //  std::cout << "destroy"<< std::endl;

  //  CEGUI::SchemeManager::getSingleton().destroyAll();

  //  std::cout << "destroy 2"<< std::endl;

  // CEGUI::OgreRenderer::destroySystem();

    //OIS::InputManager::destroyInputSystem(vista->mInputManager);




    std::cout << "pasa"<< std::endl;


}



void Ventana::creaVista()
{


    if (modelo->getNumPantalla() == 1)
    {
        mPantalla = 1;
        vista= new VistaAjedrez();

    }
    else if (modelo->getNumPantalla() == 2)
    {
        mPantalla = 2;
        vista= new VistaAjedrezSolo();

    }



}

VistaAjedrez* Ventana::muestraAjedrez(/*EscenaAjedrez escenaAjedrez*/)
{

    //sys->getGUISheet()->setVisible(false);
   // CEGUI::Window* win = sys->getGUISheet();

       //win->cleanupChildren();



    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


    static_cast<VistaAjedrez*>(vista)->iniciaVentana();



    Ogre::LogManager::getSingletonPtr()->logMessage("***sigue*");

    vista->mMouse->setEventCallback(this);
    Ogre::LogManager::getSingletonPtr()->logMessage("***si**");

    vista->mKeyboard->setEventCallback(this);
    Ogre::LogManager::getSingletonPtr()->logMessage("***sisi**");


    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);


    Ogre::LogManager::getSingletonPtr()->logMessage("***muestrainfo**");



  //  static_cast<VistaAjedrez*>(vista)->muestraInfo();

    Ogre::LogManager::getSingletonPtr()->logMessage("***fin**");

  //  CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("InfoAjedrezCEED.layout");
  //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );


    //CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);



    return static_cast<VistaAjedrez*>(vista);
}

bool Ventana::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
sys->injectMouseButtonDown(convertButton(id));




    if(vista->mousePressed(evt, id))
    {
        return true;
    }

   // return true;
}

bool Ventana::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    sys->injectMouseButtonUp(convertButton(id));


    vista->mouseReleased(evt, id);

    // else if(mPantalla == 0)
    //  {

    //  if (sys->getGUISheet()->isVisible()==true && modelo->getNumPantalla() == 1)
    //   {
    //      std::cout << "PANTALLA 1 " << std::endl;


    //    }
    //    else if (sys->getGUISheet()->isVisible()==true && modelo->getNumPantalla() == 2)
    //   {
    //        std::cout << "PANTALLA 2 " << std::endl;

    //  sys->getGUISheet()->setVisible(false);
    //    }
    //}
    return true;
}

CEGUI::MouseButton Ventana::convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}
