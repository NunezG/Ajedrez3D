
#include "../../headers/ModeloVista/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez() :
    //  mRoot(root),
    // modelo(mod)
    mCamera(0)
  //, mInputMan(0)
  , tablero(0)
  , mTarget(0)
  , mTopSpeed(150)
  ,   mRaySceneQuery(0)
  , mOrbiting(false)
  , mGoingLeft(false)
  , mGoingRight(false)
  , columnas("ABCDEFGH")
  , ventanaEmergente(0)
{
    std::cout << "nueva escena y enciende tablero" << std::endl;

    // modelo = Modelo::getSingletonPtr();
    tablero = new Tablero();
    mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "MANAGER");

    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

}
//-------------------------------------------------------------------------------------
EscenaAjedrez::~EscenaAjedrez(void)
{
    mSceneMgr->destroyQuery(mRaySceneQuery);
    // if (mInputMan) delete mInputMan;
}

Tablero* EscenaAjedrez::getTablero()
{
    return tablero;
}

void EscenaAjedrez::destruyeTablero()
{
    //delete mSceneMgr;
    delete tablero;
    tablero = NULL;
}

void EscenaAjedrez::creaIluminacion()
{
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

void EscenaAjedrez::createScene()
{
    // mSceneMgr = sceneMgr;

    tablero->creaTableroYCasillas(mSceneMgr);

    // tablero->creaFichasAjedrez(mSceneMgr);
    creaIluminacion();
}

void EscenaAjedrez::DistanciaCamara(int distanciaRelativa)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

    // the further the camera is, the faster it moves
    mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));
}

void EscenaAjedrez::setTarget(Ogre::SceneNode* target)
{
    if (target != mTarget)
    {
        mTarget = target;
        if(target)
        {
            setYawPitchDist(Ogre::Degree(90), Ogre::Degree(50), 110);
            mCamera->setAutoTracking(true, mTarget);
        }
        else
        {
            mCamera->setAutoTracking(false);
        }
    }
}


void EscenaAjedrez::setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist)
{
    mCamera->setPosition(mTarget->_getDerivedPosition());
    mCamera->setOrientation(mTarget->_getDerivedOrientation());
    mCamera->yaw(yaw);
    mCamera->pitch(-pitch);
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}

void EscenaAjedrez::rotacionCamara(Ogre::Degree angulo)
{

    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

    //Mueve la camara a la posicion central
    mCamera->setPosition(mTarget->_getDerivedPosition());
    //ANGULO Ogre::Real(120.0f) * evt.timeSinceLastFrame

    //Rota la camara

    mCamera->yaw(-angulo);

    //Devuelve la camara a su posicion ¿z? original
    // mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.025f));
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));

    //return true;
}

Ogre::Camera* EscenaAjedrez::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(-40,-40,150));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    setTarget(mTarget ? mTarget : mCamera->getSceneManager()->getRootSceneNode());
    mCamera->setFixedYawAxis(true);

    // mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    //  mTopSpeed = topSpeed;

    return mCamera;
}


//-------------------------------------------------------------------------------------
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

    Ogre::uint32 mask;


    switch (mascara)
    {

    case 'C':
        mask = CASILLA;
        break;


    case 'N':
        mask =  NEGRAS;
        break;


    case 'B':
        mask = BLANCAS;
        break;

    default:
        mask = TABLERO;

        break;
    }

    Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);

    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
    return result;
}

Ogre::Ray EscenaAjedrez::setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win)
{
    Ogre::Ray rayMouse = mCamera->getCameraToViewportRay
            (posx/float(win->getWidth()), posy/float(win->getHeight()));

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);
    return (rayMouse);
}

bool EscenaAjedrez::vaIzquierda(){

    return mGoingLeft;
}

bool EscenaAjedrez::vaDerecha(){
    return mGoingRight;
}

bool EscenaAjedrez::esModoCamara()
{
    return mOrbiting;
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

void EscenaAjedrez::empezarModoCamara()
{
    //mInputMan->entrarModoCamara();
    mOrbiting = true;
}

void EscenaAjedrez::acabarModoCamara()
{
    std::cout  << "acabarModoCamara " << std::endl;
    //mInputMan->salirModoCamara();
    mOrbiting = false;
}

//bool EscenaAjedrez::mueveTableroEscena()
//{
//MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
//if (tablero->fichaSeleccionada && tablero->getNodoCasillaSobrevolada()!=NULL && tablero->getNodoCasillaSobrevolada()->getNodoOgre()->getShowBoundingBox())
//   {
// bool resultado = escenaAjedrez->aplicaCambio();


//  modelo->jugadores.at(tablero->getTurnoNegras())->

//    }

//}


std::string EscenaAjedrez::encuentraCasillaSobrevolada(CEGUI::Vector2 mCursorPosition)
{

      //  std::cout << "autorizaCasillaSobrevolada"<< std::endl;

        // escenaAjedrez->apagaAvisos();

        // int posx = arg.state.X.abs;   // Posicion del puntero
        //  int posy = arg.state.Y.abs;   //  en pixeles.

        Ogre::RaySceneQueryResult &result = executeRay(mCursorPosition.d_x, mCursorPosition.d_y, 'C');

        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();

        if (it != result.end())
        {
            Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

            return nodoSobrevolado->getName();
        //    jugadores.at(tablero->getTurnoNegras())->

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
