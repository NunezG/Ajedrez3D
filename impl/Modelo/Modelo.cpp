#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")
  , mResourcesCfg("resources.cfg")
  , mPantalla(0)
  , salirPulsado(0)
  , tablero(NULL)
  , numJugadores(0)


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

void Modelo::creaJugador(bool negras, bool humano){

    if (humano)
    {
        jugadores.push_back(new JugadorHumano(tablero));

    }else{

        jugadores.push_back(new JugadorArtificial(tablero));
    }

    Jugador* jug = jugadores.at(numJugadores);
    if (negras)
    {

          jug->jugadorNegras = true;


    }else
    {

        jug->jugadorNegras = false;

    }




    if (numJugadores == 0) jugadorActual = jugadores.at(0);
    numJugadores++;

}
void Modelo::mueveFicha(float frecuencia)
{



jugadores.at(tablero->getTurnoNegras())->mueveFicha(frecuencia);


}


Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}


