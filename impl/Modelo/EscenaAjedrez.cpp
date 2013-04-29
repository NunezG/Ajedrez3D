
#include "../../headers/Modelo/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez(void) :
    mRaySceneQuery(0),
    mCamera(0)
   //, mInputMan(0)
  , mOrbiting(false)
  , mGoingLeft(false)
  , mGoingRight(false)
  , mTarget(0)
  , mTopSpeed(150)

  , columnas("ABCDEFGH")
{


    modelo = Modelo::getSingletonPtr();
    tablero = modelo->getTablero();

}
//-------------------------------------------------------------------------------------
EscenaAjedrez::~EscenaAjedrez(void)
{
    mSceneMgr->destroyQuery(mRaySceneQuery);
   // if (mInputMan) delete mInputMan;

}

void EscenaAjedrez::setSceneManager(Ogre::SceneManager* sceneMgr)
{
    mSceneMgr = sceneMgr;

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







EscenaAjedrez* EscenaAjedrez::getSingletonPtr()
{
    static EscenaAjedrez miEscena;
    static EscenaAjedrez* miEscenaPtr = &miEscena;
    return miEscenaPtr;
}

void iluminaCasillaSobrevolada()
{


}

void EscenaAjedrez::apagaCasilla(Casilla* casilla)
{


    casilla->getNodoOgre()->showBoundingBox(false);
    // Casilla *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    // const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
    if (!casilla->esNegra){

        casilla->cambiaMaterial("MaterialCasillaBlanca");
    }else casilla->cambiaMaterial("MaterialCasillaNegra");
}

void EscenaAjedrez::iluminaCasilla(Casilla* casilla)
{


    casilla->getNodoOgre()->showBoundingBox(true);
    // Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    // const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();

    if (casilla->esNegra)
    {


        casilla->cambiaMaterial("MaterialCasillaNegraIlum");
    }else casilla->cambiaMaterial("MaterialCasillaBlancaIlum");
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

void EscenaAjedrez::acabarModoCamara()
{
    std::cout  << "acabarModoCamara " << std::endl;
    //mInputMan->salirModoCamara();
    mOrbiting = false;
}

Ogre::Camera* EscenaAjedrez::createCamera(void){
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

Ogre::RaySceneQuery* EscenaAjedrez::createRayQuery(void)
{
    // Create the camera
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    return mRaySceneQuery;
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

//-------------------------------------------------------------------------------------
//Casilla* EscenaAjedrez::casillaOcupada(Casilla* nodoCasilla)
//{
//Mira si la casilla está ocupada y por quién
//  Ficha* child = static_cast<Casilla*> (nodoCasilla->getHijo(0));
// Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

//  if(child->getAttachedObject(0) != NULL)
//   {
//      return child;
//   }
//}

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






bool EscenaAjedrez::seleccionaFichaEnPosicion(int posX, int posY)
{

    if (tablero->getNodoFichaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...

        std::cout  << "fichasel" << std::endl;
        Ficha* ficha = static_cast<Ficha*>(tablero->getNodoFichaSeleccionada()->getHijo(0));
        ficha->getNodoOgre()->showBoundingBox(false);
        tablero->setNodoFichaSeleccionada(NULL);
    }

    std::cout  << "mpouse2" << std::endl;

    //EMPIEZA RAYO
    //Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
    Ogre::RaySceneQueryResult &result =executeRay(posX,posY,'C');//mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator it;
    it = result.begin();
    std::cout  << "mpouse3" << std::endl;


    if (it != result.end())
    {
        std::cout  << "mpouse31121: "<< it->movable->getParentSceneNode()->getName()<< std::endl;


        std::cout  << "mpouse31121: "<< it->movable->getName()<< std::endl;



        Casilla* casilla = static_cast<Casilla*>(tablero->getHijo(it->movable->getParentSceneNode()->getName()));

        std::cout  << "mpouse31: "<< casilla->getNombre() << std::endl;



        if (casilla != NULL && !casilla->sinHijos())
        {

            Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

            std::cout  << "tiene hijos" << std::endl;


            if ((tablero->getTurnoNegras()
                 && ficha->esNegra)
                    || (!tablero->getTurnoNegras() && !ficha->esNegra))
            {


                tablero->setNodoFichaSeleccionada(casilla);
                ficha->getNodoOgre()->showBoundingBox(true);
                return true;

            }

        }
    }
return false;

}


