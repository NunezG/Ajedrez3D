#ifndef __VistaAjedrez_h_
#define __VistaAjedrez_h_

//#include "../BaseOgre.h"


#include "BaseVistas.h"
#include "../Modelo/EscenaAjedrez.h"
#include "../Modelo/Autorizaciones.h"
#include <Ogre.h>

class VistaAjedrez : public BaseVistas
{
public:
    VistaAjedrez(void);
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

    bool salir();
    bool esMenuInicio();
    bool cambiaTurno();
protected:


EscenaAjedrez* escenaAjedrez;

Tablero* tablero;

    Ogre::String textoOverlay;
};

#endif // #ifndef __VistaAjedrez_h_
