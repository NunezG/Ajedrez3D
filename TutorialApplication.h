/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include <boost/lexical_cast.hpp>
#include <Ogre.h>



class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);


    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );




protected:
    virtual void createScene(void);
    void creaCasillas(Ogre::SceneNode* nodoBase);
    void creaFichas(Ogre::SceneNode* nodoBase);
    bool  FichaComestible(void);



    int muevePeon(Ogre::String coord);
    int traduceCoordenadas(Ogre::String coord);
    Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);
     Ogre::SceneNode *_selectedNode;
     Ogre::SceneNode *_nodoNuevo;
    Ogre::RaySceneQuery *mRaySceneQuery;
    bool fichaSeleccionada;
    bool turnoNegras;
    Ogre::String textoOverlay;
};

#endif // #ifndef __TutorialApplication_h_
