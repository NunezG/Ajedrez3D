#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana(ModeloVista* modeloVista) :
    //mLastStatUpdateTime(0),
    modeloVista(modeloVista),
    // mPantalla(0),
    sys(0),
    mRoot(NULL),
    //mTimer(mRoot->getTimer()),
    //  mSceneMgr(0),
    vista(NULL)
  //shutdown(0)
  //capturaRaton(true)
{
    //  modeloVista = Modelo::getSingletonPtr();

}

Ventana::~Ventana()
{

    //   std::cout << "framelis"<< std::endl;

    //delete vista;
    // std::cout << "fin"<< std::endl;
    //vista = NULL;
    // std::cout << "remove"<< std::endl;


    destruyeVista();


    std::cout << "end"<< std::endl;

}


bool areFrameStatsVisible()
{
    return true;//mFpsLabel != 0;
}

//-------------------------------------------------------------------------------------



bool Ventana::CEGUIResources()
{   
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

    CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

    sys = CEGUI::System::getSingletonPtr();

    CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");

    sys->setDefaultMouseCursor("Vanilla-Images", "MouseArrow");

    CEGUI::MouseCursor::getSingleton().setImage(sys->getDefaultMouseCursor());

    Ogre::LogManager::getSingletonPtr()->logMessage("*** ACABA GUI***");

    return true;
}

int Ventana::pantallaActual()
{
    if (vista->esMenuInicio())
    {
        return 0;

    }else return 1;
}

void Ventana::creaVista()
{  
    if (modeloVista->getNumPantalla() == 0)
        vista = new MenuInicio(modeloVista, mRoot);

    else  if (modeloVista->getNumPantalla() == 1)
    {

        modeloVista->iniciaModeloAjedrez();
        vista= new VistaAjedrez(modeloVista, mRoot);

        modeloVista->preparaEscena();

        modeloVista->escena->createViewports(vista->mWindow);

    }

    else if (modeloVista->getNumPantalla() == 2) {
        modeloVista->iniciaModeloAjedrez();
        vista= new VistaAjedrezSolo(modeloVista, mRoot);

        modeloVista->preparaEscena();

        modeloVista->escena->createViewports(vista->mWindow);

    }

}

bool Ventana::muestraVentana()
{
    if (modeloVista->getNumPantalla() == 0)
        static_cast<MenuInicio*>(vista)->pantallaInicio();
    else modeloVista->escena->createScene();

    return true;
}



