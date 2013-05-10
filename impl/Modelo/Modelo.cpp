#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo() :
   mPantalla(0)
  , salirPulsado(0)
   , numJugadores(0)
 ,nombreBlancas("Jugador 1")
 , nombreNegras("Jugador 2")

  //,  jugadores(NULL)




{
    escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    resolucion = "800 x 600";

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





void Modelo::destruyeMenu(){

    delete menu;


    menu = NULL;

}
void Modelo::mueveFicha(float time)
{

    //Jugador* jug = jugadores[0];
    jugadores.at(escenaAjedrez->getTablero()->getTurnoNegras())->mueveFicha(time);


}



//tal vez sea mejor una factoria de jugadores
void Modelo::creaJugador(bool blancas, bool humano )
{
   int num = numJugadores;


    if (humano){
        jugadores.push_back(new JugadorHumano(escenaAjedrez->getTablero()));

    }
    else {

        jugadores.push_back(new JugadorArtificial(escenaAjedrez->getTablero()));


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


