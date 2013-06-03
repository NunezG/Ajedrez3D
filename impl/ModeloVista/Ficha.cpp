#include "../../headers/ModeloVista/Ficha.h"






Ficha::Ficha(std::string nombre, int tipo) :
    esNegra(0),
    muerta(0),
    tipo_Ficha(tipo),
    ObjetoOgre(nombre),
    salto(false)
    // ,casilla(0)



{



    if(esNegra){


    }

    if(esNegra){


    }



}

Ficha::~Ficha()
{



}


Ficha::Ficha( const Ficha& fichaOriginal, std::string nombre, int tipo ):
    esNegra(fichaOriginal.esNegra),
    muerta(0),
    tipo_Ficha(tipo),
    ObjetoOgre(nombre),
    salto(false)
{


  //  tipo_Ficha = fichaOriginal



}


bool Ficha::setCasilla(int fila, int col)
{
    casilla[0] = fila;
    casilla[1] = col;
}






void Ficha::creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask)
{

    if (mask == NEGRAS) esNegra = true;
    else if (mask == BLANCAS )esNegra = false;


    ObjetoOgre::creaModelo3D(sceneMgr, nombreMalla, mask);
}


