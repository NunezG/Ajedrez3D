#include "../headers/FichaTorre.h"



FichaTorre::FichaTorre(bool esNegra) :
    Ficha(esNegra)




{
    creaEntidad("Torre");

}
FichaTorre::~FichaTorre()
{


}


bool FichaTorre::mueveFicha(){




}


bool FichaTorre::autorizaFicha(int diferencia[2]){


    if (diferencia[1]==0
            && diferencia[0] < 0 ) //MOVIMIENTO A LA DERECHA
        return true;

    else if (diferencia[1]==0
             && diferencia[0] > 0 )  //MOVIMIENTO A LA IZQUIERDA
        return true;

    else if (diferencia[0]==0
             && diferencia[1] > 0 )  //MOVIMIENTO ARRIBA
        return true;

    else if (diferencia[0]==0
             && diferencia[1] < 0 ) //MOVIMIENTO ABAJO
        return true;

    else return false;


}
