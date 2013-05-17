#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo() :
    numJugadores(0)
 ,nombreBlancas("Jugador 1")
 , nombreNegras("Jugador 2")

  //,  jugadores(NULL)




{

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






void Modelo::mueveJugador(bool turno)
{

 //   escenaAjedrez->getTablero()->getTurnoNegras()

    //Jugador* jug = jugadores[0];
    jugadores.at(turno)->mueveFicha();


}



//tal vez sea mejor una factoria de jugadores
void Modelo::creaJugador(bool blancas, bool humano ,ModeloTablero* tablero )
{

   int num = numJugadores;


    if (humano){
        jugadores.push_back(new JugadorHumano(tablero));

    }
    else {

        jugadores.push_back(new JugadorArtificial(tablero));


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


