#ifndef __Calculos_
#define __Calculos_
//#include "Tablero.h"
//#include "ModeloTablero.h"
#include "ModeloTablero.h"

enum tipoFicha
{
    Vacio,
    Peon,
    Caballo,
    Alfil,
    Torre,
    Reina,
    Rey
};


class Calculos
{


public:
    static bool evaluaJaque(int casillasInt[144], bool turnoNegras);
    static int* mueveTablero( int* tablero, int filaSel, int colSel, int filaNueva, int colNueva );
    static void normalizaTablero(int* tablero);
private:





};

#endif
