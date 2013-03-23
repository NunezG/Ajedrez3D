#include "../headers/Modelo.h"



Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")




{

//mRoot =new Ogre::Root(mPluginsCfg);
//mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

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


void Modelo::construyeMenu(){
menu = ModeloMenu::getSingletonPtr();



}



void Modelo::construyeAjedrez(){
    escena = EscenaAjedrez::getSingletonPtr();


}



Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}


