#include "../headers/BaseJuego.h"



//-------------------------------------------------------------------------------------
BaseJuego::BaseJuego(void):
    mPluginsCfg("plugins.cfg"),
    mResourcesCfg("resources.cfg")


{
    std::cout << "constructor base juego"<< std::endl;
    mRoot =new Ogre::Root(mPluginsCfg);
}
//-------------------------------------------------------------------------------------
BaseJuego::~BaseJuego(void)
{
    std::cout << "DESTRUCTOR BaseJuego "<< std::endl;

    //Remove ourself as a Window listener
    delete mRoot;
}

///////////////////////////////////////////////////////////////////////////////////////7

//-------------------------------------------------------------------------------------
bool BaseJuego::configureOpenGL()
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    //if(mRoot->showConfigDialog())

    Ventana& mFrameListener = Ventana::getCEGUISingleton();

    // Ventana& mFrameListener = Ventana::getCEGUISingleton();

    if(configuraGraficos("OpenGL"))
    {
        // Here we choose to let the system create a default rendering window by passing 'true'
        mFrameListener.iniciaVentana();

        return true;
    }
    else
    {
        return false;
    }
}


bool BaseJuego::configuraGraficos(const char *desiredRenderer)
{
    std::cout << "configuraGraficos: "<< std::endl;
    Ogre::RenderSystem *renderSystem;
    bool ok = false;
    Ogre::RenderSystemList renderers =
            Ogre::Root::getSingleton().getAvailableRenderers();

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

    Ogre::Root::getSingleton().setRenderSystem(renderSystem);

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


//-------------------------------------------------------------------------------------
bool BaseJuego::configureOgre(void)
{

    // mResourcesCfg = "resources.cfg";
    // mPluginsCfg = "plugins.cfg";

    //   mRoot = new Ogre::Root(mPluginsCfg);

    mTimer = Ogre::Root::getSingleton().getTimer();


    setupResources();

    Ventana& mFrameListener = Ventana::getCEGUISingleton();

    //  mFrameListener = new Ventana();
    bool carryOn = configureOpenGL();
    if (!carryOn) return false;


    //  chooseSceneManager();
    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    std::cout << "loadResources"<< std::endl;
    loadResources();
    std::cout << "getCEGUISingleton"<< std::endl;


    // Ventana& mFrameListener = Ventana::getCEGUISingleton();

    mFrameListener.iniciaIO();

    return true;
}


//-------------------------------------------------------------------------------------
bool BaseJuego::setup(void)
{

    return true;
}

void BaseJuego::destroyScene(void)
{
    std::cout << "destroyScene"<< std::endl;

}


//-----------------------------------------------------------------------
//CONFIGURACION PREVIA A LA INICIALIZACION DE GRAFICOS
//-------------------------------------------------------------------------------------

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
    //VistaAjedrez app;

    inicio();

    //  MenuInicial mI = createGUI();

    mRoot->startRendering();

    // clean up
    destroyScene();
    std::cout << "antes de acabar"<< std::endl;


}
