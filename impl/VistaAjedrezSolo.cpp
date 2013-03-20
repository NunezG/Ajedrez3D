
#include "../headers/VistaAjedrezSolo.h"

//-------------------------------------------------------------------------------------
VistaAjedrezSolo::VistaAjedrezSolo(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow)
    : VistaAjedrez(mSceneMgr, mWindow)

{
}

VistaAjedrezSolo::~VistaAjedrezSolo(void)
{    
}

//-------------------------------------------------------------------------------------
bool VistaAjedrezSolo::keyPressed( const OIS::KeyEvent &arg )
{
    return VistaAjedrez::keyPressed( arg );
}

bool VistaAjedrezSolo::keyReleased( const OIS::KeyEvent &arg )
{ 
    return VistaAjedrez::keyReleased( arg );
}

bool VistaAjedrezSolo::mouseMoved( const OIS::MouseEvent &arg )
{
    if(!turnoNegras)
    return VistaAjedrez::mouseMoved( arg );
    //else mInputMan->injectMouseMove(arg);
    return true;
}

bool VistaAjedrezSolo::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{      
    if(!turnoNegras)
    return VistaAjedrez::mousePressed( arg , id);
    //else mInputMan->injectMouseDown(arg, id);
     return true;

}

bool VistaAjedrezSolo::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(!turnoNegras)
    return VistaAjedrez::mouseReleased( arg, id );
    else{
      //  mInputMan->injectMouseUp(arg, id);
        // calculaMovimiento();
         return true;
    }
}

//-------------------------------------------------------------------------------------
bool VistaAjedrezSolo::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    return VistaAjedrez::frameRenderingQueued(evt);
    return true;
}


