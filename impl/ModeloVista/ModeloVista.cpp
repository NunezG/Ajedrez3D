
#include "../../headers/ModeloVista/ModeloVista.h"

//-------------------------------------------------------------------------------------
ModeloVista::ModeloVista(Modelo* modelo):
    modelo(modelo)
    , mPantalla(0)
   , escena(NULL)
   , mShutDown(0)

{
}

//-------------------------------------------------------------------------------------
ModeloVista::~ModeloVista(void)
{
    resolucion = "800 x 600";

    // if (mInputMan) delete mInputMan;
}

bool ModeloVista::getApagar()
{

    return mShutDown;

}

void ModeloVista::cambiaTurno()
{
    escena->tablero->cambiaTurno();

}


void ModeloVista::setApagar(bool apaga)
{

    mShutDown = apaga;

}
void ModeloVista::cambiaPantalla(int pantallaNueva)
{


    setNumPantalla(pantallaNueva);
}

int ModeloVista::getNumPantalla()
{
    return mPantalla;
}

void ModeloVista::setNumPantalla(int pantalla)
{
    mPantalla = pantalla;
}


void ModeloVista::setSalir(bool salir)
{
    mShutDown = salir;
}

//------------------------------------------------------------------------------------
bool ModeloVista::iniciaModeloAjedrez()
{
    escena  = new EscenaAjedrez(modelo);

    // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    modelo->creaJugador(true, true);

    //jugadorActual = modelo->jugadores.at(0);


    if (getNumPantalla() == 1)
    {
        modelo->creaJugador(false, true);
    }else {

        modelo->creaJugador(false, false);
    }
  }




bool ModeloVista::preparaEscena()
{
    std::cout   << "   iniciamodelo1" << std::endl;


    escena->setSceneManager();
    std::cout   << "   iniciamodelo2" << std::endl;

    escena->createCamera();
    std::cout   << "   iniciamodelo3" << std::endl;

    escena->createRayQuery();
    std::cout   << "   iniciamodelo4" << std::endl;

   // escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);

    // Set default mipmap level (NB some APIs ignore this)
    std::cout   << "   iniciamodelo5" << std::endl;


    return true;
}
