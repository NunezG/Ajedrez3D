#ifndef __ArbolBusqueda_
#define __ArbolBusqueda_

#include "../Modelo/Movimientos.h"

class ArbolBusqueda
{
public:

    static int alphaBeta(ModeloTablero* table,const int alpha,const int beta,const int depthleft );

private:
    static short CalculatePieceActionValue(int pieceType);
    static int evaluaTablero(const int casillasInt[144]);
    static short valorFicha(const tipoFicha tipo);
};


#endif
