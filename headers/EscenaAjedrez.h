#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_
#include "CreacionJuego.h"
#include "InputMan.h"





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

#endif // #ifndef __TutorialApplication_h_
