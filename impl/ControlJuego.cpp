
#include "../headers/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego()

{
}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{
    std::cout << "destructor control juego"<< std::endl;

}

void ControlJuego::inicio(void){


  Ventana& mFrameListener = Ventana::getCEGUISingleton();
   std::cout << "addFrameListener"<< std::endl;

    Ogre::Root::getSingletonPtr()->addFrameListener(this);
std::cout << "iniciaIO"<< std::endl;




EscenaAjedrez EscAjedrez;

std::cout << "createScene"<< std::endl;

EscAjedrez.createScene(mSceneMgr);


    mFrameListener.EmpiezaCEGUI();

    std::cout << "EscAjedrez"<< std::endl;


    std::cout << "MuestraMenu"<< std::endl;


  //  mFrameListener.MuestraMenu();

    std::cout << "acaba MuestraMenu"<< std::endl;



}


ControlJuego& ControlJuego::getControlSingleton()
{
static ControlJuego miControlJuego_;
return miControlJuego_;
}




//-------------------------------------------------------------------------------------
bool ControlJuego::setupMenu(void)
{

    // Create the scene

  //  createMainMenu();

  //  createGUI();




    return true;
}





void ControlJuego::cambiaPantalla(){

    //TutorialApplication ta;
    tut= new TutorialApplication(mSceneMgr);

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




    std::cout << "frameRenderingQueued " << std::endl;


Ventana& mFrameListener = Ventana::getCEGUISingleton();



    if(mFrameListener.getVentana()->isClosed()){

        std::cout << "VENTANA CERRADA!!!!!!!!!!!" << std::endl;

        return false;

    }


   if(!mFrameListener.getVentana()->isVisible()){
       std::cout << "BOTON CERRAR PULSADO EN CERRADA!!!!!!!!!!!" << std::endl;
        return false;
}

   if(mFrameListener.mShutDown){
       std::cout << "BOTON CERRAR PULSADO A TRAVES DE mShutDown!!!!!!!!!!!" << std::endl;
        return false;
}




    //Need to capture/update each device
    mFrameListener.capture();
    std::cout << "mFrameListener33333333333333 " << std::endl;


    mFrameListener.statUpdate(evt);

    return true;


    //return  BaseApplication::frameRenderingQueued(evt);

}




bool ControlJuego::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //  mTrayMgr->showCursor();
    //if (mTrayMgr->injectMouseUp(arg, id)) return true;

 //   Ventana& mFrameListener = Ventana::getCEGUISingleton();
 //   mFrameListener.mouseReleased(arg,id);

  //  if(mFrameListener.mPantalla==1)
 //   {
   //     if(tut==NULL){
   //         cambiaPantalla();

   //     }

    //    tut->mouseReleased(arg,id);


 //   }

    // mInputMan->injectMouseUp(arg, id);
    return true;
}

bool ControlJuego::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    std::cout << "BaseJuego MOUSEPRESSED " << std::endl;


    //Ventana& mFrameListener = Ventana::getCEGUISingleton();
    // TutorialApplication* tut;

  //  mFrameListener.mousePressed(arg,id);




  //  if(mFrameListener.mPantalla==1)
   // {
  //      std::cout << "mPantalla 1 " << std::endl;

   //     tut->mousePressed(arg, id);


  //  }

    //  mTrayMgr->hideCursor();
    // if (mTrayMgr->injectMouseDown(arg, id)) return true;
    // mInputMan->injectMouseDown(arg, id);
    return true;
}



bool ControlJuego::mouseMoved( const OIS::MouseEvent &arg )
{
    std::cout << "mouseMoved en CONTROLJUEGO " << std::endl;


   // Ventana& mFrameListener = Ventana::getCEGUISingleton();

  //  mFrameListener.mouseMoved(arg);

 //   if(mFrameListener.mPantalla==1)
 //   {

      //  tut->mouseMoved(arg);

 //   }

    return true;

}


//-------------------------------------------------------------------------------------
bool ControlJuego::keyPressed( const OIS::KeyEvent &arg )
{

   // Ventana& mFrameListener = Ventana::getCEGUISingleton();

 //   if(mFrameListener.mPantalla==1)
 //   {

   //     tut->keyPressed(arg);

 //   }

 //   mFrameListener.keyPressed(arg);





    return true;
}

bool ControlJuego::keyReleased( const OIS::KeyEvent &arg )
{

  //  Ventana& mFrameListener = Ventana::getCEGUISingleton();

  //  if(mFrameListener.mPantalla==1)
  //  {

   //     tut->keyReleased(arg);

  //  }

  //  mFrameListener.keyReleased(arg);

    return true;
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
