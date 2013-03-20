#ifndef __BaseOgre_h_
#define __BaseOgre_h_


#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "SdkTrays.h"

//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include "EscenaAjedrez.h"

#include "BaseVistas.h"
//#include "CreacionJuego.h"

class BaseOgre: public BaseVistas
{
public:
    BaseOgre(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow);
    virtual ~BaseOgre(void);
   // bool setupJuego(void);

  //  virtual bool keyPressed( const OIS::KeyEvent &arg );
  //  virtual bool keyReleased( const OIS::KeyEvent &arg );
   // virtual bool mouseMoved( const OIS::MouseEvent &arg );
  //  virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
   // virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;

    bool iniciaVista();

protected:
    Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);


    void FichaComestible();


    EscenaAjedrez* escenaAjedrez;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
  //  Ogre::RaySceneQuery *mRaySceneQuery;
   // Ogre::Camera* mCamera;
    Ogre::OverlayContainer* mCursor;      // cursor
    Ogre::OverlayManager* mOverlayManager;
    Ogre::SceneNode *_nodoNuevo;

   // InputMan::SdkCameraMan* mInputMan;

    bool mCursorWasVisible;                    // was cursor visible before dialog appeared



private:
   // virtual void createViewports(void);
    //void createCamera(void);
    void createScene(void);


};

#endif // #ifndef __BaseOgre_h_
