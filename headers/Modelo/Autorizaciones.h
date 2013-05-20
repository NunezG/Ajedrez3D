#ifndef __Autorizaciones_
#define __Autorizaciones_
//#include "Tablero.h"
#include "Calculos.h"



class Autorizaciones : public Calculos
{
public:

  //  static void normalizaTablero(int* tablero);
    static bool autoriza(int* miTablero,  tipoFicha tipo, int filaSel, int colSel,  int filaNueva, int colNueva, bool turnoNegras, int alPaso);
    static bool verificaJaqueMate(int* tablero, bool turnoNegras, int alPaso);

private:


   static  bool autorizaRey(int filaDif, int colDif,  int filaNueva, int colNueva, int* tablero, bool turnoNegras);
    static bool autorizaReina(int filaDif, int colDif,  int filaNueva, int colNueva,int* miTablero);
    static bool autorizaPeon(int filaDif, int colDif,  int filaNueva, int colNueva,  int filaSel, int* miTablero, bool turnoNegras, int alPaso);
   static  bool autorizaAlfil(int filaDif, int colDif,  int filaNueva,int colNueva, int* elTablero);
   static  bool autorizaTorre(int filaDif, int colDif,  int filaNueva,int colNueva,int* elTablero);
    static bool autorizaCaballo(int filaDif, int colDif);

    static bool verificaCamino(int distancia,  int filaNueva,int colNueva, int camino, int* casillas);


   static bool mueveTorre(int* tablero, const int casilla);

   static bool mueveAlfil(int* tablero, const int casilla);

   static bool mueveCaballo(int* tablero,const int casilla);

   static bool mueveReina(int* tablero, const int casilla);

   static bool muevePeon(int* tablero,const int casilla, bool turnoNegras, int alPaso);

   static bool mueveRey(int* tablero, const int casilla);
  //  bool evaluaJaque(const int casillasInt[144], bool turnoNegras);


};

#endif