bool Ventana::ventanaCerrada()
{

    //  VistaAjedrez* miVista = static_cast<VistaAjedrez*>(vista);
    if (vista->mWindow->isClosed() || !vista->mWindow->isVisible())
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

    if(!vista->esMenuInicio())
    {
        vista->keyPressed(evt);
    }

    sys->injectKeyDown(evt.key);
    sys->injectChar(evt.text);

    if (evt.key == OIS::KC_ESCAPE)// Pulsa Esc
    {
        modeloVista->setSalir(true);
        vista->mWindow->setVisible(false);
        modeloVista->setApagar(true);
    }
    else if (evt.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        // mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }

    return true;
}

bool Ventana::keyReleased(const OIS::KeyEvent& evt)
{

    if(!vista->esMenuInicio()){
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
    if(ventanaCerrada() /*|| EscenaAjedrez->getSalir()*/)
    {
        //std::cout << "VENTANA CERRADA"<< std::endl;
        // shutdown = true;
        return false;
    }

    sys->injectTimePulse(evt.timeSinceLastFrame);

    //  if (capturaRaton){
    //    }
    // statUpdate(evt);


    //  if (modelo->getTablero()->jugadores[modelo->getTablero()->getTurnoNegras()]->esHumano())
    //   {

    // std::cout << "f4"<< std::endl;

    if (vista != NULL)
    {
        //   std::cout << "f4bis"<< std::endl;

        vista->capture();
        //  std::cout << "f4bis2"<< std::endl;

        if(modeloVista->getNumPantalla() > 0)
        {
            vista->mueveCamara(evt.timeSinceLastFrame);
        }
        //  std::cout << "f4bis3"<< std::endl;

      //  vista->actualizaGUI();


     //   if(pantallaActual() > 0)
     //   {
          //  std::cout << "ESPERA" <<std::endl;

         //   modeloVista->escena->miraCambios();


            //  if (modelo->getTablero()->getNodoCasillaSobrevolada() != NULL && modelo->getTablero()->getNodoCasillaSobrevolada()->seleccionada)
            //  {
            //  std::cout << "ILUMINA UNA CASILLA" <<std::endl;

            // static_cast<VistaAjedrez*>(punteroVentana->vista)->escenaAjedrez->iluminaCasilla(modelo->getTablero()->getNodoCasillaSobrevolada());
            //  static_cast<JugadorHumano*>(modelo->jugadores.at(modelo->getTablero()->getTurnoNegras()))->sobreVuelaCasilla();
            // }
      //  }
    }
    //  std::cout << "f4bis3"<< std::endl;
    //  if( pantallaActual() == 0)
    //  {
    //  }
    //
    // else if(modelo->getNumPantalla() == 2)
    //{
    //   if (modelo->getTablero()->getTurnoNegras())
    //  {
    //         punteroVentana->capturaRaton = false;

    //            calculaMovimiento();
    //  esperaCalculo=true;
    //   }//else punteroVentana->capturaRaton = true;
    //}


    //  if (modelo->getTablero()->getTurnoNegras())
    // {



    //  }


    //  std::cout << "f3"<< std::endl;

    //Ogre::LogManager::getSingletonPtr()->logMessage("*SI QUITO ESTO NO VA");
    //std::cout << "SI QUITO ESTO NO VA"<< std::endl;

    return true;
    // }
}

//BaseApplication* Ventana::Create(Ogre::String type) {
//  if ( type == "JuegoPorTurnos" ) return  VistaAjedrez(mSceneMgr, mWindow);
//   if ( type == "JuegoEnSolitario" ) return  VistaAjedrezSolo(mSceneMgr, mWindow);
//  return NULL;
//}

void Ventana::destruyeVista()
{
    if (vista)
    {


        Ogre::WindowEventUtilities::removeWindowEventListener(vista->mWindow, this);


        std::cout << "destroy 3"<< std::endl;

        vista->windowClosed();


        delete vista;

        vista = 0;

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

    }


    //  std::cout << "pasa"<< std::endl;


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


//-------------------------------------------------------------------------------------
void Ventana::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool Ventana::initOgre(void)
{


    mRoot->addFrameListener(this);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    //  static_cast<MenuInicio*>(vista)->iniciaVentana();

    vista->mMouse->setEventCallback(this);
    vista->mKeyboard->setEventCallback(this);


    // EmpiezaCEGUI();


    loadResources();



}



bool Ventana::resetOgre(void)
{


    // punteroVentana->destruyeMenu();

    destruyeVista();


    // std::cout   << "   reset1 " << std::endl;

    //APAGA
    if (mRoot ){

        delete mRoot;
        mRoot = NULL;
    }

    //  std::cout   << "   reset2 " << std::endl;

    //ENCIENDE
    mRoot =new Ogre::Root("plugins.cfg");
    // mTimer = mRoot->getTimer();


    //  std::cout   << "   reset3 " << std::endl;

}



bool Ventana::start(void)
{
    mRoot->startRendering();
}


void Ventana::destroyScene(void)
{


    //  if modelo->   modelo->destruyeMenu();
    //MIRA ESTO!!!!!!!!!!!!!!!!
    //  if (modelo->escenaAjedrez != NULL)
    //  {
    mRoot->removeFrameListener(this);
    //mRoot->destroySceneManager(modelo->escenaAjedrez->mSceneMgr);
    //  modelo->escenaAjedrez->destruyeTablero();



    //MIRA A VER
    //  mRoot->destroySceneManager(mSceneMgr);
    delete mRoot;

    //  }


    //  delete punteroVentana;

    //  if (mRoot)



    //  modelo = NULL;


    //delete mRoot;

    // mTimer = NULL;


    mRoot = NULL;

    //

    //    punteroVentana = NULL;


}
