#include "../headers/CreacionJuego.h"



//-------------------------------------------------------------------------------------
CreacionJuego::CreacionJuego(void):
    mWindow(0),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mSceneMgr(0),
    mModoJuego(1),
    mRoot(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mShutDown(false),
    mLastStatUpdateTime(0),

    mPantalla(0)

  //mCursorWasVisible(false)

    //mCursor(0)


    //mRenderer(0)

{








}
//-------------------------------------------------------------------------------------
CreacionJuego::~CreacionJuego(void)
{

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
     delete mRoot;
}

///////////////////////////////////////////////////////////////////////////////////////7












//-------------------------------------------------------------------------------------
bool CreacionJuego::configureOpenGL(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    //if(mRoot->showConfigDialog())
    if(configuraGraficos("OpenGL"))
    {
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "Ajedrez OpenGL");

        return true;
    }
    else
    {
        return false;
    }
}


bool CreacionJuego::configuraGraficos(const char *desiredRenderer)
{

    Ogre::RenderSystem *renderSystem;
    bool ok = false;
    Ogre::RenderSystemList renderers =
            mRoot->getSingleton().getAvailableRenderers();

    // See if the list is empty (no renderers available)
    if(renderers.empty())
        return false;

    for(Ogre::RenderSystemList::iterator it = renderers.begin();
        it != renderers.end(); it++)
    {
        renderSystem = *it;
        if(strstr(renderSystem->getName().c_str(), desiredRenderer))
        {
            ok = true;
            break;
        }
    }

    if(!ok) {
        // We still don't have a renderer; pick
        // up the first one from the list
        renderSystem = *renderers.begin();
    }

    mRoot->getSingleton().setRenderSystem(renderSystem);

    // Manually set some configuration options (optional)

    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
        std::cout << "LAS OPCIONES: " <<CO.first<<" " <<CO.second.currentValue << std::endl;


    }

    renderSystem->setConfigOption("Full Screen", "No");

    renderSystem->setConfigOption("Video Mode", "800 x 600");


    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
        std::cout << "LAS OPCIONES: " <<CO.first<<" " <<CO.second.currentValue << std::endl;
    }
    return true;

}



//Unattach OIS before window shutdown (very important under Linux)
void CreacionJuego::windowClosed(Ogre::RenderWindow* rw)
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

//Adjust mouse clipping area
void CreacionJuego::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}


//-------------------------------------------------------------------------------------
void CreacionJuego::iniciaIO(void)
{

 //   CEGUIFrameListener* mFrameListener;


    mFrameListener = new CEGUIFrameListener(mWindow);
  //  mFrameListener..empie
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

    mRoot->addFrameListener(this);


    Ogre::LogManager::getSingletonPtr()->logMessage("*** FIN OIS ***");


    // mTrayMgr = new OgreBites::SdkTrayManager("MiTrayManager", mWindow, mMouse, this);
    //  mTrayMgr->showTrays();
    //  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //  mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //  mTrayMgr->hideCursor();

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




}




//void CreacionJuego::creaTablero(void)
//{



 //   EscenaAjedrez EscAjedrez;

  //  EscAjedrez.createScene(mSceneMgr);

   // TutorialApplication ta;



//}

//void CreacionJuego::createGUI(void){



 //  if(mPantalla==0){

    //    TutorialApplication tut;



//    }




