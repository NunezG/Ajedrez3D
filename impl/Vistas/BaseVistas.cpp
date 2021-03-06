#include "../../headers/Vistas/BaseVistas.h"

BaseVistas::BaseVistas(ModeloVista* modeloV, std::string label):
    mInputManager(0),
    mMouse(0),
    mKeyboard(0)
  , sys(0)
  , modeloVista(modeloV)
  , mRoot(0)
{  

    std::cout   << "  INICIA OGRE " << std::endl;


    //INICIA OGRE
    // construct Ogre::Root : no plugins filename, no config filename, using a custom log filename
    mRoot = new Ogre::Root("", "", "LowLevelOgre.log");
    // mRoot =new Ogre::Root("plugins.cfg");
    std::cout   << "  INICIA OGRE2222 " << std::endl;

    // (esto reemplaza plugins.cfg)
    // A list of required plugins
    Ogre::StringVector required_plugins;
    required_plugins.push_back("GL RenderSystem");
    required_plugins.push_back("Octree & Terrain Scene Manager");


    std::cout   << "  INICIA OGRE 333" << std::endl;


    // List of plugins to load
    Ogre::StringVector plugins_toLoad;
    plugins_toLoad.push_back("RenderSystem_GL");
    plugins_toLoad.push_back("Plugin_OctreeSceneManager");


    std::cout   << "  INICIA OGRE444 " << std::endl;
Ogre::String PluginFolder = ("/usr/local/lib/OGRE/");

    // Load the OpenGL RenderSystem and the Octree SceneManager plugins
    for (Ogre::StringVector::iterator j = plugins_toLoad.begin(); j != plugins_toLoad.end(); j++)
    {
        std::cout   << " HAYPLUGIN: " << *j  << std::endl;

#ifdef _DEBUG
        std::cout   << "  INICIA OGREDEBUG" << std::endl;

        mRoot->loadPlugin(PluginFolder + *j + Ogre::String("_d"));
#else
        std::cout   << "  INICIA OGRE NODEBI" << std::endl;

        mRoot->loadPlugin(PluginFolder + *j);
#endif;
    }
    std::cout   << "  INICIA OGRE 555" << std::endl;

    // Check if the required plugins are installed and ready for use
    // If not: exit the application
    Ogre::Root::PluginInstanceList ip = mRoot->getInstalledPlugins();
    for (Ogre::StringVector::iterator j = required_plugins.begin(); j != required_plugins.end(); j++)
    {
        bool found = false;
        // try to find the required plugin in the current installed plugins
        for (Ogre::Root::PluginInstanceList::iterator k = ip.begin(); k != ip.end(); k++)
        {
            if ((*k)->getName() == *j)
            {
                found = true;
                break;
            }
        }
      //  if (!found)  // return false because a required plugin is not available
      //  {
      //      return false;
      //  }
    }

    std::cout   << "  INICIA OGRE 666" << std::endl;

    // Esto reemplaza resources.cfg
    //-------------------------------------------------------------------------------------
    // setup resources
    // Only add the minimally required resource locations to load up the Ogre head mesh
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/programs", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/scripts", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/textures", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/models", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/schemes", "FileSystem", "Schemes");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/imagesets", "FileSystem", "Imagesets");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/fonts", "FileSystem", "Fonts");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/layouts", "FileSystem", "Layouts");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/looknfeel", "FileSystem", "LookNFeel");



    std::cout   << "  CONFIGURAGRAFICOS " << std::endl;

    configuraGraficos("OpenGL");

    std::cout   << " FIN CONFIGURAGRAFICOS " << std::endl;

    mWindow = mRoot->initialise(true,label);
    



    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();



    //INICIA OIS
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem( pl );
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
    //Set initial mouse clipping size




    //INICIA CEGUI
    CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    //  CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
    sys = CEGUI::System::getSingletonPtr();
    CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

    // sys->getDefaultGUIContext().getMouseCursor().se

    //  getMouseCursor().setDefaultImage(sheet->getMouseCursor());



    // CEGUI::MouseCursor::getSingleton().setImage(sys->getDefaultMouseCursor());


    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet= wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    // sys->setGUISheet(sheet);
    sys->getDefaultGUIContext().setRootWindow( sheet );
    //CEGUI::System::getSingleton().getDefaultGUIContext.getrgetRenderer();

    //sys->getDefaultGUIContext().
    sheet->setMouseCursor("Vanilla-Images/MouseArrow");


    // CEGUI::System::getSingleton().getDefaultGUIContext().setDefault
    // CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage("Vanilla-Images/MouseArrow");

    // CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getImage()-


    sys->getDefaultGUIContext().getMouseCursor().setImage(sheet->getMouseCursor());

    windowResized();

    //sys->renderGUI();
    sys->getRenderer()->beginRendering();
}

