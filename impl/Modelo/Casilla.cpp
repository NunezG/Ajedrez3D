#include "../../headers/Modelo/Casilla.h"



Casilla::Casilla(std::string nombre) :
    esNegra(0)
  , ObjetoOgre("Casilla_"+nombre)




{





}



Casilla::~Casilla()
{


}

posicion Casilla::getPosicion(){
    return posCasilla;

}






void Casilla::setPosicion(int posFila, int posCol){


    posCasilla.Fila = posFila;

    posCasilla.Columna = posCol;

}


void Casilla::trasladarAPunto(){

    //char pos11= posicion.Fila;
    int pos1 =  posCasilla.Fila;
    int pos0 = posCasilla.Columna;





    getNodoOgre()->translate(-10*pos1,0,-10*pos0);

}
