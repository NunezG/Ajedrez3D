#ifndef __VistaAjedrez_h_
#define __VistaAjedrez_h_

#include "BaseApplication.h"
#include "Autorizaciones.h"
#include <Ogre.h>

class VistaAjedrez : public BaseApplication
{
public:
    VistaAjedrez(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow);
    ~VistaAjedrez(void);
    // Ogre::FrameListener
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


protected:


    Ogre::SceneNode *_selectedNode;


    bool fichaSeleccionada;
    Ogre::String textoOverlay;
};

#endif // #ifndef __VistaAjedrez_h_