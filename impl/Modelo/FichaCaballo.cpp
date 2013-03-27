#include "../../headers/Modelo/FichaCaballo.h"



FichaCaballo::FichaCaballo(bool esNegra) :
    Ficha(esNegra)




{
   // creaEntidad("Caballo");

}

FichaCaballo::~FichaCaballo()
{


}

bool FichaCaballo::mueveFicha(){




}


bool FichaCaballo::autorizaFicha(int diferencia[2]){
    int dif1 = 10;
    int dif2 = 20;


    if (diferencia[0]==-dif2
            && (diferencia[1] == dif1
                || diferencia[1] == -dif1)

            || diferencia[0] == dif2
            && (diferencia[1] == dif1
                || diferencia[1] == -dif1)

            || diferencia[0] == dif1
            && (diferencia[1] == dif2
                || diferencia[1] == -dif2)

            || diferencia[0] == -dif1
            && (diferencia[1] == dif2
                || diferencia[1] == -dif2))
        return true;
    else return false;




}
