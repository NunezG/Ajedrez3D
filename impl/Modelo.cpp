#include "../headers/Modelo.h"



Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")




{

mRoot =new Ogre::Root(mPluginsCfg);
mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

}
Modelo::~Modelo()
{


}

bool Modelo::getApagar(){

    return mShutDown;

}


int Modelo::getNumPantalla(){

    return mPantalla;

}

bool Modelo::creaFichas(){


    //entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");


}
