#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")

{
    resolucion = new std::string("1024 x 768");
    tablero = new Tablero();

//mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

}
Modelo::~Modelo()
{


}

Tablero* Modelo::getTablero()
{
return tablero;

}

bool Modelo::getApagar()
{

    return mShutDown;

}

int Modelo::getNumPantalla()
{

    return mPantalla;

}

void Modelo::construyeMenu()
{
menu = ModeloMenu::getSingletonPtr();

}



void Modelo::construyeAjedrez()
{


}



Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}


