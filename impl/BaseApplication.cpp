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
BaseApplication::BaseApplication(Ogre::SceneManager* mSceneMgr)
    : //CreacionJuego(),
      mRaySceneQuery(0),
      mCamera(0),
      mInputMan(0),
      mSceneMgr(mSceneMgr)


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
createViewports();



    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());


    createCamera();

    std::cout << "setupJuego 22 " << std::endl;

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::cout << "setupJuego  33 " << std::endl;



     std::cout << "createscene44" << std::endl;






//   createOverlay();





    return true;
}





//-------------------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{


 mInputMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera

    // mTrayMgr->frameRenderingQueued(evt);

    // if (!mTrayMgr->isDialogVisible())
    //   {

    //     if (mOutputDebugPanel->isVisible())   // if details panel is visible, then update its contents
    //   {
    //   mOutputDebugPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
    //   mOutputDebugPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
    //   mOutputDebugPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
    //    mOutputDebugPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
    //   mOutputDebugPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
    //    mOutputDebugPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
    //  mOutputDebugPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
    //  }
    // }

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


    // if (mTrayMgr->injectMouseMove(arg)) return true;

    //  arg->consume();
    // return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    std::cout << "BASEAPPLICATION MOUSEPRESSED " << std::endl;



    //  mTrayMgr->hideCursor();
    // if (mTrayMgr->injectMouseDown(arg, id)) return true;
    // mInputMan->injectMouseDown(arg, id);
    return true;
}






bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //  mTrayMgr->showCursor();
    //if (mTrayMgr->injectMouseUp(arg, id)) return true;

    // mInputMan->injectMouseUp(arg, id);
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






/*Ogre::Ray BaseApplication::setRayQuery(int posx, int posy, uint32 mask) {
 Ogre::Ray rayMouse = _camera->getCameraToViewportRay
    (posx/float(_win->getWidth()), posy/float(_win->getHeight()));
  _raySceneQuery->setRay(rayMouse);
  _raySceneQuery->setSortByDistance(true);
  _raySceneQuery->setQueryMask(mask);
  return (rayMouse);
}*/





