
#include "../../headers/Vistas/VistaAjedrezSolo.h"

//-------------------------------------------------------------------------------------
VistaAjedrezSolo::VistaAjedrezSolo( Ogre::RenderWindow* mWindow)
    : VistaAjedrez(mWindow)

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
    if(!escenaAjedrez->esTurnoNegras())
    return VistaAjedrez::mouseMoved( arg );
    //else mInputMan->injectMouseMove(arg);
    return true;
}

bool VistaAjedrezSolo::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{      
    if(!escenaAjedrez->esTurnoNegras())
    return VistaAjedrez::mousePressed( arg , id);
    //else mInputMan->injectMouseDown(arg, id);
     return true;

}

bool VistaAjedrezSolo::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(!escenaAjedrez->esTurnoNegras())
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
    if(modelo->escena->esTurnoNegras())rotaTurno = Ogre::Real(0.0f);
    return VistaAjedrez::frameRenderingQueued(evt);
    return true;
}


