#ifndef __Autorizaciones_
#define __Autorizaciones_
#include <Ogre.h>
#include "Tablero.h"

class Autorizaciones
{
public:
    Autorizaciones(void);
    virtual ~Autorizaciones(void);

    static bool autorizaCasilla(Ogre::SceneNode* nodoSeleccionado, Ogre::SceneNode* nodoSobrevolado, bool turnoNegras);

private:

    static bool autorizaRey(Ogre::Vector3 diferencia);
    static bool autorizaReina(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado);
    static bool autorizaPeon(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado, Ogre::Vector3 seleccionado);
    static bool autorizaAlfil(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado);
    static bool autorizaTorre(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado);
    static bool autorizaCaballo(Ogre::Vector3 diferencia);

   // static bool caminoAbajo(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagArrIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagAbIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagArrDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagAbDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);

    static bool verificaCamino(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo, int camino);



};

#endif
