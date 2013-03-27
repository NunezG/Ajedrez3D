#include "../../headers/Modelo/Ficha.h"



Ficha::Ficha(bool esNegra) :
    esNegra(0),
    muerta(0)
    // ,casilla(0)



{



    if(esNegra){


    }

    if(esNegra){


    }



}

Ficha::~Ficha()
{


}

bool Ficha::setCasilla(int fila, int col)
{
    casilla[0] = fila;
    casilla[1] = col;
}





short Ficha::CalculatePieceValue(tipoFicha pieceType)
{
    switch (pieceType)
    {
        case Peon:
            {
                return 100;
}

        case Caballo:
            {
                return 320;
            }
        case Alfil:
            {
                return 325;
            }
        case Torre:
            {
                return 500;
            }

        case Reina:
            {
                return 975;
            }

        case Rey:
            {
                return 32767;
            }
        default:
            {
                return 0;
            }
    }
}



short Ficha::CalculatePieceActionValue(tipoFicha pieceType)
{
    switch (pieceType)
    {
        case Peon:
            {
                return 6;
            }
        case Caballo:
            {
                return 3;
            }
        case Alfil:
            {
                return 3;
            }
        case Torre:
            {
                return 2;
            }
        case Reina:
            {
                return 1;
            }
        case Rey:
            {
                return 1;
            }
        default:
            {
                return 0;
            }
    }
}
