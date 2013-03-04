
#ifndef __Movimientos_
#define __Movimientos_
#include <Ogre.h>




class Movimientos
{
public:
    Movimientos(void);
    virtual ~Movimientos(void);

    static bool autorizaCasilla(Ogre::SceneNode* nodoSeleccionado, Ogre::SceneNode* nodoSobrevolado, bool turnoNegras);

    static bool FichaComestible(Ogre::SceneNode* nodoSobrevolado, bool turnoNegras);




protected:


    static bool autorizaRey(Ogre::Vector3 diferencia);
    static bool autorizaReina(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado);
    static bool autorizaPeonNegro(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado, Ogre::Vector3 seleccionado);
    static bool autorizaPeonBlanco(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado, Ogre::Vector3 seleccionado);
    static bool autorizaAlfil(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado);
    static bool autorizaTorre(Ogre::Vector3 diferencia, Ogre::SceneNode *nodoSobrevolado);
    static bool autorizaCaballo(Ogre::Vector3 diferencia);

    static bool caminoDerecha(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    static bool caminoIzquierda(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    static bool caminoArriba(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    static bool caminoAbajo(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    static bool caminoDiagArrIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    static bool caminoDiagAbIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    static bool caminoDiagArrDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    static bool caminoDiagAbDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);


};

#endif
