#include "../../headers/Vistas/BaseVistas.h"

BaseVistas::BaseVistas(ModeloVista* modeloV, std::string label):
mInputManager(0),
    mMouse(0),
    mKeyboard(0)
  , sys(0)
  , modeloVista(modeloV)
  , mRoot(0)

  //modoJuego(0)
{  
    //  modelo = Modelo::getSingletonPtr();

    //escena = modeloV->escena;

  //  modeloVista = modeloV;


    //ENCIENDE
    mRoot =new Ogre::Root("plugins.cfg");

    Ogre::LogManager::getSingletonPtr()->logMessage("***CONFIGURA GRAFICOS**");

    configuraGraficos("OpenGL");

    mWindow = mRoot->initialise(true,label);
    //  mWindow = mRoot->initialise(true,label);

    // *renderer = myRenderer;

    CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);


    iniciaOIS();


    //  CEGUIResources();

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


    // iniciaCEGUI();

    //  myRenderer  = CEGUI  ::OgreRenderer::bootstrapSystem(*mWindow);





    // iniciaVentana();
}



BaseVistas::~BaseVistas()
{



    std::cout << "destroy cegu o gre system"<< std::endl;
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



Ogre::RenderWindow* BaseVistas::getVentana()
{
    return mWindow;
}





bool BaseVistas::CEGUIResources()
{


    return true;
}




bool BaseVistas::iniciaCEGUI()
{

    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

    CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");


    sys = CEGUI::System::getSingletonPtr();

    CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");

    CEGUI::System::getSingleton().setDefaultMouseCursor("Vanilla-Images", "MouseArrow");

    CEGUI::MouseCursor::getSingleton().setImage(sys->getDefaultMouseCursor());



    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet= wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    //  CEGUI::System* sys = CEGUI::System::getSingletonPtr();
    sys->setGUISheet(sheet);
    sys->renderGUI();
    //BaseVistas::iniciaVentana();

    return true;
}


void BaseVistas::capture()
{
    //Need to capture/update each device
    mKeyboard->capture();

    mMouse->capture();

}

int BaseVistas::getFPS()
{
    Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();
    return ((int)stats.lastFPS);
}

bool BaseVistas::iniciaOIS()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("***INICIAVENTAAN EN BASE**");

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
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing 4");


    //Set initial mouse clipping size
    windowResized();

    Ogre::LogManager::getSingletonPtr()->logMessage("*** sale de inicio IOS");

    // Bootstrap CEGUI::System with an OgreRenderer object that uses the
    // default Ogre rendering window as the default output surface, an Ogre based
    // ResourceProvider, and an Ogre based ImageCodec.
    //  CEGUI::OgreRenderer& myRenderer  = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);

    return true;
}


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

//Unattach OIS before window shutdown (very important under Linux)
void BaseVistas::windowClosed()
{

    std::cout << "windowclosed"<< std::endl;

    if( mInputManager )
    {
        mInputManager->destroyInputObject( mKeyboard );

        mInputManager->destroyInputObject( mMouse );



        OIS::InputManager::destroyInputSystem(mInputManager);


        // delete mKeyboard;
        //delete mMouse;
        // delete mInputManager;
        mMouse = 0;
        mKeyboard = 0;
        mInputManager = 0;

    }


    std::cout << "sale"<< std::endl;

}

bool BaseVistas::configuraGraficos(const char *desiredRenderer)
{

    //SETUP RESOURCES
    // Load resource paths from config file
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

    Ogre::LogManager::getSingletonPtr()->logMessage("***CONFIGURA GRAAAAAAAAAAAAA**");

    //CONFIGUREOPENGL
    Ogre::RenderSystem *renderSystem;
    bool ok = false;

    Ogre::RenderSystemList renderers =
            Ogre::Root::getSingleton().getAvailableRenderers();

    // See if the list is empty (no renderers available)
    if(renderers.empty())
    {
        return false;

    }

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
    }
    Ogre::Root::getSingleton().setRenderSystem(renderSystem);
    // Manually set some configuration options (optional)

    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {

        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;

    }

    renderSystem->setConfigOption("Full Screen", "No");

    renderSystem->setConfigOption("Video Mode", modeloVista->resolucion);

    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
        // std::cout << "LAS OPCIONES: " <<CO.first<<" " <<CO.second.currentValue << std::endl;
    }

    //  std::cout << " SALE DE GRAFICOS" << std::endl;


    return true;
}




bool BaseVistas::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{


    sys->injectMouseButtonDown(convertButton(id));


}



bool BaseVistas::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{


    sys->injectMouseButtonUp(convertButton(id));


}


bool BaseVistas::keyPressed( const OIS::KeyEvent &evt )
{



    sys->injectKeyDown(evt.key);
    sys->injectChar(evt.text);



    if (evt.key == OIS::KC_ESCAPE)// Pulsa Esc
    {
        modeloVista->setSalir(true);
        mWindow->setVisible(false);
        modeloVista->setApagar(true);
    }
    else if (evt.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        // mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }

}

bool BaseVistas::keyReleased( const OIS::KeyEvent &arg )
{



    sys->injectKeyUp(arg.key);







}

bool BaseVistas::mouseMoved( const OIS::MouseEvent &evt )
{



    sys->injectMouseMove(evt.state.X.rel, evt.state.Y.rel);



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

    if(mWindow->isClosed() || !mWindow->isVisible()/*|| EscenaAjedrez->getSalir()*/)
    {
        //std::cout << "VENTANA CERRADA"<< std::endl;
        // shutdown = true;
        return false;
    }

    sys->injectTimePulse(evt.timeSinceLastFrame);


    capture();


    return true;
}
