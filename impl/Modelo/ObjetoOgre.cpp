#include "../../headers/Modelo/ObjetoOgre.h"



ObjetoOgre::ObjetoOgre(std::string nombre) :
    vectorHijos(0),
    nodoEscena(NULL)
  , entidad(NULL)



{
    nombreObjeto = nombre;
    //nombreNodo = "test"+nombre;


}
ObjetoOgre::~ObjetoOgre()
{


}



void ObjetoOgre::cambiaMaterial(std::string material){
    entidad->setMaterialName(material);

}

bool ObjetoOgre::creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask)
{
   //  entidad = mSceneMgr->createEntity("test12", "Tablero.mesh");
    mSceneMgr = sceneMgr;
    nodoEscena = mSceneMgr->createSceneNode(nombreObjeto);
    std::cout  << "NOMBREOBJETO: "<< nombreObjeto << std::endl;

std::cout  << "CREA MODELO 3D: "<< nombreMalla << std::endl;

    nombreMalla.append(".mesh");

    std::cout  << "CREA MODELO 3D: "<< nombreMalla << std::endl;

    entidad = mSceneMgr->createEntity(nombreObjeto, nombreMalla);
    std::cout  << "CREA 33: " << std::endl;

    nodoEscena->attachObject(entidad);

    std::cout  << "CREA44: " << std::endl;

        entidad->setQueryFlags(mask);
        std::cout  << "SALE: " << std::endl;

}

void ObjetoOgre::trasladar(int x, int z)
{
    nodoEscena->translate(x,0,z);


}

void ObjetoOgre::rota(int grados){

    nodoEscena->yaw(Ogre::Degree(grados));


}


ObjetoOgre* ObjetoOgre::getHijo(std::string posicion)
{

}

ObjetoOgre* ObjetoOgre::getHijo(int numero)
{
    ObjetoOgre* obj = vectorHijos.at(numero);

    std::cout  << "GETHIJO: " << std::endl;

    std::cout  << "GETHIJO: " << obj->nombreObjeto <<std::endl;


    return vectorHijos.at(numero);
}



bool ObjetoOgre::agregaHijo(ObjetoOgre* objetoHijo){

    vectorHijos.push_back(objetoHijo);

    if (nodoEscena != NULL) nodoEscena->addChild(objetoHijo->getNodoOgre());

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


//bool ObjetoOgre::NuevoObjetoDeOgre(){
    //CREA EL OBJETO?


    //crea nodo

    //crea entidad



//}
