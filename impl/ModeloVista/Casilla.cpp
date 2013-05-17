#include "../../headers/ModeloVista/Casilla.h"

Casilla::Casilla(std::string nombre) :
    esNegra(0)
  //, seleccionada(0)
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



void Casilla::apagaCasilla()
{

    std::cout  << "apagacasilla " << std::endl;

    getNodoOgre()->showBoundingBox(false);
    std::cout  << " fin apagacasilla " << std::endl;

    if (!esNegra)
    {
        std::cout  << "material casilla blanca " << std::endl;


        cambiaMaterial("MaterialCasillaBlanca");
    }else cambiaMaterial("MaterialCasillaNegra");

    std::cout  << "fin de fin " << std::endl;

}

void Casilla::iluminaCasilla()
{


    getNodoOgre()->showBoundingBox(true);

    if (esNegra)
    {


        cambiaMaterial("MaterialCasillaNegraIlum");
    }else cambiaMaterial("MaterialCasillaBlancaIlum");
}

