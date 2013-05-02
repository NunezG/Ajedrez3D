#ifndef __VistaAjedrez_h_
#define __VistaAjedrez_h_

//#include "../BaseOgre.h"


#include "BaseVistas.h"
#include "../Modelo/EscenaAjedrez.h"
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

    Ogre::RaySceneQueryResult& executeRay(int posx, int posy, char mascara);
    Ogre::RaySceneQuery* createRayQuery(void);

    bool seleccionaFichaEnPosicion(int posX, int posY);

    EscenaAjedrez* escenaAjedrez;

protected:

Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);

Tablero* tablero;

    Ogre::String textoOverlay;
    Ogre::RaySceneQuery *mRaySceneQuery;
    Ogre::RenderWindow* mWindow;
};

#endif // #ifndef __VistaAjedrez_h_
