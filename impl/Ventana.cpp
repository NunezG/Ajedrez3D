#include "../headers/Ventana.h"



Ventana::Ventana() :
    mLastStatUpdateTime(0),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mPantalla(0),
    sys(0),
    mRoot(Ogre::Root::getSingletonPtr()),
    mTimer(mRoot->getTimer()),
    mSceneMgr(0),
    tut(0)


{
    // Ventana* Ventana::miFrameListener = 0;// Inicializar el puntero
    std::cout << "constructor ventana"<< std::endl;

    //mTimer = mRoot->getTimer();
}
Ventana::~Ventana()
{
    // Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();

    // Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();

    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

    windowClosed(mWindow);

}



Ventana& Ventana::getCEGUISingleton()
{
    static Ventana miFrameListener;
    return miFrameListener;
}

Ogre::RenderWindow* Ventana::getVentana(){
    //  Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
    return mWindow;

}



void Ventana::capture(){

    //  std::cout << "capture" << std::endl;
    mMouse->capture();


    //  std::cout << "capture 2" << std::endl;

    mKeyboard->capture();

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

    //  std::cout << "currentTime:  "<< currentTime <<std::endl;


    if (areFrameStatsVisible() && currentTime - mLastStatUpdateTime > 250)
    {
        //       std::cout << "entr aen el IF:  "<< currentTime <<std::endl;


        //  Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();

        // Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();

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
void Ventana::iniciaIO(void)
{
    std::cout << "iniciaIO "<<std::endl;
    //   Ventana* mFrameListener;


    std::cout << "mWindow   "<<std::endl;

    //  mWindow = mRoot->getAutoCreatedWindow();

    std::cout << "Initializing OIS  "<<std::endl;

    //  mFrameListener..empie
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OISpuntero ***");
    std::cout << "Initializing OIS222222222222  "<<std::endl;

    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));


    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing mInputManager ***");
    std::cout << "Initializing mInputManager  "<<std::endl;

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);


    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);





    std::cout << "FIN Initializing OIS  "<<std::endl;
    Ogre::LogManager::getSingletonPtr()->logMessage("***FIN  Initializing OISpuntero ***");




    //Set initial mouse clipping size


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


//Unattach OIS before window shutdown (very important under Linux)
void Ventana::windowClosed(Ogre::RenderWindow* rw)
{

    // Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
    //  Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();

    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        std::cout << "if windowClosed"<< std::endl;

        if( mInputManager )
        {
            std::cout << "if mInputManager"<< std::endl;

            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}



//Adjust mouse clipping area
void Ventana::windowResized(Ogre::RenderWindow* rw)
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


    ms.width = width;
    ms.height = height;
    std::cout << "test "<<std::endl;
    std::cout << "ms.width "<< ms.width <<std::endl;
    std::cout << "ms.height  "<< ms.height <<std::endl;



}




bool Ventana::iniciaVentana(){
    // mRoot = Ogre::Root::getSingletonPtr();
    mWindow = mRoot->initialise(true, "Ajedrez OpenGL");
    return true;
}

bool Ventana::EmpiezaCEGUI(/*Ogre::RenderWindow* mWindow*/)
{
    std::cout << "EmpiezaCEGUI "<< std::endl;



    //  iniciaVentana();


    // Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();

    //  Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();


    // mWindow = mRoot->getAutoCreatedWindow();

    // Bootstrap CEGUI::System with an OgreRenderer object that uses the
    // default Ogre rendering window as the default output surface, an Ogre based
    // ResourceProvider, and an Ogre based ImageCodec.
    CEGUI::OgreRenderer& myRenderer  = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);


    // mFrameListener. = new Ventana();

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

    std::cout << "acaba createGUI " <<std::endl;
    //  std::cout << "EMPIEZA Ventana" << std::endl;
    //createGUI();
    //  std::cout << "acaba createGUI" << std::endl;


    //   std::cout << "nombre mRoot "<< <<std::endl;




    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");
    // EscenaAjedrez EscAjedrez;
    // EscAjedrez.createScene(mSceneMgr);

    return true;
}




bool Ventana::injectTimePulse(const Ogre::FrameEvent& evt)
{

    sys->injectTimePulse(evt.timeSinceLastFrame);

}

//bool Ventana::quit(const CEGUI::EventArgs &e)
//{
// _quit = true;
// return true;
//}



