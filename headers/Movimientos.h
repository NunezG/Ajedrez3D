
#ifndef __Movimientos_
#define __Movimientos_
#include <Ogre.h>




class Movimientos
{
public:
    Movimientos(void);
    virtual ~Movimientos(void);

   static bool caminoDerecha(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
   static bool caminoIzquierda(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
   static bool caminoArriba(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
   static bool caminoAbajo(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
   static bool caminoDiagArrIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
   static bool caminoDiagAbIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
   static bool caminoDiagArrDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
   static bool caminoDiagAbDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);

protected:




};

#endif // #ifndef __TutorialApplication_h_
