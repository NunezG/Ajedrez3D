#include "../../headers/Modelo/FichaRey.h"



FichaRey::FichaRey(std::string nombre) :
    Ficha("R_"+nombre, Rey)



{
    //creaEntidad("Rey");

}
FichaRey::~FichaRey()
{


}






bool FichaRey::mueveFicha(){




}

bool FichaRey::autorizaFicha(int diferencia[2])
{
    if ((diferencia[0]==10||diferencia[0]==-10||diferencia[0]==0)
            && (diferencia[1]==10||diferencia[1]==-10||diferencia[1]==0))
        return true;
    else return false;
}
