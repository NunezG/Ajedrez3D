#include "../../headers/Modelo/FichaAlfil.h"



FichaAlfil::FichaAlfil(std::string nombre) :
    Ficha("Alfil"+nombre)

   // ,casilla(0)

{

   // creaEntidad("Alfil");
}

FichaAlfil::~FichaAlfil()
{


}


bool FichaAlfil::mueveFicha(){





}



bool FichaAlfil::autorizaFicha(int diferencia[2]){



    if (diferencia[1] - diferencia[0] == 0
            && diferencia[1] > 0) //LETRAS DESCENDENTES Y NUMEROS DESCENDENTES
        return true;

    else if (diferencia[1] + diferencia[0] == 0
             && diferencia[1] > 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR DERECHA)
        return true;

    else if(diferencia[1] + diferencia[0] == 0
            && diferencia[1] < 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO IZQUIERDA)
        return true;

    else if(diferencia[1] - diferencia[0] == 0
            && diferencia[1] < 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ABAJO DERECHA)
        return true;

    else return false;




}
