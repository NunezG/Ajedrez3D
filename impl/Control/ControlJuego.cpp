
#include "../../headers/Control/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego(),
    esperaCalculo(false)

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
    else if(modelo->getNumPantalla() == 2)
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