BaseVistas::~BaseVistas()
{
    //Unattach OIS before window shutdown (very important under Linux)
    if( mInputManager )
    {
        mInputManager->destroyInputObject( mKeyboard );
        mInputManager->destroyInputObject( mMouse );
        OIS::InputManager::destroyInputSystem(mInputManager);
        mMouse = 0;
        mKeyboard = 0;
        mInputManager = 0;
    }
    
    CEGUI::OgreRenderer::destroySystem();
    
    if (mRoot )
    {
        mRoot->removeFrameListener(this);
        //mRoot->destroySceneManager(modelo->escenaAjedrez->mSceneMgr);
        //  modelo->escenaAjedrez->destruyeTablero();
        //  mRoot->destroySceneManager(mSceneMgr);
        delete mRoot;
        mRoot = NULL;
    }
    // delete mWindow;
    // mWindow = 0;
}

void BaseVistas::empieza()
{
    mRoot->startRendering();
}


//int BaseVistas::getFPS()
//{
//    Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();
//    return ((int)stats.lastFPS);
//}

//Adjust mouse clipping area
void BaseVistas::windowResized()
{
    unsigned int width, height, depth;
    int left, top;
    mWindow->getMetrics(width, height, depth, left, top);
    
    const OIS::MouseState &ms = mMouse->getMouseState();
    
    ms.width = width;
    ms.height = height;
}


bool BaseVistas::configuraGraficos(const char *desiredRenderer)
{
    //SETUP RESOURCES
    // Load resource paths from config file

    /*
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");
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
    


    */
    //CONFIGUREOPENGL
    Ogre::RenderSystem *renderSystem;
    bool ok = false;
    
    Ogre::RenderSystemList renderers =
            mRoot->getAvailableRenderers();
    
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
    if(!ok)
    {
        // We still don't have a renderer; pick
        // up the first one from the list
        renderSystem = *renderers.begin();
        std::cout   << "   RENDERER POR DEFECTO: "<<renderSystem->getName() << std::endl;
    }
   /*
    ALTERNATIVA, TEL VEZ ES MEJOR (MAS COMPRENSIBLE)
    //-------------------------------------------------------------------------------------
        // configure
        // Grab the OpenGL RenderSystem, or exit
        Ogre::RenderSystem* renderSystem = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
        if(!(renderSystem->getName() == "OpenGL Rendering Subsystem"))
        {
            return false; //No RenderSystem found
        }

        */

    //EN PRIÇNCIPIO NO HACE FALTA ESTA LINEA



    // Manually set some configuration options (optional)
 /*
    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
    }
   */
    renderSystem->setConfigOption("VSync", "No");
    renderSystem->setConfigOption("Full Screen", "No");
    renderSystem->setConfigOption("Video Mode", modeloVista->resolucion);

    /*
    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
    }
    */
    
    mRoot->setRenderSystem(renderSystem);



    return true;
}

bool BaseVistas::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();




    context.injectMouseButtonDown(CEGUI::MouseButton(id));
    //  sys->injectMouseButtonDown(convertButton(id));
    return true;
}

bool BaseVistas::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    CEGUI::MouseButton(buttonID);


    context.injectMouseButtonUp(CEGUI::MouseButton(id));
    // sys->injectMouseButtonUp(convertButton(id));
    return true;
}

bool BaseVistas::keyPressed( const OIS::KeyEvent &evt )
{
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    context.injectKeyDown(CEGUI::Key::Scan(evt.key));
    context.injectChar(evt.text);

    if (evt.key == OIS::KC_ESCAPE)// Pulsa Esc
    {
        mWindow->setVisible(false);
        modeloVista->setApagar(true);
    }
    else if (evt.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        // mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    return true;
}

bool BaseVistas::keyReleased( const OIS::KeyEvent &arg )
{
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    context.injectKeyUp(CEGUI::Key::Scan(arg.key));
    return true;
}

bool BaseVistas::mouseMoved( const OIS::MouseEvent &evt )
{



    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    std::cout  << "X REL: " <<evt.state.X.rel <<std::endl;
    std::cout  << "Y REL: " <<evt.state.Y.rel << std::endl;


    context.injectMouseMove(evt.state.X.rel, evt.state.Y.rel) ;


    return true;

}

CEGUI::MouseButton BaseVistas::convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
        
    case OIS::MB_Right:
        return CEGUI::RightButton;
        
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
        
    default:
        return CEGUI::LeftButton;
    }
}

bool BaseVistas::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed() || !mWindow->isVisible())
        return false;
    
    sys->injectTimePulse(evt.timeSinceLastFrame);
    sys->getDefaultGUIContext().injectTimePulse(evt.timeSinceLastFrame);


    // sys->getDefaultGUIContext().updateWindowContainingMouse();
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
    
    return true;
}
