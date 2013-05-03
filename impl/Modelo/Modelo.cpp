#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")
  , mResourcesCfg("resources.cfg")
  , mPantalla(0)
  , salirPulsado(0)
  , tablero(NULL)
   , numJugadores(0)


  //,  jugadores(NULL)




{
    resolucion = "800 x 600";
    tablero = new Tablero();

//mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

}
Modelo::~Modelo()
{
    for (int i=0; i<jugadores.size();i++){
        delete jugadores.at(i);
        jugadores.at(i) = NULL;
    }
    jugadores.clear();


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





void Modelo::destruyeTablero(){
   //delete mSceneMgr;

    delete tablero;

    tablero = NULL;


}

void Modelo::destruyeMenu(){

    delete menu;


    menu = NULL;

}
void Modelo::mueveFicha(float time)
{

    //Jugador* jug = jugadores[0];
    jugadores.at(getTablero()->getTurnoNegras())->mueveFicha(time);


}



//tal vez sea mejor una factoria de jugadores
void Modelo::creaJugador(bool blancas, bool humano )
{
   int num = numJugadores;


    if (humano){
        jugadores.push_back(new JugadorHumano(getTablero()));

    }
    else {

        jugadores.push_back(new JugadorArtificial(getTablero()));


    }

    if (blancas)
    {
        jugadores.at(num)->jugadorNegras = 0;


    }else {

        jugadores.at(num)->jugadorNegras = 1;

    }

    if (numJugadores == 0) jugadorActual = jugadores.at(0);

    numJugadores++;
}

Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}



