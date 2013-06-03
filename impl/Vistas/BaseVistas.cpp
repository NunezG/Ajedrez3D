#include "../../headers/Vistas/BaseVistas.h"

BaseVistas::BaseVistas(ModeloVista* modeloV, Ogre::Root* mRoot, std::string label):
    modeloVista(modeloV)
    ,mInputManager(0),
    mMouse(0),
    mKeyboard(0)

    //modoJuego(0)
{  
  //  modelo = Modelo::getSingletonPtr();

    //escena = modeloV->escena;

    Ogre::LogManager::getSingletonPtr()->logMessage("***CONFIGURA GRAFICOS**");

    configuraGraficos("OpenGL");

    mWindow = mRoot->initialise(true,label);
  //  mWindow = mRoot->initialise(true,label);

   // *renderer = myRenderer;

    iniciaOIS();

    CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);


    Ogre::LogManager::getSingletonPtr()->logMessage("***boootrss**");

 //  myRenderer  = CEGUI  ::OgreRenderer::bootstrapSystem(*mWindow);

    Ogre::LogManager::getSingletonPtr()->logMessage("***CONFIGURA GRAFICOS**");

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet= wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    CEGUI::System* sys = CEGUI::System::getSingletonPtr();
    sys->setGUISheet(sheet);
    sys->renderGUI();

    Ogre::LogManager::getSingletonPtr()->logMessage("***ACABA**");

   // iniciaVentana();
}

BaseVistas::~BaseVistas()
{

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    wmgr.getWindow("MenuInicio/VentanaMenu")->setVisible(false);
    // wmgr.getWindow("Demo")->setVisible(false);

    wmgr.getWindow("MenuInicio")->setVisible(false);

    wmgr.destroyWindow("MenuInicio/VentanaMenu");
    wmgr.destroyWindow("MenuInicio");


    std::cout << "delete window"<< std::endl;
    CEGUI::OgreRenderer::destroySystem();


   // delete mWindow;
        std::cout << "delete window 2"<< std::endl;

   // mWindow = 0;
}

Ogre::RenderWindow* BaseVistas::getVentana()
{
    return mWindow;
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

    Ogre::LogManager::getSingletonPtr()->logMessage("*** sale de inicio cegui");

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
    if(renderers.empty()){



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



    if(!ok) {

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





