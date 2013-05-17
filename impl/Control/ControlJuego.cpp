
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





    punteroVentana->frameRenderingQueued(evt);

    //jugador.mueveFicha();



    return true;
}

//------------------------------------------------------------------------------------
bool ControlJuego::iniciaModeloAjedrez(void)
{

    escenaAjedrez  = EscenaAjedrez::getSingletonPtr();


    // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    modelo->creaJugador(true, true, escenaAjedrez->getTablero()->traduceTablero());


    if (modelo->getNumPantalla() == 1)
    {
        modelo->creaJugador(false, true, escenaAjedrez->getTablero()->traduceTablero());


    }else {

        modelo->creaJugador(false, false, escenaAjedrez->getTablero()->traduceTablero());

    }

    escenaAjedrez->setSceneManager(/*mRoot*/);
    escenaAjedrez->createCamera();


    escenaAjedrez->createRayQuery();

   // escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);


    VistaAjedrez* laVista = static_cast<VistaAjedrez*>(punteroVentana->vista);



    escenaAjedrez->createViewports(laVista->mWindow);

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);



    escenaAjedrez->createScene();

    return true;
}





