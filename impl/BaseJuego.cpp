#include "../headers/BaseJuego.h"



//-------------------------------------------------------------------------------------
BaseJuego::BaseJuego(void):
    mWindow(0),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mSceneMgr(0),
    mModoJuego(1),
    mRoot(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),


    tut(0)

  //mCursorWasVisible(false)

  //mCursor(0)


  //mRenderer(0)

{

}
//-------------------------------------------------------------------------------------
BaseJuego::~BaseJuego(void)
{

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    delete mRoot;
}

///////////////////////////////////////////////////////////////////////////////////////7

//-------------------------------------------------------------------------------------
bool BaseJuego::configureOpenGL(void)
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


bool BaseJuego::configuraGraficos(const char *desiredRenderer)
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

    renderSystem->setConfigOption("Video Mode", "1024 x 768");


    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
        std::cout << "LAS OPCIONES: " <<CO.first<<" " <<CO.second.currentValue << std::endl;
    }
    return true;

}


//Adjust mouse clipping area
void BaseJuego::windowResized(Ogre::RenderWindow* rw)
{
    std::cout << "WINDOWRESIZED "<< std::endl;


    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();


    std::cout << "width "<< width <<std::endl;
    std::cout << "height "<< height <<std::endl;
    std::cout << "depth "<< depth <<std::endl;

    std::cout << "left "<< left <<std::endl;
    std::cout << "top "<< top <<std::endl;


    std::cout << "ms.width "<< ms.width <<std::endl;
    std::cout << "ms.ms.height  "<< ms.height <<std::endl;




    ms.width = width;
    ms.height = height;
}


//-------------------------------------------------------------------------------------
void BaseJuego::iniciaIO(void)
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



//-------------------------------------------------------------------------------------
bool BaseJuego::configureOgre(void)
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


//-------------------------------------------------------------------------------------
bool BaseJuego::setup(void)
{

    return true;
}

void BaseJuego::destroyScene(void)
{
}


//-----------------------------------------------------------------------
//CONFIGURACION PREVIA A LA INICIALIZACION DE GRAFICOS
//-------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------
void BaseJuego::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}


//-------------------------------------------------------------------------------------
void BaseJuego::setupResources(void)
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
void BaseJuego::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void BaseJuego::loadResources(void)
{

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();



}


//-------------------------------------------------------------------------------------
void BaseJuego::go(void)
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

    inicio();
    Ogre::LogManager::getSingletonPtr()->logMessage("*** FIN CREATEGUI ***");

    //  MenuInicial mI = createGUI();

    mRoot->startRendering();

    // clean up
    destroyScene();

}
