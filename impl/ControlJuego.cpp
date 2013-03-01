
#include "../headers/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego(),
    mLastStatUpdateTime(0)

{
}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{
    windowClosed(mWindow);

}

void ControlJuego::inicio(void){



    EscenaAjedrez EscAjedrez;

    EscAjedrez.createScene(mSceneMgr);

    MenuInicio* menu = new MenuInicio(mFrameListener);
    menu->createGUI();


}


ControlJuego& ControlJuego::getControlSingleton()
{
static ControlJuego miControlJuego_;
return miControlJuego_;
}



void ControlJuego::createMainMenu(void)
{

    // mSceneMgr->getRootSceneNode()->addChild(nodo1);
    std::cout  << "Gestion del overlay2" << std::endl;

    //   mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
    std::cout  << "Gestion del overla22y" << std::endl;
    // Ogre::Overlay *overlay = mOverlayManager->getByName("Menu");
    std::cout  << "Gestion del overla33" << std::endl;
    // Ogre::OverlayElement* cont = mOverlayManager->getOverlayElement("instrucciones");
    // cont->setCaption("PRUEBA DE OVERLAY");
    //  overlay->show();

    std::cout  << "Gestion del overlay" << std::endl;
    // Gestion del overlay ---------------------------------------------
    //    Ogre::OverlayElement *oe;

    //    mOverlayManager-> hasOverlayElement("JuegoSolitario");
    //  oe = mOverlayManager->getOverlayElement("JuegoSolitario");
    //  oe->setCaption(textoOverlay);


    //    oe = mOverlayManager->getOverlayElement("JuegoTurnos");
    //   oe->setCaption("CAPTIOOON");

    std::cout  << "fin Gestion del overlay" << std::endl;

}


//-------------------------------------------------------------------------------------
bool ControlJuego::setupMenu(void)
{

    // Create the scene

    createMainMenu();

  //  createGUI();




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
bool ControlJuego::statUpdate(const Ogre::FrameEvent& evt)
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




void ControlJuego::cambiaPantalla(){

    //TutorialApplication ta;
    tut= new TutorialApplication(mSceneMgr,mWindow);

    std::cout << "CAMBIA LA PANTALLAAAAAAAAAAAAAAAAAAAAAAz" << std::endl;

    //  createViewports();

    // Create the scene
    //   createScene();

    tut->setupJuego();


tut->createScene();

}




//-------------------------------------------------------------------------------------
bool ControlJuego::frameRenderingQueued(const Ogre::FrameEvent& evt)
{


    mFrameListener->injectTimePulse(evt);

    if(mWindow->isClosed())
        return false;

    if(mFrameListener->mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    statUpdate(evt);

    return true;


    //return  BaseApplication::frameRenderingQueued(evt);

}




bool ControlJuego::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //  mTrayMgr->showCursor();
    //if (mTrayMgr->injectMouseUp(arg, id)) return true;
    mFrameListener->mouseReleased(arg,id);

    if(mFrameListener->mPantalla==1)
    {
        if(tut==NULL){
            cambiaPantalla();

        }

        tut->mouseReleased(arg,id);


    }

    // mInputMan->injectMouseUp(arg, id);
    return true;
}

bool ControlJuego::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    std::cout << "BaseJuego MOUSEPRESSED " << std::endl;


    // TutorialApplication* tut;

    mFrameListener->mousePressed(arg,id);




    if(mFrameListener->mPantalla==1)
    {
        std::cout << "mPantalla 1 " << std::endl;

        tut->mousePressed(arg, id);


    }

    //  mTrayMgr->hideCursor();
    // if (mTrayMgr->injectMouseDown(arg, id)) return true;
    // mInputMan->injectMouseDown(arg, id);
    return true;
}



bool ControlJuego::mouseMoved( const OIS::MouseEvent &arg )
{

    mFrameListener->mouseMoved(arg);

    if(mFrameListener->mPantalla==1)
    {

        tut->mouseMoved(arg);

    }

    return true;

}


//-------------------------------------------------------------------------------------
bool ControlJuego::keyPressed( const OIS::KeyEvent &arg )
{



    if (arg.key == OIS::KC_ESCAPE)
    {
        mFrameListener->mShutDown = true;
        return true;
    }else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }





    if(mFrameListener->mPantalla==1)
    {

        tut->keyPressed(arg);

    }

    mFrameListener->keyPressed(arg);





    return true;
}

bool ControlJuego::keyReleased( const OIS::KeyEvent &arg )
{


    if(mFrameListener->mPantalla==1)
    {

        tut->keyReleased(arg);

    }

    mFrameListener->keyReleased(arg);

    return true;
}




//Unattach OIS before window shutdown (very important under Linux)
void ControlJuego::windowClosed(Ogre::RenderWindow* rw)
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



//void BaseJuego::creaTablero(void)
//{



//   EscenaAjedrez EscAjedrez;

//  EscAjedrez.createScene(mSceneMgr);

// TutorialApplication ta;



//}

//void BaseJuego::createGUI(void){



//  if(mPantalla==0){

//    TutorialApplication tut;



//    }

//}





/* void BaseJuego::createOverlay() {
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
