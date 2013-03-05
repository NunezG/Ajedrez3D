
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
    else return BaseApplication::mouseMoved( arg );

}

bool VistaAjedrezSolo::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{      
    if(!turnoNegras)
    return VistaAjedrez::mousePressed( arg , id);
    else return BaseApplication::mousePressed( arg, id );
}

bool VistaAjedrezSolo::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(!turnoNegras)
    return VistaAjedrez::mouseReleased( arg, id );
    else{
         BaseApplication::mouseReleased( arg, id );
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


