#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <OIS.h>
#include <iostream>
#include <Ogre.h>

class CEGUIFrameListener //: public OIS::KeyListener, public OIS::MouseListener
{
public:
  CEGUIFrameListener(Ogre::RenderWindow* mWindow);

  bool EmpiezaCEGUI(Ogre::RenderWindow* mWindow);


  //virtual ~CEGUIFrameListener(void);

//bool quit(const CEGUI::EventArgs &e);

bool keyPressed(const OIS::KeyEvent& evt);

bool keyReleased(const OIS::KeyEvent& evt);

bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

bool mouseMoved( const OIS::MouseEvent &arg );


void iniciaCEGUI();


bool injectTimePulse(const Ogre::FrameEvent& evt);

// CEGUI::System* mGUISystem;
CEGUI::Window *sheet;

CEGUI::System* sys;

private:


CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);




};
