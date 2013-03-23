
#include "../headers/ControlJuego.h"

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
    if(punteroVentana->pantallaActual() == 0)
    {
         std::cout << "PANTALLA ACTUAL ES 0" << std::endl;

        if(punteroVentana->mPantalla > 0){
            std::cout << "CAMBIA DE PANTALLA " << std::endl;

            punteroVentana->muestraAjedrez(/*escenaAjedrez*/);
            std::cout << "FIN CAMBIO" << std::endl;
            iniciaModeloAjedrez();


        }
    }

    if(punteroVentana->getVentana()->isClosed())
        return false;

    if(!punteroVentana->getVentana()->isVisible())
        return false;

    if(punteroVentana->mShutDown)
        return false;



    punteroVentana->frameRenderingQueued(evt);


    if(punteroVentana->mPantalla == 2)
    {
        std::cout << "punteroVentana->mPantalla = 2" << std::endl;



        if (modelo->escena->esTurnoNegras() && esperaCalculo == false)
        {
            calculaMovimiento();
            esperaCalculo==true;
        }

}


    return true;
}


//------------------------------------------------------------------------------------
bool ControlJuego::iniciaModeloAjedrez(void)
{
   // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    std::cout << "INICIA VISTA 1 " << std::endl;

    modelo->construyeAjedrez();


    //escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    std::cout << "INICIA VISTA 2 " << std::endl;

    modelo->escena->setSceneManager(mSceneMgr);

    modelo->escena->createRayQuery();
    std::cout << "INICIA VISTA 3 " << std::endl;

    modelo->escena->createCamera();
   // mInputMan = new InputMan::SdkCameraMan(escenaAjedrez->createCamera());   // create a default camera controller
    //mInputMan->setTopSpeed(100);

    std::cout << "INICIA VISTA 4 " << std::endl;

    modelo->escena->createViewports(punteroVentana->getVentana());
    std::cout << "INICIA VISTA 5 " << std::endl;

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::cout << "INICIA VISTA 6 " << std::endl;

    createScene();

    return true;
}





void ControlJuego::createScene(void)
{
    modelo->escena->createScene();
}




bool ControlJuego::iniciaModelo(){

}

void ControlJuego::calculaMovimiento(){
    //INICIA LA IA PARA CALCULAR LA FICHA A MOVER









}
