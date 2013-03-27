#include "../../headers/Modelo/FichaReina.h"



FichaReina::FichaReina(bool esNegra) :
   // FichaAlfil(esNegra),
    Ficha(esNegra)




{
      // saux <<"(N)Reina"<< Ogre::StringConverter::toString(i);

    //creaEntidad("Reina");


}
FichaReina::~FichaReina()
{


}



bool FichaReina::mueveFicha(){




}

bool FichaReina::autorizaFicha(int diferencia[2]){

//if (FichaTorre::autorizaFicha(diferencia))
//{
    //return Ficha::autorizaFicha(diferencia);
//}

return false;
}
