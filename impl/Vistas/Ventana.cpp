#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana(ModeloVista* modeloVista) :
    //mLastStatUpdateTime(0),
    modeloVista(modeloVista),
    // mPantalla(0),
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


int Ventana::pantallaActual()
{
    if (vista->esMenuInicio())
    {
        return 0;

    }else return 1;
}

void Ventana::creaVista()
{  
    resetOgre();


    std::cout << "pdespues de reset" << std::endl;

    if (modeloVista->getNumPantalla() == 0)
        vista = new MenuInicio(modeloVista, mRoot);
    else
    {




        if (modeloVista->getNumPantalla() == 1)
        {
            std::cout << "pantalla 1" << std::endl;

            vista= new VistaAjedrez(modeloVista, mRoot);

        }

        else if (modeloVista->getNumPantalla() == 2)
        {
            std::cout << "pantalla 2" << std::endl;

            //EL CONTRUCTOR DE BASEVISTAS CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI
            vista= new VistaAjedrezSolo(modeloVista, mRoot);

        }


        modeloVista->escena->createCamera();
        std::cout << "p331" << std::endl;

        modeloVista->escena->createViewports(vista->mWindow);


        modeloVista->modelo = Modelo::getSingletonPtr();










        std::cout << "escc" << std::endl;


        std::cout << "escc2222: " <<   modeloVista->escena->esModoCamara()<< std::endl;


       // modeloVista->iniciaModeloAjedrez();

        modeloVista->generaJugadores();
        std::cout << "2221" << std::endl;



    }


    std::cout << "init" << std::endl;

    initOgre();


    muestraVentana();
    std::cout << "start" << std::endl;

    mRoot->startRendering();

}

bool Ventana::muestraVentana()
{
    vista->iniciaCEGUI();

    if (modeloVista->getNumPantalla() == 0)
        static_cast<MenuInicio*>(vista)->pantallaInicio();
    else
    {
        modeloVista->escena->createScene();
        modeloVista->creaModeloTablero();
    }
    return true;
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

        vista = NULL;

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




bool Ventana::initOgre(void)
{


    mRoot->addFrameListener(vista);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    //  static_cast<MenuInicio*>(vista)->iniciaVentana();

    vista->mMouse->setEventCallback(vista);
    vista->mKeyboard->setEventCallback(vista);


    // EmpiezaCEGUI();


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






void Ventana::destroyScene(void)
{


    //  if modelo->   modelo->destruyeMenu();
    //MIRA ESTO!!!!!!!!!!!!!!!!
    //  if (modelo->escenaAjedrez != NULL)
    //  {
    mRoot->removeFrameListener(vista);
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
