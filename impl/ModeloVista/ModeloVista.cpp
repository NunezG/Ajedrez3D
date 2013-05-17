
#include "../../headers/ModeloVista/ModeloVista.h"

//-------------------------------------------------------------------------------------
ModeloVista::ModeloVista(Modelo* modelo):
    modelo(modelo)
    , mPantalla(0)
   , escena(NULL)
 , salirPulsado(0)

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

void ModeloVista::cambiaPantalla(int pantallaNueva)
{
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    wmgr.getWindow("MenuInicio/VentanaMenu")->setVisible(false);
    // wmgr.getWindow("Demo")->setVisible(false);

    wmgr.getWindow("MenuInicio")->setVisible(false);

    wmgr.destroyWindow("MenuInicio/VentanaMenu");
    wmgr.destroyWindow("MenuInicio");

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

bool ModeloVista::getSalir()
{
    return salirPulsado;
}

void ModeloVista::setSalir(bool salir)
{
    salirPulsado = salir;
}

//------------------------------------------------------------------------------------
bool ModeloVista::iniciaModeloAjedrez()
{
    escena  = new EscenaAjedrez(modelo);

    // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    modelo->creaJugador(true, true, escena->getTablero()->traduceTablero());

    if (getNumPantalla() == 1)
    {
        modelo->creaJugador(false, true, escena->getTablero()->traduceTablero());
    }else {

        modelo->creaJugador(false, false, escena->getTablero()->traduceTablero());
    }

    escena->setSceneManager(/*mRoot*/);
    escena->createCamera();

    escena->createRayQuery();

   // escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);



    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    escena->createScene();

    return true;
}
