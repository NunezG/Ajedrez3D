
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

 //  std::cout << "frameRenderingQueued"<< std::endl;


    if(punteroVentana -> pantallaActual() == 0)
    {

        if(modelo->getNumPantalla() > 0)
        {
            modelo->destruyeMenu();

            punteroVentana->muestraAjedrez();
            iniciaModeloAjedrez();
        }

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
    modelo->creaJugador(true, true);



    if (modelo->getNumPantalla() == 1)
    {
        modelo->creaJugador(false, true);


    }else {

        modelo->creaJugador(false, false);

    }

    modelo->escenaAjedrez->setSceneManager(mRoot);
    modelo->escenaAjedrez->createCamera();


    modelo->escenaAjedrez->createRayQuery();

   // escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);


    modelo->escenaAjedrez->createViewports(punteroVentana->getVentana());

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);



    modelo->escenaAjedrez->createScene();

    return true;
}





