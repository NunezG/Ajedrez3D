#include "../headers/CEGUIFrameListener.h"



CEGUIFrameListener::CEGUIFrameListener(Ogre::RenderWindow* mWindow)
{
    std::cout << "CONSTRUCTOR CEGUI" << std::endl;

    EmpiezaCEGUI(mWindow);
}






bool CEGUIFrameListener::EmpiezaCEGUI(Ogre::RenderWindow* mWindow)
{

    // Bootstrap CEGUI::System with an OgreRenderer object that uses the
    // default Ogre rendering window as the default output surface, an Ogre based
    // ResourceProvider, and an Ogre based ImageCodec.
    CEGUI::OgreRenderer& myRenderer  = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);


    // mFrameListener. = new CEGUIFrameListener();

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

  //  std::cout << "EMPIEZA CEGUIFRAMELISTENER" << std::endl;
//  createGUI();
  //  std::cout << "acaba createGUI" << std::endl;

    return true;
}




bool CEGUIFrameListener::injectTimePulse(const Ogre::FrameEvent& evt)
{

sys->injectTimePulse(evt.timeSinceLastFrame);

}

 //bool CEGUIFrameListener::quit(const CEGUI::EventArgs &e)
//{
 // _quit = true;
 // return true;
//}

 bool CEGUIFrameListener::keyPressed(const OIS::KeyEvent& evt)
{

     std::cout << "CEGUIFrameListener KEYPRESSED " << std::endl;

   //  CEGUI::System *sys = CEGUI::System::getSingletonPtr();
     sys->injectKeyDown(evt.key);
     sys->injectChar(evt.text);
     return true;

}

 bool CEGUIFrameListener::keyReleased(const OIS::KeyEvent& evt)
{
     sys->injectKeyUp(evt.key);
     return true;


}

 bool CEGUIFrameListener::mouseMoved( const OIS::MouseEvent &arg )
 {
 //mFrameListener->mouseMoved(arg,id);



     sys->injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
     // Scroll wheel.
     if (arg.state.Z.rel)
         sys->injectMouseWheelChange(arg.state.Z.rel / 120.0f);




     return true;

 }


 bool CEGUIFrameListener::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
     std::cout << "CEGUIFrameListener MOUSEPRESSED"  << std::endl;

     if(sys->injectMouseButtonDown(convertButton(id)))
     {
         std::cout << "HA SIDO PROCESADO CORRECTAMENTE EN CEGUI " << std::endl;
         return true;
 }else  std::cout << "NO HA SIDO PROCESADO " << std::endl;
  return true;
}

 bool CEGUIFrameListener::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{


      std::cout << "mouseReleased de CEGUIFrameListener"  << std::endl;
     sys->injectMouseButtonUp(convertButton(id));
  return true;
}

 CEGUI::MouseButton CEGUIFrameListener::convertButton(OIS::MouseButtonID buttonID)
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


















