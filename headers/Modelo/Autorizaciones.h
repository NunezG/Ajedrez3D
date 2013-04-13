#ifndef __Autorizaciones_
#define __Autorizaciones_
#include <Ogre.h>
#include "Tablero.h"

class Autorizaciones
{
public:
    Autorizaciones(void);
    virtual ~Autorizaciones(void);

    static bool autorizaCasilla(Tablero* miTablero, Casilla* nodoSeleccionado, Casilla* nodoSobrevolado, bool turnoNegras);
    static bool evaluaJaque(int casillasInt[144], bool turnoNegras);

private:



    //Tablero* elTablero;
    static bool autorizaRey(posicion diferencia, posicion nodoSobrevolado, Tablero* miTablero, bool turnoNegras);
    static bool autorizaReina(posicion diferencia, posicion nodoSobrevolado,Tablero* miTablero);
    static bool autorizaPeon(posicion diferencia, Casilla* nodoSobrevolado, posicion seleccionado, bool turnoNegras,Tablero* miTablero);
    static bool autorizaAlfil(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero);
    static bool autorizaTorre(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero);
    static bool autorizaCaballo(posicion diferencia);



   // static bool caminoAbajo(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagArrIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagAbIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagArrDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);
    //static bool caminoDiagAbDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo);

    static bool verificaCamino(int distancia, posicion _nodoNuevo, int camino, Tablero* elTablero);



};

#endif
