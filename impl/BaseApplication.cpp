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
      mWindow(mWindow)



    //mTrayMgr(0),
    //mCameraMan(0),
    //  mOutputDebugPanel(0),




{

    //this->mSceneMgr = mSceneMgr;

}


//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    //if (mTrayMgr) delete mTrayMgr;

    mSceneMgr->destroyQuery(mRaySceneQuery);

}






//-------------------------------------------------------------------------------------
bool BaseApplication::setupJuego(void)
{
    std::cout << "set" << std::endl;

    std::cout << "setupJuego" << std::endl;



    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    std::cout << "setupJuego 112221 " << std::endl;

    createCamera();

    std::cout << "setupJuego 11 " << std::endl;

    createViewports();

    std::cout << "setupJuego 22 " << std::endl;

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::cout << "setupJuego  33 " << std::endl;

    createScene();

    std::cout << "createscene44" << std::endl;






    //   createOverlay();





    return true;
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


    // mCursor->setPosition(mMouse->getMouseState().X.abs, mMouse->getMouseState().Y.abs);



    //  arg->consume();
    // return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    std::cout << "BASEAPPLICATION MOUSEPRESSED " << std::endl;

    //  mTrayMgr->hideCursor();
    // if (mTrayMgr->injectMouseDown(arg, id)) return true;
    mInputMan->injectMouseDown(arg, id);
    std::cout << "ACABA MOUSEPRESSED " << std::endl;

    return true;
}






bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //  mTrayMgr->showCursor();
    //if (mTrayMgr->injectMouseUp(arg, id)) return true;

    mInputMan->injectMouseUp(arg, id);
    return true;
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
    std::cout << "createViewports "<<std::endl;

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

    std::cout << "CREA LA CAMARA" << std::endl;


    mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    mInputMan->setTopSpeed(100);
}


void BaseApplication::createScene(void)
{
    EscenaAjedrez EscAjedrez;

    EscAjedrez.createScene(mSceneMgr);

}


/*Ogre::Ray BaseApplication::setRayQuery(int posx, int posy, uint32 mask) {
 Ogre::Ray rayMouse = _camera->getCameraToViewportRay
    (posx/float(_win->getWidth()), posy/float(_win->getHeight()));
  _raySceneQuery->setRay(rayMouse);
  _raySceneQuery->setSortByDistance(true);
  _raySceneQuery->setQueryMask(mask);
  return (rayMouse);
}*/





