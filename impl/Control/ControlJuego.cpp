
#include "../../headers/Control/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego()


{
}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{
    std::cout << "DELETE JUGADORES" << std::endl;


    std::cout << "FIN DELETE" << std::endl;


}

ControlJuego& ControlJuego::getControlSingleton()
{
    static ControlJuego miControlJuego_;
    return miControlJuego_;
}

//-------------------------------------------------------------------------------------
bool ControlJuego::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    std::cout << "FRAME CHUNGO" << std::endl;


    if(punteroVentana -> pantallaActual() == 0)
    {
        std::cout << "PUNT" <<std::endl;

        if(modelo->getNumPantalla() > 0)
        {
            std::cout << "CAMBIA DE PANTALLA " << std::endl;
            modelo->destruyeMenu();

            punteroVentana->muestraAjedrez();
            std::cout << "FIN CAMBIO" << std::endl;
            iniciaModeloAjedrez();
        }
        std::cout << "finif " <<std::endl;

    }


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


    else if(punteroVentana -> pantallaActual() > 0)
    {



        modelo->mueveFicha(evt.timeSinceLastFrame);

      //  if (modelo->getTablero()->getNodoCasillaSobrevolada() != NULL && modelo->getTablero()->getNodoCasillaSobrevolada()->seleccionada)
      //  {
          //  std::cout << "ILUMINA UNA CASILLA" <<std::endl;

           // static_cast<VistaAjedrez*>(punteroVentana->vista)->escenaAjedrez->iluminaCasilla(modelo->getTablero()->getNodoCasillaSobrevolada());
          //  static_cast<JugadorHumano*>(modelo->jugadores.at(modelo->getTablero()->getTurnoNegras()))->sobreVuelaCasilla();


       // }

    }

    std::cout << "finifififif " <<std::endl;

    if(punteroVentana -> getVentana()->isClosed())
        return false;


    std::cout << "1 " <<std::endl;

    if(!punteroVentana -> getVentana()->isVisible())
        return false;


    std::cout << "2 " <<std::endl;

    if(modelo->getSalir())
        return false;
    std::cout << "3 " <<std::endl;

    punteroVentana->frameRenderingQueued(evt);

    //jugador.mueveFicha();


    std::cout << "return " <<std::endl;

    return true;
}





//------------------------------------------------------------------------------------
bool ControlJuego::iniciaModeloAjedrez(void)
{
    // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    modelo->creaJugador(true, true);



    if (modelo->getNumPantalla() == 1)
    {
        modelo->creaJugador(false, true);


    }else {

        modelo->creaJugador(false, false);

    }




    //escenaAjedrez = EscenaAjedrez::getSingletonPtr();

    std::cout << "INICIA VISTA 1 " << std::endl;



    //escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    std::cout << "INICIA VISTA 2 " << std::endl;

    static_cast<VistaAjedrez*>(punteroVentana->vista)->escenaAjedrez->setSceneManager(mRoot);

    static_cast<VistaAjedrez*>(punteroVentana->vista)->createRayQuery();
    std::cout << "INICIA VISTA 3 " << std::endl;

   // escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);

    std::cout << "INICIA VISTA 4 " << std::endl;

    static_cast<VistaAjedrez*>(punteroVentana->vista)->escenaAjedrez->createViewports(punteroVentana->getVentana());
    std::cout << "INICIA VISTA 5 " << std::endl;

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::cout << "INICIA VISTA 6 " << std::endl;

    static_cast<VistaAjedrez*>(punteroVentana->vista)->escenaAjedrez->createScene();

    return true;
}





