/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __BaseApplication_h_
#define __BaseApplication_h_


#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "SdkTrays.h"




#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>



#include "InputMan.h"
#include "CreacionJuego.h"

class BaseApplication //: public CreacionJuego
{
public:
    BaseApplication(Ogre::SceneManager* mSceneMgr);
    virtual ~BaseApplication(void);
    bool setupJuego(void);
    virtual void createCamera(void) = 0;
    Ogre::SceneManager* mSceneMgr;
    virtual void createViewports(void) = 0;
    virtual void createScene(void) = 0; // Override me!
protected:
    Ogre::RaySceneQuery *mRaySceneQuery;

    Ogre::RenderWindow* mWindow;

    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

   // virtual void createScene(void) = 0; // Override me!
    // virtual void createMainMenu(void) = 0; // Override me!
  //  virtual void createViewports(void) = 0;


    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );



    void createOverlay();

    //CEGUI::Renderer* mGUIRenderer;

    Ogre::Camera* mCamera;

    //Button* createButton(TrayLocation trayLoc, const Ogre::String& name, const Ogre::String& caption, Ogre::Real width = 0);

    // OgreBites
   // OgreBites::SdkTrayManager* mTrayMgr;
   // OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
    InputMan::SdkCameraMan* mInputMan;
  //  OgreBites::ParamsPanel* mOutputDebugPanel;     // sample details panel
    bool mCursorWasVisible;                    // was cursor visible before dialog appeared

    Ogre::OverlayManager* mOverlayManager;

Ogre::OverlayContainer* mCursor;      // cursor


// Ogre::RaySceneQuery *mRaySceneQuery;
 Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);

};

#endif // #ifndef __BaseApplication_h_
