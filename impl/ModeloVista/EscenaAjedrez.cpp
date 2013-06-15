#include "../../headers/ModeloVista/EscenaAjedrez.h"

EscenaAjedrez::EscenaAjedrez() :
    mCamera(0)
  //, tablero(0)
  , mTarget(0)
 // , mTopSpeed(150)
 // ,   mRaySceneQuery(0)
  //, mOrbiting(false)
  , mGoingLeft(false)
  , mGoingRight(false)
 // , columnas("ABCDEFGH")
  , ventanaEmergente(0)
{
    tablero = new Tablero();
    mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "MANAGER");
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

}

EscenaAjedrez::~EscenaAjedrez(void)
{
    mSceneMgr->destroyQuery(mRaySceneQuery);
    delete tablero;
    tablero = NULL;
}

Tablero* EscenaAjedrez::getTablero()
{
    return tablero;
}

void EscenaAjedrez::createScene()
{
    tablero->creaTableroYCasillas(mSceneMgr);

//CREA LA ILUMINACIÓN
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setShadowColour(Ogre::ColourValue(0.75, 0.75, 0.75) );
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.55, 0.55, 0.55));

    mSceneMgr->setShadowTextureCount(2);
    mSceneMgr->setShadowTextureSize(1024);

    Ogre::Light* light2 = mSceneMgr->createLight("Light2");
    light2->setPosition(600,5000,600);
    //  light2->setDiffuseColour(0.1,0.1,0.1);
    light2->setType(Ogre::Light::LT_POINT);
    light2->setDirection(Ogre::Vector3(0,0,0));
    //  light2->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    //light2->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    //light2->setSpotlightFalloff(1.0f);
    light2->setCastShadows(true);

    Ogre::Light* light = mSceneMgr->createLight("Light1");
    light->setPosition(-600,5000,-600);
    light->setType(Ogre::Light::LT_POINT);
    light->setDirection(Ogre::Vector3(0,0,0));
    // light2->setDiffuseColour(0.1,0.1,0.1);
    // light->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    // light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    // light->setSpotlightFalloff(1.0f);
    light->setCastShadows(true);


}

void EscenaAjedrez::DistanciaCamara(int distanciaRelativa)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();
    mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));
}





void EscenaAjedrez::rotacionCamara(Ogre::Degree angulo)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

    //Mueve la camara a la posicion central
    mCamera->setPosition(mTarget->_getDerivedPosition());
    //Rota la camara
    mCamera->yaw(-angulo);

    //Devuelve la camara a su posicion original
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}

void EscenaAjedrez::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(-40,-40,150));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);


    if (mCamera->getSceneManager()->getRootSceneNode() != mTarget)
    {
        mTarget = mCamera->getSceneManager()->getRootSceneNode();
        if(mTarget)
        {
            mCamera->setPosition(mTarget->_getDerivedPosition());
            mCamera->setOrientation(mTarget->_getDerivedOrientation());
            mCamera->yaw(Ogre::Degree(90));
            mCamera->pitch(-Ogre::Degree(50));
            mCamera->moveRelative(Ogre::Vector3(0, 0, 110));
            mCamera->setAutoTracking(true, mTarget);
        }
        else
        {
            mCamera->setAutoTracking(false);
        }
    }

    mCamera->setFixedYawAxis(true);

    // mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    //  mTopSpeed = topSpeed;

   // return mCamera;
}

void EscenaAjedrez::createViewports(Ogre::RenderWindow* window)
{
    mWindow = window;
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

Ogre::RaySceneQueryResult& EscenaAjedrez::executeRay(int posx, int posy, char mascara)
{   
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    Ogre::uint32 mask;

    switch (mascara)
    {

    case 'C':
        mask = CASILLA;
        break;

    default:
        mask = TABLERO;

        break;
    }

    Ogre::Ray rayMouse = mCamera->getCameraToViewportRay
            (posx/float(mWindow->getWidth()), posy/float(mWindow->getHeight()));

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);

    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();

    return result;
}

bool EscenaAjedrez::vaIzquierda()
{
    return mGoingLeft;
}

bool EscenaAjedrez::vaDerecha(){
    return mGoingRight;
}

void EscenaAjedrez::mueveCamaraIzquierda()
{
    mGoingLeft = true;
}

void EscenaAjedrez::mueveCamaraDerecha()
{
    mGoingRight = true;
}

void EscenaAjedrez::noMueveCamara()
{
    mGoingRight = false;
    mGoingLeft = false;
}

void EscenaAjedrez::setModoCamara(bool modo)
{
    modoCamara = modo;
}

bool EscenaAjedrez::getModoCamara()
{
   return modoCamara;
}

std::string EscenaAjedrez::encuentraCasillaSobrevolada(CEGUI::Vector2 mCursorPosition)
{
        Ogre::RaySceneQueryResult &result = executeRay(mCursorPosition.d_x, mCursorPosition.d_y, 'C');
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();

        if (it != result.end())
        {
            Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();
            return nodoSobrevolado->getName();
        }

    return "";
}

void EscenaAjedrez::muestraVentanaEmergente(std::string nombreLayout)
{
    if (!CEGUI::WindowManager::getSingleton().isWindowPresent(nombreLayout))
    {
        ventanaEmergente = CEGUI::WindowManager::getSingleton().loadWindowLayout(nombreLayout+"CEED.layout");
        //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaEmergente);
    }else
    {
        ventanaEmergente = CEGUI::WindowManager::getSingleton().getWindow(nombreLayout);
        ventanaEmergente->setVisible(true);
    }
}

void EscenaAjedrez::apagaVentanaEmergente()
{
    //CEGUI::System::getSingleton().getGUISheet()->cleanupChildren();
    if (ventanaEmergente != NULL && ventanaEmergente->isVisible())
    {
         std::cout << "apagaavisos dentro"<< std::endl;
        ventanaEmergente->setVisible(false);
        CEGUI::WindowManager::getSingleton().destroyWindow(ventanaEmergente->getName());
        ventanaEmergente = NULL;
    }
}
