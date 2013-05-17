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

#include "../Modelo/Modelo.h"


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


    Casilla* getNodoCasillaSeleccionada();
    Casilla* getNodoCasillaSobrevolada();

    void setNodoCasillaSeleccionada(Casilla* nodo);
    void setNodoCasillaSobrevolada(Casilla* nodo);

    void actualizaTablero(posicion casillaOrigen,posicion casillaDestino);

     ModeloTablero* traduceTablero();



   // std::string columnas;

   Ogre::SceneManager* mSceneMgr;
   bool fichaSeleccionada;
   Ogre::Degree rotacionCamara;

   void promocionaPeon();

 //  bool turnoNegras;
   void cambiaTurno();

private:



   void creaCasillas();

  // ObjetoOgre* objetoOgreAsociado;


   void creaPeones();
   void creaNobleza();
   void creaVasallos();
   //void creaFichas();

  // bool verificaCamino(int inicial[2], int final[2], int camino);
   int evaulaTablero(const int casillasInt[144]);

   // int nivel;

   // int alPaso;

    int peonesPromocionados;

    Casilla* _selectedNode;
    Casilla* _nodoNuevo;



   /*
     bool jaqueNegras;
     bool mateNegras;
     bool jaqueBlancas;
     bool mateBlancas;

   */
  //   bool ahogado;

  //  Ficha* fichasNegras[16];
  //  Ficha* fichasBlancas[16];

   // Ogre::SceneNode* nodoTablero;

   // Tablero* listaNodos[];

   // int casillas[8][8];



};

#endif
