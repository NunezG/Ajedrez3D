#ifndef __Tablero_
#define __Tablero_

#include "FichaAlfil.h"
#include "FichaCaballo.h"
#include "FichaTorre.h"
#include "FichaReina.h"
#include "FichaRey.h"
#include "FichaPeon.h"


#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3
#define CASILLA 1 << 0  // Mascara para el escenario






struct Casilla{
    Ogre::String posicion;
    Ficha* fichaAsociada;


};


struct TableroPrueba{



     bool BlackCheck;
     bool BlackMate;
     bool WhiteCheck;
     bool WhiteMate;
     bool StaleMate;

     int Score;
    Casilla* casillas[64];


    Ficha* fichasNegras[16];
    Ficha* fichasBlancas[16];
   // int casillas[8][8];
    TableroPrueba* tableroHermano;
    TableroPrueba* tableroHijo;

};


// ESTE SERÁ EL NODO USADO EN LOS ÁRBOLES
class Tablero
{
public:






    ~Tablero(void);
    Ficha* fichasNegras[16];
    Ficha* fichasBlancas[16];


    Tablero(void);

    bool creaFichasAjedrez(Ogre::SceneManager* sceneMgr);

    int nivel;


    bool creaTableroYCasillas(Ogre::SceneManager* mSceneMgr);
    Ogre::SceneNode* nodoCasillero;
    void creaCasillas();

    Ogre::String columnas;

    Ogre::SceneManager* mSceneMgr;

private:

    ObjetoOgre* objetoOgreAsociado;



    Ogre::SceneNode* nodoTablero;


    Tablero* listaNodos[];


    Ogre::Entity *entTablero;

    bool verificaCamino(int inicial[2], int final[2], int camino);

    void creaFichas();

    void creaPeones();
    void creaNobleza();
    void creaVasallos();

    int casillas[8][8];

    bool turnoNegras;

};

#endif
