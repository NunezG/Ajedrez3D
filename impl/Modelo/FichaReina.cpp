#include "../../headers/Modelo/FichaReina.h"



FichaReina::FichaReina(std::string nombre) :
   // FichaAlfil(esNegra),
    Ficha("D_"+nombre, Reina)




{
      // saux <<"(N)Reina"<< Ogre::StringConverter::toString(i);

    //creaEntidad("Reina");


}
FichaReina::~FichaReina()
{


}



bool FichaReina::mueveFicha(){





}


FichaReina::FichaReina( const Ficha& fichaOriginal, std::string nombre):
    Ficha(fichaOriginal, "D_"+nombre, Reina)

{


    std::cout  <<"COPIA ESNEGRA: "<< esNegra<< std::endl;


}


bool FichaReina::autorizaFicha(int diferencia[2]){

//if (FichaTorre::autorizaFicha(diferencia))
//{
    //return Ficha::autorizaFicha(diferencia);
//}

return false;
}
