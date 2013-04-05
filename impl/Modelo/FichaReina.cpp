#include "../../headers/Modelo/FichaReina.h"



FichaReina::FichaReina(std::string nombre) :
   // FichaAlfil(esNegra),
    Ficha("Reina"+nombre)




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
