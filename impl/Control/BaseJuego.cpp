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

  //  modelo->construyeMenu();







    punteroVentana->MuestraMenu();






    //punteroVentana->iniciaVista();
    // iniciaModeloAjedrez();


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


//-----------------------------------------------------------------------
//CONFIGURACION PREVIA A LA INICIALIZACION DE GRAFICOS
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
void BaseJuego::setupResources(void)
{

}


//-------------------------------------------------------------------------------------
void BaseJuego::go(void)
{

    modelo = Modelo::getSingletonPtr();

    punteroVentana = new Ventana();

    //if (!configureOgre())
    //      return;

    punteroVentana->resetOgre();

    punteroVentana->initOgre();

    UN BUCLE WHILE QUE MIRE UNA VARIABLE (EN ESCENAAJEDREZ?) PARA RESETEAR LA VENTANA Y QUE MODELOVISTA NO CAMBIE??? CREA UNA BASE PARA ESCENAAJEDREZ Y MENUINICIAL???


    inicio();

    
    punteroVentana->start();


    // clean up (despues de ejeucion)
    punteroVentana->destroyScene();
}
