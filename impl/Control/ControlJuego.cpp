
#include "../../headers/Control/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego(),
    esperaCalculo(false),
    mSceneMgr(mSceneMgr)

{
}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{
}

void ControlJuego::inicio(void){

    modelo->construyeMenu();

    Ogre::Root::getSingletonPtr()->addFrameListener(this);
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

    punteroVentana->EmpiezaCEGUI();
    punteroVentana->MuestraMenu();

    //punteroVentana->iniciaVista();
    // iniciaModeloAjedrez();


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
        if(punteroVentana -> mPantalla > 0){
            std::cout << "CAMBIA DE PANTALLA " << std::endl;

            punteroVentana->muestraAjedrez(/*escenaAjedrez*/);
            std::cout << "FIN CAMBIO" << std::endl;
            iniciaModeloAjedrez();

        }
    }  else if(punteroVentana -> mPantalla == 2)
    {


        if (modelo->getTablero()->getTurnoNegras() && esperaCalculo == false)
        {
            punteroVentana->capturaRaton = false;

            calculaMovimiento();
            //  esperaCalculo=true;
        }else punteroVentana->capturaRaton = true;

    }


    if(punteroVentana -> getVentana()->isClosed())
        return false;

    if(!punteroVentana -> getVentana()->isVisible())
        return false;

    if(punteroVentana -> mShutDown)
        return false;

    punteroVentana->frameRenderingQueued(evt);

    //jugador.mueveFicha();


    return true;
}


//------------------------------------------------------------------------------------
bool ControlJuego::iniciaModeloAjedrez(void)
{
    // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    escenaAjedrez = EscenaAjedrez::getSingletonPtr();

    std::cout << "INICIA VISTA 1 " << std::endl;

    modelo->construyeAjedrez();


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





void ControlJuego::createScene(void)
{
}




bool ControlJuego::iniciaModelo(){

}

void ControlJuego::calculaMovimiento(){

    std::cout << "CALCULA MOVIMIENTO" << std::endl;


    ModuloIA* modulo = ModuloIA::getCEGUISingletonPtr();

    //¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡PASALO A VITA AJEDREZ SOLO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    modulo->construyeArbol(modelo->getTablero()->traduceTablero());


    if (modulo->tableroElegido != NULL)
    {
        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[0]<< std::endl;
        std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[1]<< std::endl;

        modelo->getTablero()->mueveIA(modulo->tableroElegido->movimiento[0],modulo->tableroElegido->movimiento[1]);

        modulo->tableroElegido = NULL;

    } else std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;

    std::cout  << "DELETE TABLEROPADRE EN COTROL: "<<  std::endl;

    delete modulo->tableroPadre;

    std::cout  << "NULEA MODULO EN COTROL: "<<  std::endl;
    modulo->tableroPadre = NULL;

    modulo = NULL;

    //   std::cout   << "BORRA TABLERO " << std::endl;


    //  delete modulo->tableroElegido;


    //   std::cout  << "NULLEA TABLERO " << std::endl;


    //  modulo->tableroElegido = NULL;

    //modulo->ejecutaMovimiento(mod);

    //INICIA LA IA PARA CALCULAR LA FICHA A MOVER

    //PRIMERO HAZLO CON EL TABLERO Y LUEGO TE OCUPAS DE LAS FICHAS
    //EMPEZAMOS POR TODOS LOS MOVIMIENTOS DE TODOS LOS PEONES
    //ModuloIA modulo;

    // modelo->escena->tablero->movimientosPeon();
}
