#include "../../headers/Modelo/ObjetoOgre.h"



ObjetoOgre::ObjetoOgre()



{

}
ObjetoOgre::~ObjetoOgre()
{


}

bool ObjetoOgre::creaEntidad(Ogre::String nombre)
{
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
}

bool ObjetoOgre::setEntidad(Ogre::Entity* entidad)
{
    entFicha = entidad;
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
    return true;
}

Ogre::Entity* ObjetoOgre::getEntidad()
{
    return entFicha;
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
}

bool ObjetoOgre::setNodoOgre(Ogre::SceneNode* nodo)
{
    nodoEscena = nodo;
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
    return true;
}

Ogre::SceneNode* ObjetoOgre::getNodoOgre()
{
    return nodoEscena;
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
}


bool ObjetoOgre::NuevoObjetoDeOgre(){
    //CREA EL OBJETO?


    //crea nodo

    //crea entidad



}
