#ifndef __VistaAjedrez_h_
#define __VistaAjedrez_h_

//#include "../BaseOgre.h"


#include "BaseVistas.h"
#include <Ogre.h>

class VistaAjedrez : public  BaseVistas
{
public:
    VistaAjedrez(Ogre::RenderWindow* window);
    ~VistaAjedrez(void);

    bool mueveCamara(float frecuencia);

    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool salir();
    bool esMenuInicio();


    bool seleccionaFichaEnPosicion(int posX, int posY);
    bool muestraJaque();

    CEGUI::Window *ventanaJaque;


protected:


Tablero* tablero;

    Ogre::String textoOverlay;
    Ogre::RenderWindow* mWindow;
};

#endif // #ifndef __VistaAjedrez_h_
