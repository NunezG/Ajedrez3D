
#include "../../headers/Control/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego()
    //esperaCalculo(false)

{
}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{
}

ControlJuego& ControlJuego::getControlSingleton()
{
    static ControlJuego miControlJuego_;
    return miControlJuego_;
}

//-------------------------------------------------------------------------------------
bool ControlJuego::frameRenderingQueued(const Ogre::FrameEvent& evt)
{


    if(punteroVentana -> pantallaActual() == 0)
    {
        if(modelo->getNumPantalla() > 0)
        {
            std::cout << "CAMBIA DE PANTALLA " << std::endl;
            modelo->destruyeMenu();

            punteroVentana->muestraAjedrez();
            std::cout << "FIN CAMBIO" << std::endl;
            iniciaModeloAjedrez();
        }
    }


   else if(modelo->getNumPantalla() > 0)
    {

        modelo->mueveFicha(evt.timeSinceLastFrame);

     //  if (modelo->getTablero()->getTurnoNegras())
    //    {
     //       punteroVentana->capturaRaton = false;



                  //  calculaMovimiento();
            //  esperaCalculo=true;
     //   }else punteroVentana->capturaRaton = true;
  }




    if(punteroVentana -> getVentana()->isClosed())
        return false;

    if(!punteroVentana -> getVentana()->isVisible())
        return false;

    if(modelo->getSalir())
        return false;

    punteroVentana->frameRenderingQueued(evt);

    //jugador.mueveFicha();

    return true;
}

//------------------------------------------------------------------------------------
bool ControlJuego::iniciaModeloAjedrez(void)
{
    // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());


    modelo->construyeAjedrez();


    escenaAjedrez = EscenaAjedrez::getSingletonPtr();

    std::cout << "INICIA VISTA 1 " << std::endl;



    modelo->creaJugador(true, true);


    if (modelo->getNumPantalla() == 1){

         modelo->creaJugador(false, true);

    }else{
         modelo->creaJugador(false, false);

    }




    //escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    std::cout << "INICIA VISTA 2 " << std::endl;

    escenaAjedrez->setSceneManager(mSceneMgr);

    escenaAjedrez->createRayQuery();
    std::cout << "INICIA VISTA 3 " << std::endl;

    escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);

    std::cout << "INICIA VISTA 4 " << std::endl;

    escenaAjedrez->createViewports(punteroVentana->getVentana());
    std::cout << "INICIA VISTA 5 " << std::endl;

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::cout << "INICIA VISTA 6 " << std::endl;

    escenaAjedrez->createScene();

    return true;
}