int Ventana::pantallaActual(){
    if (tut==NULL){
        return 0;

    }else return 1;

}


bool Ventana::MuestraMenu(){

    //sys = CEGUI::System::getSingletonPtr();
    menu = new MenuInicio();
    std::cout << "inicia createGUI " << std::endl;

    CEGUI::FrameWindow* fwdw = menu->createGUI();
    std::cout << "acaba createGUI " << std::endl;

    sys->getGUISheet()->addChildWindow( fwdw );
    std::cout << "acaba createGUI GUAYYY" << std::endl;



}




bool Ventana::keyPressed(const OIS::KeyEvent& evt)
{

    // Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
    // Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();

    std::cout << "Ventana KEYPRESSED " << std::endl;


    if(mPantalla == 1){


        tut->keyPressed(evt);
    }



    //  CEGUI::System *sys = CEGUI::System::getSingletonPtr();
    sys->injectKeyDown(evt.key);
    sys->injectChar(evt.text);


    if (evt.key == OIS::KC_ESCAPE)
    {
        std::cout << "PULSA ESCAPE"<< std::endl;
        mShutDown = true;
        return true;
    }else if (evt.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }



    return true;

}

bool Ventana::keyReleased(const OIS::KeyEvent& evt)
{
    //  Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
    //  Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();

    if(mPantalla == 1){


        tut->keyReleased(evt);
    }



    sys->injectKeyUp(evt.key);





    return true;


}

bool Ventana::mouseMoved( const OIS::MouseEvent &evt )
{
    //mFrameListener->mouseMoved(arg,id);


    if(mPantalla == 1){


        tut->mouseMoved(evt);
    }


    sys->injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
    // Scroll wheel.
    if (evt.state.Z.rel)
        sys->injectMouseWheelChange(evt.state.Z.rel / 120.0f);




    return true;

}

int Ventana::getFPS(){
    Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();
    return ((int)stats.lastFPS);

}



//-------------------------------------------------------------------------------------
bool Ventana::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    /*
    if(mWindow->isClosed())
        return false;

    if(mFrameListener->mShutDown)
        return false;

    */
 //   std::cout << "frameRenderingQueued en framelistener" << std::endl;

    injectTimePulse(evt);
    capture();
    statUpdate(evt);

    if(mPantalla == 1 && tut != NULL){
        std::cout << "frameRenderingQueued en framelistener TUTORIALAPP" << std::endl;

        tut->frameRenderingQueued(evt);
    }


}

bool Ventana::muestraAjedrez()
{

    //    VistaAjedrez ta;
    tut= new VistaAjedrez(mSceneMgr, mWindow);

    std::cout << "CAMBIA LA PANTALLAAAAAAAAAAAAAAAAAAAAAAz" << std::endl;

    //  createViewports();

    // Create the scene
    //   createScene();

    tut->setupJuego();




}

bool Ventana::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{

    if(mPantalla == 1){


        tut->mousePressed(evt, id);
        std::cout << "ACABA MOUSEPRESSED DE VENTANA " << std::endl;

        // mInputMan->injectMouseDown(evt, id);
    }



    std::cout << " MOUSEPRESSED en Ventana"  << std::endl;

    if(sys->injectMouseButtonDown(convertButton(id)))
    {
         std::cout << " MOUSEPRESSED en PROCSADO SI O SI"  << std::endl;
        return true;
    }else  std::cout << "NO HA SIDO PROCESADO " << std::endl;



    return true;
}




bool Ventana::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{

    if(mPantalla == 1){


        tut->mouseReleased(evt, id);
    }

    std::cout << "mouseReleased de Ventana"  << std::endl;
    sys->injectMouseButtonUp(convertButton(id));


    //  std::cout << "HA SIDO PROCESADO CORRECTAMENTE EN CEGUI " << std::endl;

    if(mPantalla == 0){
        if(menu->salirPulsado){
            std::cout << "BOTOTON SALIR PULSADO!! " << std::endl;
            mShutDown = true;
            std::cout << "setvisible!! " << std::endl;

            // mWindow->setVisible(false);
        }else if (sys->getGUISheet()->isVisible()==true && menu->modoJuego == 1){
            std::cout << "CAMBIO PANTALLA" << std::endl;

            sys->getGUISheet()->setVisible(false);
            mPantalla = 1;
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
