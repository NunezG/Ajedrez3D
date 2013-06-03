#ifndef __ArbolBusqueda_
#define __ArbolBusqueda_

//#include "ModeloTablero.h"
//#include "../Modelo/ModuloIA.h"
#include "../Modelo/Movimientos.h"


class ArbolBusqueda
{
public:

    ~ArbolBusqueda(void);
    ArbolBusqueda();




private:


    static short CalculatePieceActionValue(int pieceType);


    int evaluaTablero(const int casillasInt[144], bool turnoN);

    int alphaBeta(ModeloTablero* table,const int alpha,const int beta,const int depthleft );

    short valorFicha(const tipoFicha tipo);


    bool construyeArbol(ModeloTablero* tableroPadre);

};


#endif
