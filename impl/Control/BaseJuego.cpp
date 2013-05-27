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
    sleep(0.5);

    modeloVista = new ModeloVista(modelo);
    sleep(0.5);

    punteroVentana = new Ventana(modeloVista);
    sleep(0.5);

    //if (!configureOgre())
    //      return;

    punteroVentana->resetOgre();
    sleep(0.5);

    punteroVentana->vista = new MenuInicio(modeloVista, punteroVentana->mRoot);


    punteroVentana->CEGUIResources();
    sleep(0.5);

    punteroVentana->MuestraMenu();
    sleep(0.5);


    punteroVentana->initOgre();
    sleep(0.5);



    //UN BUCLE WHILE QUE MIRE UNA VARIABLE (EN ESCENAAJEDREZ?) PARA RESETEAR LA VENTANA Y QUE MODELOVISTA NO CAMBIE???

        while(!modeloVista->getApagar())
        {
           // std::cout << "incia ffff" << std::endl;

            sleep(0.5);
            punteroVentana->start();
           // std::cout << "acaba ffff" << std::endl;
        }

    std::cout << "acaba del todo" << std::endl;

    // clean up (despues de ejeucion)
    punteroVentana->destroyScene();
}
