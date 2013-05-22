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
    static bool evaluaJaque(int* casillasInt, bool turnoNegras);
    static int* mueveTablero( int* tablero, int filaSel, int colSel, int filaNueva, int colNueva );
    static int* normalizaTablero(int* tablero);
private:





};

#endif
