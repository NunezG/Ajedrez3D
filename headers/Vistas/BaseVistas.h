#ifndef __BaseVistas_
#define __BaseVistas_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

//#include <CEGUI/CEGUISystem.h>
//#include <CEGUI/CEGUIWindow.h>
//#include <CEGUI/CEGUIMinizipResourceProvider.h>
//#include <CEGUI/CEGUIEventSet.h>
//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "../ModeloVista/EscenaAjedrez.h"
#include "../ModeloVista/ModeloVista.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>


class BaseVistas: public OIS::KeyListener, public OIS::MouseListener, public Ogre::FrameListener
{
public:
    ~BaseVistas(void);
    void empieza();

    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
    Ogre::Root *mRoot;
    Ogre::RenderWindow* mWindow;

protected:
    BaseVistas(ModeloVista* modeloV, std::string label);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    ModeloVista* modeloVista;

private:
    void windowResized();
  //  int getFPS();
    bool configuraGraficos(const char *desiredRenderer);
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    OIS::InputManager* mInputManager;
    CEGUI::OgreRenderer* renderer;
    CEGUI::System* sys;

};

#endif
