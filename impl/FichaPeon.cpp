#include "../headers/FichaPeon.h"



FichaPeon::FichaPeon(bool esNegra) :
    Ficha(esNegra)



{
    creaEntidad("Peon");

}
FichaPeon::~FichaPeon()
{


}


bool FichaPeon::mueveFicha(){




}

bool FichaPeon::autorizaFicha(int diferencia[2]){

    if (diferencia[0]==-10
            || (diferencia[0]==-20
                && casilla[0] == -10))
    {
        //if (nodoSobrevolado->getChildIterator().hasMoreElements())
        //    return false;
       return true;

    } //else if (nodoSobrevolado->getChildIterator().hasMoreElements()
         //      && (diferencia==Ogre::Vector3(-10,0,10)
          //         || diferencia==Ogre::Vector3(-10,0,-10)))
       // return true;
    else return false;


}
