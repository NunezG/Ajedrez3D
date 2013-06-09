#ifndef __Autorizaciones_
#define __Autorizaciones_

#include "Movimientos.h"

class Autorizaciones : public Movimientos
{
public:
    //  static void normalizaTablero(int* tablero);
    static  int autorizaRey(ModeloTablero* miTablero);
    static int autorizaReina(ModeloTablero* miTablero);
    static int autorizaPeon(ModeloTablero* miTablero);
    static  int autorizaAlfil(ModeloTablero* miTablero);
    static  int autorizaTorre(ModeloTablero* miTablero);
    static int autorizaCaballo(ModeloTablero* miTablero);

private:
    //  static bool verificaCamino(int distancia,  int filaNueva,int colNueva, int camino, int* casillas);

};

#endif
