#ifndef __Autorizaciones_
#define __Autorizaciones_
//#include "Tablero.h"
#include "Movimientos.h"



class Autorizaciones : public Movimientos
{
public:

  //  static void normalizaTablero(int* tablero);
    static bool autoriza(ModeloTablero* miTablero,  tipoFicha tipo);

private:


   static  bool autorizaRey(ModeloTablero* miTablero);
    static bool autorizaReina(ModeloTablero* miTablero);
    static bool autorizaPeon(ModeloTablero* miTablero);
   static  bool autorizaAlfil(ModeloTablero* miTablero);
   static  bool autorizaTorre(ModeloTablero* miTablero);
    static bool autorizaCaballo(int Dif);

  //  static bool verificaCamino(int distancia,  int filaNueva,int colNueva, int camino, int* casillas);




};

#endif
