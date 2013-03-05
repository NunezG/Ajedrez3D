/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "../headers/BaseApplication.h"


//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow)
    : //CreacionJuego(),
      mRaySceneQuery(0),
      mCamera(0),
      mInputMan(0),
      mSceneMgr(mSceneMgr),
      mWindow(mWindow),
      turnoNegras(0),
      _nodoNuevo(0)

{
}

BaseApplication::~BaseApplication(void)
{
    if (mInputMan) delete mInputMan;
    mSceneMgr->destroyQuery(mRaySceneQuery);
}


//-------------------------------------------------------------------------------------
bool BaseApplication::setupJuego(void)
{
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    createScene();

    return true;
}


void BaseApplication::apagaCasilla(Ogre::SceneNode* casilla)
{
    casilla->showBoundingBox(false);
    Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
    if (mNombreEntidad[1] == 'B'){
        mEntidadCasilla->setMaterialName("MaterialBlanco");
    }else mEntidadCasilla->setMaterialName("MaterialNegro");
}


void BaseApplication::iluminaCasilla(Ogre::SceneNode* casilla){
    casilla->showBoundingBox(true);
    Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
    if (mNombreEntidad[1] == 'B')
    {
        mEntidadCasilla->setMaterialName("MaterialBlancoIluminado");
    }else mEntidadCasilla->setMaterialName("MaterialNegroIluminado");
}

//-------------------------------------------------------------------------------------
void BaseApplication::FichaComestible()
{
    //Mira si la casilla está ocupada y por quién
    Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (_nodoNuevo->getChild(0));
    Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

    if((!turnoNegras && ent->getName()[1] == 'N')
            || (turnoNegras && ent->getName()[1] == 'B'))
    {
        iluminaCasilla(_nodoNuevo);
    }
}

Ogre::Ray BaseApplication::setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win)
{
    Ogre::Ray rayMouse = mCamera->getCameraToViewportRay
            (posx/float(win->getWidth()), posy/float(win->getHeight()));

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);
    return (rayMouse);
}

//-------------------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}


//-------------------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(-40,-40,150));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    mInputMan->setTopSpeed(100);
}


void BaseApplication::createScene(void)
{
    EscenaAjedrez EscAjedrez;
    EscAjedrez.createScene(mSceneMgr);
}

//-------------------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
    mInputMan->injectKeyDown(arg);

    return true;
}

bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{
    mInputMan->injectKeyUp(arg);

    return true;
}

bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    mInputMan->injectMouseMove(arg);

    return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    mInputMan->injectMouseDown(arg, id);

    return true;
}

bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    mInputMan->injectMouseUp(arg, id);
    return true;
}
