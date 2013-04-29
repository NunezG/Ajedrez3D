#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana() :
    mLastStatUpdateTime(0),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mPantalla(0),
    sys(0),
    mRoot(Ogre::Root::getSingletonPtr()),
    mTimer(mRoot->getTimer()),
  //  mSceneMgr(0),
    vista(NULL),
    capturaRaton(true)
{
    modelo = Modelo::getSingletonPtr();

}

Ventana::~Ventana()
{
    std::cout << "vista"<< std::endl;

    delete vista;
    std::cout << "fin"<< std::endl;
    vista = NULL;
    std::cout << "remove"<< std::endl;

    windowClosed(mWindow);

    std::cout << "listenre"<< std::endl;

    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);


    std::cout << "detach"<< std::endl;

    mRoot->detachRenderTarget(mWindow);
    std::cout << "framelis"<< std::endl;




    std::cout << "end"<< std::endl;

}

Ogre::RenderWindow* Ventana::getVentana(){
    return mWindow;
}

void Ventana::capture(){
    //Need to capture/update each device
    mMouse->capture();
}

bool areFrameStatsVisible()
{
    return true;//mFpsLabel != 0;
}

/*-----------------------------------------------------------------------------
| Process frame events. Updates frame statistics widget set and deletes
| all widgets queued for destruction.
-----------------------------------------------------------------------------*/
bool Ventana::statUpdate(const Ogre::FrameEvent& evt)
{
    unsigned long currentTime = mTimer->getMilliseconds();

    if (areFrameStatsVisible() && currentTime - mLastStatUpdateTime > 250)
    {
        Ogre::String s("FPS: "+ getFPS());
    }
    return true;
}

//-------------------------------------------------------------------------------------
void Ventana::iniciaIO(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing mInputManager ***");

    mInputManager = OIS::InputManager::createInputSystem( pl );
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    Ogre::LogManager::getSingletonPtr()->logMessage("***FIN  Initializing OISpuntero ***");
}


//Unattach OIS before window shutdown (very important under Linux)
void Ventana::windowClosed(Ogre::RenderWindow* rw)
{      
    if( rw == mWindow )
    {
        std::cout << "windowclosed"<< std::endl;

        if( mInputManager )
        {
            std::cout << "destroy"<< std::endl;
            mInputManager->destroyInputObject( mKeyboard );
            std::cout << "destroy2"<< std::endl;

            mInputManager->destroyInputObject( mMouse );


            std::cout << "destroy 3"<< std::endl;

            OIS::InputManager::destroyInputSystem(mInputManager);
            std::cout << "destroy 4"<< std::endl;

            mInputManager = 0;
        }
    }
}

//Adjust mouse clipping area
void Ventana::windowResized(Ogre::RenderWindow* rw)
{    
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();

    ms.width = width;
    ms.height = height;
}

bool Ventana::iniciaVentana(){
    mWindow = mRoot->initialise(true, "Ajedrez OpenGL");
    return true;
}

bool Ventana::EmpiezaCEGUI()
{   
    // Bootstrap CEGUI::System with an OgreRenderer object that uses the
    // default Ogre rendering window as the default output surface, an Ogre based
    // ResourceProvider, and an Ogre based ImageCodec.
    CEGUI::OgreRenderer& myRenderer  = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);

    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

    // CEGUI::SchemeManager::getSingleton().loadScheme( (CEGUI::utf8*)"TaharezLook.scheme");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

    sys = CEGUI::System::getSingletonPtr();

    sys->setDefaultFont("DejaVuSans-10");
    sys->setDefaultMouseCursor("TaharezLook", "MouseArrow");

    CEGUI::MouseCursor::getSingleton().setImage(sys->getDefaultMouseCursor());

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    sys->setGUISheet(sheet);

    sys->renderGUI();
    Ogre::LogManager::getSingletonPtr()->logMessage("*** ACABA GUI***");



    return true;
}

bool Ventana::injectTimePulse(const Ogre::FrameEvent& evt)
{   
    sys->injectTimePulse(evt.timeSinceLastFrame);
}

int Ventana::pantallaActual(){
    if (vista->esMenuInicio()){

        return 0;

    }else return 1;

}

bool Ventana::MuestraMenu(){

    vista = new MenuInicio();
}

bool Ventana::keyPressed(const OIS::KeyEvent& evt)
{   
    if(mPantalla > 0){
        vista->keyPressed(evt);
    }

    sys->injectKeyDown(evt.key);
    sys->injectChar(evt.text);

    if (evt.key == OIS::KC_ESCAPE)// Pulsa Esc
    {
        modelo->setSalir(true);
    }else if (evt.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }

    return true;
}

bool Ventana::keyReleased(const OIS::KeyEvent& evt)
{
    if(mPantalla > 0){
        vista->keyReleased(evt);
    }

    sys->injectKeyUp(evt.key);

    return true;
}

bool Ventana::mouseMoved( const OIS::MouseEvent &evt )
{   

    sys->injectMouseMove(evt.state.X.rel, evt.state.Y.rel);



    if(mPantalla > 0)
    {


        vista->mouseMoved(evt);



        // Scroll wheel.
        if (evt.state.Z.rel)
            sys->injectMouseWheelChange(evt.state.Z.rel / 120.0f);
    }



    return true;
}

int Ventana::getFPS()
{
    Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();
    return ((int)stats.lastFPS);
}

//-------------------------------------------------------------------------------------
bool Ventana::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    injectTimePulse(evt);
    mKeyboard->capture();

    if (capturaRaton){
    capture();
    }
    statUpdate(evt);



    if(mPantalla > 0 && vista != NULL)
    {
        vista->frameRenderingQueued(evt);
    }
}


//BaseApplication* Ventana::Create(Ogre::String type) {
  //  if ( type == "JuegoPorTurnos" ) return  VistaAjedrez(mSceneMgr, mWindow);
 //   if ( type == "JuegoEnSolitario" ) return  VistaAjedrezSolo(mSceneMgr, mWindow);
  //  return NULL;
//}

bool Ventana::muestraAjedrez(/*EscenaAjedrez escenaAjedrez*/)
{
    delete vista;
    vista = NULL;
    if (mPantalla == 1)
    {
        vista= new VistaAjedrez();
    }
    else if (mPantalla == 2)
    {
        vista= new VistaAjedrezSolo();
    }
}

bool Ventana::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{

    std::cout << "mousePressed"<< std::endl;


    if(mPantalla > 0){
        vista->mousePressed(evt, id);
    }

    if(sys->injectMouseButtonDown(convertButton(id)))
    {
        return true;
    }

    return true;
}

bool Ventana::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    sys->injectMouseButtonUp(convertButton(id));

    if(mPantalla > 0)
    {
        vista->mouseReleased(evt, id);
    }
    else if(mPantalla == 0)
    {
        std::cout << "MOUSE RELEASED EN PANTALLA = 0 " << std::endl;

        if (sys->getGUISheet()->isVisible()==true && modelo->getNumPantalla() == 1)
        {
            std::cout << "PANTALLA 1 " << std::endl;

            sys->getGUISheet()->setVisible(false);
           mPantalla = 1;
        }
        else if (sys->getGUISheet()->isVisible()==true && modelo->getNumPantalla() == 2)
        {
            std::cout << "PANTALLA 2 " << std::endl;

            sys->getGUISheet()->setVisible(false);
            mPantalla = 2;
        }
    }
    return true;
}

CEGUI::MouseButton Ventana::convertButton(OIS::MouseButtonID buttonID)
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
