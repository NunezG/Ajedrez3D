#include "../../headers/Control/BaseJuego.h"

//-------------------------------------------------------------------------------------
BaseJuego::BaseJuego(void)//: mSceneMgr(mSceneMgr)

    //mPluginsCfg("plugins.cfg"),
   // mResourcesCfg("resources.cfg")
{

 //   modelo = Modelo::getSingletonPtr();
}
//-------------------------------------------------------------------------------------
BaseJuego::~BaseJuego(void)
{
   // delete mRoot;
}

///////////////////////////////////////////////////////////////////////////////////////7

//-------------------------------------------------------------------------------------
bool BaseJuego::configureOpenGL()
{
    if(configuraGraficos("OpenGL"))
    {
        punteroVentana->iniciaVentana();

        return true;
    }
    else
    {
        return false;
    }
}

void BaseJuego::inicio(void){

    modelo->construyeMenu();

    Ogre::Root::getSingletonPtr()->addFrameListener(this);
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

    punteroVentana->EmpiezaCEGUI();
    punteroVentana->MuestraMenu();

    //punteroVentana->iniciaVista();
    // iniciaModeloAjedrez();


}

bool BaseJuego::configuraGraficos(const char *desiredRenderer)
{
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

    }

    renderSystem->setConfigOption("Full Screen", "No");
    renderSystem->setConfigOption("Video Mode", "1920 x 1080");

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
    setupResources();

    bool carryOn = configureOpenGL();
    if (!carryOn) return false;

    // Load resources
    loadResources();

    punteroVentana->iniciaIO();

    return true;
}

//-------------------------------------------------------------------------------------
bool BaseJuego::setup(void)
{
    return true;
}

void BaseJuego::destroyScene(void)
{

    std::cout << "destruyemenu"<< std::endl;


  //  if modelo->   modelo->destruyeMenu();

    std::cout << "destruyetablero"<< std::endl;

    std::cout << "modelo->getTablero()"<<modelo->getTablero()<< std::endl;

    if (modelo->getTablero()) modelo->destruyeTablero();

    std::cout << "nullea mod " << std::endl;

    modelo = NULL;

    std::cout << "delete roor " << std::endl;

    //delete mRoot;
    std::cout << "nullea " << std::endl;

    mTimer = NULL;
    std::cout << "nullea " << std::endl;

    if (mRoot)
     mRoot->removeFrameListener(this);

    mRoot = NULL;
    std::cout << "puntventana"<< std::endl;

    delete punteroVentana;
    std::cout << "nullea " << std::endl;

    punteroVentana = NULL;

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
    cf.load(modelo->mResourcesCfg);
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
void BaseJuego::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

//-------------------------------------------------------------------------------------
void BaseJuego::go(void)
{
    modelo = Modelo::getSingletonPtr();

    mRoot =new Ogre::Root(modelo->mPluginsCfg);
    mTimer = mRoot->getTimer();
    punteroVentana = new Ventana();

    if (!configureOgre())
        return;

    inicio();

    mRoot->startRendering();



    // clean up (despues de ejeucion)
    destroyScene();
}
