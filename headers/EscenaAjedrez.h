#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_
//#include "CreacionJuego.h"
//#include "InputMan.h"

#include <Ogre.h>

#define CASILLA 1 << 0  // Mascara para el escenario
#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3




class  EscenaAjedrez
{
public:
    EscenaAjedrez(void);
    ~EscenaAjedrez(void);

    void createScene(Ogre::SceneManager*);


protected:
    Ogre::SceneManager* mSceneMgr;

    void creaFichas(Ogre::SceneNode* nodoBase);
    void creaCasillas(Ogre::SceneNode* nodoBase);



};

#endif
