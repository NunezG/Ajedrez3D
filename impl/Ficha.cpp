#include "../headers/Ficha.h"



Ficha::Ficha(bool esNegra) :
    esNegra(0),
    muerta(0)
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

bool Ficha::creaEntidad(Ogre::String nombre)
{
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
}

bool Ficha::setEntidad(Ogre::Entity* entidad)
{
    entFicha = entidad;
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
    return true;
}

Ogre::Entity* Ficha::getEntidad()
{
    return entFicha;
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
}

bool Ficha::setCasilla(int fila, int col)
{
    casilla[0] = fila;
    casilla[1] = col;
}
