#include "../../headers/Control/BaseJuego.h"

//-------------------------------------------------------------------------------------
BaseJuego::BaseJuego(void): punteroVentana(NULL)

  //mPluginsCfg("plugins.cfg"),
  // mResourcesCfg("resources.cfg")
{

    //   modelo = Modelo::getSingletonPtr();
}
//-------------------------------------------------------------------------------------
BaseJuego::~BaseJuego(void)
{
    // delete mRoot;
}

///////////////////////////////////////////////////////////////////////////////////////7

//-------------------------------------------------------------------------------------
bool BaseJuego::configureOpenGL()
{
    //if(configuraGraficos("OpenGL"))
    //{
    //punteroVentana->iniciaVentana();

    //  return true;
    //}

    return false;

}

void BaseJuego::inicio(void){

    modelo->construyeMenu();







    punteroVentana->MuestraMenu();






    //punteroVentana->iniciaVista();
    // iniciaModeloAjedrez();


}

bool BaseJuego::initOgre(void){


    if (punteroVentana->vista == NULL)
    {
        punteroVentana->vista = new MenuInicio();
        punteroVentana->vista->mWindow = mRoot->initialise(true, "Root Prueba");

    }
    std::cout   << "   5 " << std::endl;


    Ogre::Root::getSingletonPtr()->addFrameListener(this);


    std::cout   << "   6 " << std::endl;

    punteroVentana->EmpiezaCEGUI();
    punteroVentana->CEGUIResources();
    std::cout   << "   7 " << std::endl;


    loadResources();

    std::cout   << "   8 " << std::endl;


}



bool BaseJuego::resetOgre(void)
{


    // punteroVentana->destruyeMenu();

      if(punteroVentana->vista){
          CEGUI::OgreRenderer::destroySystem();
          punteroVentana->destruyeVista();
      }



    std::cout   << "   reset1 " << std::endl;

    //APAGA
    if (mRoot )delete mRoot;
    mRoot = NULL;


    std::cout   << "   reset2 " << std::endl;

    //ENCIENDE
    mRoot =new Ogre::Root("plugins.cfg");
    // mTimer = mRoot->getTimer();


    std::cout   << "   reset3 " << std::endl;






}



bool BaseJuego::start(void)
{

    mRoot->startRendering();

}


//-------------------------------------------------------------------------------------
bool BaseJuego::configureOgre(void)
{
    // setupResources();

    //   bool carryOn = configureOpenGL();
    //  if (!carryOn) return false;



    // punteroVentana->iniciaIO();

    return true;
}

//-------------------------------------------------------------------------------------
bool BaseJuego::setup(void)
{
    return true;
}

void BaseJuego::destroyScene(void)
{



    //  if modelo->   modelo->destruyeMenu();



    if (modelo->escenaAjedrez->getTablero()){


        modelo->escenaAjedrez->destruyeTablero();



        //MIRA A VER
        mRoot->destroySceneManager(mSceneMgr);

    }

    if (mRoot)
        mRoot->removeFrameListener(this);

    delete mRoot;

    modelo = NULL;


    //delete mRoot;

    // mTimer = NULL;


    mRoot = NULL;

    delete punteroVentana;

    punteroVentana = NULL;


}

//-----------------------------------------------------------------------
//CONFIGURACION PREVIA A LA INICIALIZACION DE GRAFICOS
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
void BaseJuego::setupResources(void)
{

}

//-------------------------------------------------------------------------------------
void BaseJuego::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

//-------------------------------------------------------------------------------------
void BaseJuego::go(void)
{
    std::cout   << "   mod " << std::endl;

    modelo = Modelo::getSingletonPtr();
    std::cout   << "   vent " << std::endl;

    punteroVentana = new Ventana();

    //if (!configureOgre())
    //      return;
    std::cout   << "   reset " << std::endl;

    resetOgre();
    std::cout   << "   init " << std::endl;

    initOgre();

    inicio();
    std::cout   << "   start " << std::endl;

    
    start();


    // clean up (despues de ejeucion)
    destroyScene();
}
