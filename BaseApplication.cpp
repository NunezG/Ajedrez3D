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
#include "BaseApplication.h"

//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
   // mTrayMgr(0),
    //mCameraMan(0),
  //  mOutputDebugPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mInputMan(0),
    mMouse(0),
    mKeyboard(0),
    mLastStatUpdateTime(0),
    mCursor(0)
{

}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
   // if (mTrayMgr) delete mTrayMgr;
    if (mInputMan) delete mInputMan;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
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
//-------------------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    //A PARTIR DE AQUI ES MAS O MENOS OPCIONAL





  //  mTrayMgr = new OgreBites::SdkTrayManager("MiTrayManager", mWindow, mMouse, this);

  //  mTrayMgr->showTrays();
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
   // mTrayMgr->hideCursor();

    // create a params panel for displaying sample details
 //   Ogre::StringVector items;
 //   items.push_back("Línea 1:");
/*    items.push_back("Línea 2:");
    items.push_back("Línea 3:");
    items.push_back("Línea 4:");
    items.push_back("Línea 5:");
    items.push_back("Línea 6:");
    items.push_back("Línea 7:");
    items.push_back("Línea 8:");
    items.push_back("Línea 9:");
    items.push_back("Línea 10:");
    items.push_back("Línea 11:");

    mOutputDebugPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DebugPanel", 600, items);
    mOutputDebugPanel->setParamValue(9, "Bilinear");
    mOutputDebugPanel->setParamValue(10, "Solid");
    mOutputDebugPanel->hide();
*/
    mRoot->addFrameListener(this);

    createOverlay();

}
//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
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
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}
//-------------------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);
    mTimer = Ogre::Root::getSingleton().getTimer();

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();

    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();

    return true;
}
//-------------------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    // mTrayMgr->frameRenderingQueued(evt);
    BaseApplication::statUpdate(evt);
   // if (!mTrayMgr->isDialogVisible())
 //   {
        mInputMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
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



bool areFrameStatsVisible()
{
    return true;//mFpsLabel != 0;
}


/*-----------------------------------------------------------------------------
| Process frame events. Updates frame statistics widget set and deletes
| all widgets queued for destruction.
-----------------------------------------------------------------------------*/
bool BaseApplication::statUpdate(const Ogre::FrameEvent& evt)
{


    unsigned long currentTime = mTimer->getMilliseconds();
    if (areFrameStatsVisible() && currentTime - mLastStatUpdateTime > 250)
    {
        Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();

        mLastStatUpdateTime = currentTime;

        Ogre::String s("FPS: ");
        s += Ogre::StringConverter::toString((int)stats.lastFPS);

        for (int i = s.length() - 5; i > 5; i -= 3) { s.insert(i, 1, ','); }
       // mFpsLabel->setCaption(s);

    /*    if (mStatsPanel->getOverlayElement()->isVisible())
        {
            Ogre::StringVector values;
            std::ostringstream oss;

            oss.str("");
            oss << std::fixed << std::setprecision(1) << stats.avgFPS;
            Ogre::String str = oss.str();
            for (int i = str.length() - 5; i > 0; i -= 3) { str.insert(i, 1, ','); }
            values.push_back(str);

            oss.str("");
            oss << std::fixed << std::setprecision(1) << stats.bestFPS;
            str = oss.str();
            for (int i = str.length() - 5; i > 0; i -= 3) { str.insert(i, 1, ','); }
            values.push_back(str);

            oss.str("");
            oss << std::fixed << std::setprecision(1) << stats.worstFPS;
            str = oss.str();
            for (int i = str.length() - 5; i > 0; i -= 3) { str.insert(i, 1, ','); }
            values.push_back(str);

            str = Ogre::StringConverter::toString(stats.triangleCount);
            for (int i = str.length() - 3; i > 0; i -= 3) { str.insert(i, 1, ','); }
            values.push_back(str);

            str = Ogre::StringConverter::toString(stats.batchCount);
            for (int i = str.length() - 3; i > 0; i -= 3) { str.insert(i, 1, ','); }
            values.push_back(str);

            mStatsPanel->setAllParamValues(values);
        }
*/
    }

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
    mCursor->setPosition(mMouse->getMouseState().X.abs, mMouse->getMouseState().Y.abs);
   // if (mTrayMgr->injectMouseMove(arg)) return true;
    mInputMan->injectMouseMove(arg);
    return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
  //  mTrayMgr->hideCursor();
   // if (mTrayMgr->injectMouseDown(arg, id)) return true;
   mInputMan->injectMouseDown(arg, id);
    return true;
}

bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
  //  mTrayMgr->showCursor();
   //if (mTrayMgr->injectMouseUp(arg, id)) return true;
   mInputMan->injectMouseUp(arg, id);
    return true;
}

//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

/*Ogre::Ray BaseApplication::setRayQuery(int posx, int posy, uint32 mask) {
 Ogre::Ray rayMouse = _camera->getCameraToViewportRay
    (posx/float(_win->getWidth()), posy/float(_win->getHeight()));
  _raySceneQuery->setRay(rayMouse);
  _raySceneQuery->setSortByDistance(true);
  _raySceneQuery->setQueryMask(mask);
  return (rayMouse);
}*/

//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}


void BaseApplication::createOverlay() {
  mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
  Ogre::Overlay *overlay = mOverlayManager->getByName("Info");
  overlay->show();
  mCursor = (Ogre::OverlayContainer*)mOverlayManager->getOverlayElement("cursor");
 // mCursor =  (Ogre::OverlayContainer*)mOverlayManager->createOverlayElementFromTemplate("cursor", "Panel", "Cursor");
 // mCursor = mOverlayManager->getOverlayElement("cursor");
}

