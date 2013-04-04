#ifndef __Tablero_
#define __Tablero_

#include <vector>
#include <string>
#include <iostream>


#include "FichaAlfil.h"
#include "FichaCaballo.h"
#include "FichaTorre.h"
#include "FichaReina.h"
#include "FichaRey.h"
#include "FichaPeon.h"
#include "Casilla.h"




enum enColummas{
    COL_A,
    COL_B,
    COL_C,
    COL_D,
    COL_E,
    COL_F,
    COL_G,
    COL_H

};



// ESTE SERÁ EL NODO USADO EN LOS ÁRBOLES
class Tablero
{
public:

    ~Tablero(void);

    Tablero(void);

    int nivel;


    std::string columnas;

   Ogre::SceneManager* mSceneMgr;




    bool creaFichasAjedrez(Ogre::SceneManager* sceneMgr);

    bool creaTableroYCasillas(Ogre::SceneManager* sceneMgr);

    Ogre::SceneNode* nodoCasillero;




private:



    Ficha* fichasNegras[16];
    Ficha* fichasBlancas[16];

    int casillas[8][8];

    void creaCasillas();


    Ogre::SceneNode* nodoTablero;



    ObjetoOgre* objetoOgreAsociado;



    void creaFichas();

    void creaPeones();
    void creaNobleza();
    void creaVasallos();
    //void creaFichas();




    Tablero* listaNodos[];


    bool verificaCamino(int inicial[2], int final[2], int camino);




    bool turnoNegras;
};

#endif
