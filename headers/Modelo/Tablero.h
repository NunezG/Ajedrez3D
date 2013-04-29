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
class Tablero: public ObjetoOgre
{
public:

    ~Tablero(void);

    Tablero(void);

   int getAlPaso();

   void setAlPaso(int casilla);

  // bool creaFichasAjedrez(Ogre::SceneManager* sceneMgr);

    bool creaTableroYCasillas(Ogre::SceneManager* sceneMgr);

    //Ogre::SceneNode* nodoCasillero;


    bool getTurnoNegras();
   // void setTurnoNegras(bool turno);


    Casilla* getNodoFichaSeleccionada();
    Casilla* getNodoCasillaSobrevolada();

    void setNodoFichaSeleccionada(Casilla* nodo);
    void setNodoCasillaSobrevolada(Casilla* nodo);


    bool FichaComestible();
    void cambiaTurno();

    int* actualizaTablero(posicion casillaOrigen,posicion casillaDestino);

    int* mueveIA(int origen, int destino);
    int* traduceTablero();

    int* mueveYTraduceTablero();


    std::string columnas;

   Ogre::SceneManager* mSceneMgr;


private:

   FichaReina* promocionaPeon(Ficha* nodoFicha);

   void creaCasillas();

  // ObjetoOgre* objetoOgreAsociado;


   void creaPeones();
   void creaNobleza();
   void creaVasallos();
   //void creaFichas();

  // bool verificaCamino(int inicial[2], int final[2], int camino);
   int evaulaTablero(const int casillasInt[144]);
   short traduceFicha(tipoFicha tipo);

    int nivel;

    int alPaso;

    int peonesPromocionados;

    Casilla* _selectedNode;
    Casilla* _nodoNuevo;

     bool jaqueNegras;
     bool mateNegras;
     bool jaqueBlancas;
     bool mateBlancas;
     bool ahogado;

  //  Ficha* fichasNegras[16];
  //  Ficha* fichasBlancas[16];

   // Ogre::SceneNode* nodoTablero;

    Tablero* listaNodos[];
    bool turnoNegras;

   // int casillas[8][8];



};

#endif
