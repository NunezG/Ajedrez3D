
#include "../../headers/Control/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego()


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
            modelo->destruyeMenu();





             resetOgre();

             punteroVentana->creaVista();


            punteroVentana->vista->mWindow = mRoot->initialise(true, "Ajedrez 2 Jugadores");


            initOgre();

            punteroVentana->muestraAjedrez();


            iniciaModeloAjedrez();



            start();


            // Load resources
           // loadResources();
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


    if(punteroVentana ->ventanaCerrada() || modelo->getSalir())
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


    VistaAjedrez* laVista = static_cast<VistaAjedrez*>(punteroVentana->vista);



    modelo->escenaAjedrez->createViewports(laVista->mWindow);

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);



    modelo->escenaAjedrez->createScene();

    return true;
}





