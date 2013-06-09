#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana(ModeloVista* modeloVista) :
    //mLastStatUpdateTime(0),
    modeloVista(modeloVista),
    // mPantalla(0),
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



void Ventana::creaVista()
{  
   // resetOgre();

    std::cout << "pdespues de reset" << std::endl;

    if (modeloVista->getNumPantalla() == 0)
        vista = new MenuInicio(modeloVista);
    else
    {

        if (modeloVista->getNumPantalla() == 1)
        {
            std::cout << "pantalla 1" << std::endl;

            vista= new VistaAjedrez(modeloVista);

        }

        else if (modeloVista->getNumPantalla() == 2)
        {
            std::cout << "pantalla 2" << std::endl;

            //EL CONTRUCTOR DE BASEVISTAS CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI
            vista= new VistaAjedrezSolo(modeloVista);

        }

        modeloVista->escena->createCamera();
        std::cout << "p331" << std::endl;

        modeloVista->escena->createViewports(vista->mWindow);


        modeloVista->modelo = Modelo::getSingletonPtr();


        std::cout << "escc2222: " <<   modeloVista->escena->esModoCamara()<< std::endl;


       // modeloVista->iniciaModeloAjedrez();

        modeloVista->generaJugadores();
        std::cout << "2221" << std::endl;



    }



    muestraVentana();
    std::cout << "start" << std::endl;

    vista->empieza();
}

bool Ventana::muestraVentana()
{
    iniciaListeners();


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




bool Ventana::iniciaListeners()
{

    vista->mRoot->addFrameListener(vista);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    //  static_cast<MenuInicio*>(vista)->iniciaVentana();

    vista->mMouse->setEventCallback(vista);
    vista->mKeyboard->setEventCallback(vista);


    // EmpiezaCEGUI();


}



bool Ventana::destruyeVista(void)
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


}





