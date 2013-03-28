#include "../../headers/Modelo/ObjetoOgre.h"



ObjetoOgre::ObjetoOgre(Ogre::SceneManager* sceneMgr, Ogre::String nombre)



{
    mSceneMgr = sceneMgr;
    nombreEntidad = "test"+nombre;
    nombreNodo = "test"+nombre;


}
ObjetoOgre::~ObjetoOgre()
{


}

bool ObjetoOgre::creaModelo3D(Ogre::String nombreMalla)
{
   //  entidad = mSceneMgr->createEntity("test12", "Tablero.mesh");
    nodoEscena = mSceneMgr->createSceneNode(nombreNodo);
    entidad = mSceneMgr->createEntity(nombreEntidad, nombreMalla.append(".mesh"));
}





bool ObjetoOgre::setEntidad(Ogre::Entity* entidad)
{
    entidad = entidad;
   // entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
    return true;
}

Ogre::Entity* ObjetoOgre::getEntidad()
{
    return entidad;
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
