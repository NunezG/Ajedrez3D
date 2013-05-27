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
    for (int i=0; i<jugadores.size();i++)
    {
        delete jugadores.at(i);
        jugadores.at(i) = NULL;
    }
    jugadores.clear();
}



//tal vez sea mejor una factoria de jugadores
void Modelo::creaJugador(bool blancas, bool humano)
{ 
    int num = numJugadores;
    
    //HAY QUE CAMBIAR LO DE MODELOTABKERO PORQUE LOS JUGADORES ESTAN EN UN VECTOR Y ESE ES EL PROBLEMA
    if (humano)
    {
        std::cout << "CREA UN JUGADOR HUMANO" << std::endl;

        jugadores.push_back(new JugadorHumano());
    }
    else
    {
        std::cout << "CREA UN JUGADOR ARTIFICIAL" << std::endl;

        jugadores.push_back(new JugadorArtificial());
    }
    
    if (blancas)
    {
        jugadores.at(num)->jugadorNegras = 0;
    }
    else
    {
        jugadores.at(num)->jugadorNegras = 1;
    }

    numJugadores++;
}

Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}