//}


 //-------------------------------------------------------------------------------------
 bool CreacionJuego::frameRenderingQueued(const Ogre::FrameEvent& evt)
 {



     Ogre::LogManager::getSingletonPtr()->logMessage("*** frameRenderingQueued***");






     mFrameListener->injectTimePulse(evt);

     if(mWindow->isClosed())
         return false;

     if(mShutDown)
         return false;

     //Need to capture/update each device
     mKeyboard->capture();
     mMouse->capture();

     CreacionJuego::statUpdate(evt);












return true;


     //return  BaseApplication::frameRenderingQueued(evt);

 }



 /* void CreacionJuego::createOverlay() {
     // OgreBites::Button *buton = mTrayMgr->createButton(OgreBites::TL_CENTER,"NOMBREBOTON","CAPTIONBONTON",250);
     //mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
     //    mTrayMgr->showFrameStats(OgreBites::TL_TOPLEFT);
     //   mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);


     mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
     Ogre::Overlay *overlay = mOverlayManager->getByName("Info");
     // Ogre::OverlayElement* cont = mOverlayManager->getOverlayElement("instrucciones");
     // cont->setCaption("PRUEBA DE OVERLAY");
     //overlay->show();
     mCursor = (Ogre::OverlayContainer*)mOverlayManager->getOverlayElement("cursor");

     // mCursor =  (Ogre::OverlayContainer*)mOverlayManager->createOverlayElementFromTemplate("cursor", "Panel", "Cursor");
     // mCursor = mOverlayManager->getOverlayElement("cursor");
 }
*/


//-------------------------------------------------------------------------------------
bool CreacionJuego::configureOgre(void)
{

    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";

    mRoot = new Ogre::Root(mPluginsCfg);
    mTimer = Ogre::Root::getSingleton().getTimer();

    setupResources();

    bool carryOn = configureOpenGL();
    if (!carryOn) return false;

    chooseSceneManager();
    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources

    loadResources();




    iniciaIO();

return true;
}






bool CreacionJuego::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //  mTrayMgr->showCursor();
    //if (mTrayMgr->injectMouseUp(arg, id)) return true;
    mFrameListener->mouseReleased(arg,id);

    // mInputMan->injectMouseUp(arg, id);
    return true;
}

bool CreacionJuego::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    std::cout << "BASEAPPLICATION MOUSEPRESSED " << std::endl;


    mFrameListener->mousePressed(arg,id);




















    //  mTrayMgr->hideCursor();
    // if (mTrayMgr->injectMouseDown(arg, id)) return true;
    // mInputMan->injectMouseDown(arg, id);
    return true;
}


bool CreacionJuego::mouseMoved( const OIS::MouseEvent &arg )
{



    mFrameListener->mouseMoved(arg);





    return true;





}


//-------------------------------------------------------------------------------------
bool CreacionJuego::keyPressed( const OIS::KeyEvent &arg )
{



    if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
        return true;
    }else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }




    mFrameListener->keyPressed(arg);





    return true;
}

bool CreacionJuego::keyReleased( const OIS::KeyEvent &arg )
{



    mFrameListener->keyReleased(arg);


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
bool CreacionJuego::statUpdate(const Ogre::FrameEvent& evt)
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

            mStatsPanel->setAllParamValues(values);
        }
*/
    }

    return true;
}


//-------------------------------------------------------------------------------------
bool CreacionJuego::setup(void)
{





    return true;
}

void CreacionJuego::destroyScene(void)
{
}


//-----------------------------------------------------------------------
//CONFIGURACION PREVIA A LA INICIALIZACION DE GRAFICOS
//-------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------
void CreacionJuego::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}





//-------------------------------------------------------------------------------------
void CreacionJuego::setupResources(void)
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
void CreacionJuego::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void CreacionJuego::loadResources(void)
{

       Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();



}












//-------------------------------------------------------------------------------------
void CreacionJuego::go(void)
{
//#ifdef _DEBUG
 //   mResourcesCfg = "resources_d.cfg";
 //   mPluginsCfg = "plugins_d.cfg";
//#else
   // mResourcesCfg = "resources.cfg";
   // mPluginsCfg = "plugins.cfg";
//#endif

    if (!configureOgre())
        return;

    // Create application object
    //TutorialApplication app;
    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI  entra***");

    createGUI();
    Ogre::LogManager::getSingletonPtr()->logMessage("*** FIN CREATEGUI ***");

  //  MenuInicial mI = createGUI();

    mRoot->startRendering();

    // clean up
    destroyScene();

}
