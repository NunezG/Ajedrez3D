#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_

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

private:
    Ogre::SceneManager* mSceneMgr;



    void creaFichas();
    void creaCasillas();

    void creaPeones();
    void creaNobleza();
    void creaVasallos();


    Ogre::String columnas;
    Ogre::SceneNode* nodoTablero;
    Ogre::SceneNode* nodoCasillero;
};

#endif
