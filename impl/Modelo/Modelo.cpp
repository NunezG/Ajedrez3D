#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")
  , mResourcesCfg("resources.cfg")
  , mPantalla(0)
  , salirPulsado(0)
  , tablero(NULL)


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


bool Modelo::getSalir(){
    return salirPulsado;
}

void Modelo::setSalir(bool salir){
    salirPulsado = salir;
}
int Modelo::getNumPantalla()
{
    return mPantalla;
}


void Modelo::setNumPantalla(int pantalla)
{
    mPantalla = pantalla;
}

void Modelo::construyeMenu()
{
    menu = new ModeloMenu();

}



void Modelo::construyeAjedrez()
{
    std::cout << "construye ajedrez " << std::endl;



}


void Modelo::destruyeTablero(){
   //delete mSceneMgr;

    delete tablero;
    std::cout << "nullea " << std::endl;

    tablero = NULL;


}

void Modelo::destruyeMenu(){

    delete menu;

    std::cout << "nullea " << std::endl;

    menu = NULL;

}


Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}


