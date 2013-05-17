#include "../../headers/Modelo/Jugador.h"



Jugador::Jugador(ModeloTablero* tablero) :
//esperaEleccion(false)
miTablero(tablero)



{


}

Jugador::~Jugador()
{


}




int* Jugador::mueveTablero( int filaSel, int colSel, int filaNueva, int colNueva )
{

    int* tableroTraducido = miTablero->casillasInt;

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );

    int posFinal = 24+(filaNueva*12) + colNueva+2;

    int posInicial = 24+(filaSel*12) + colSel+2;


    tableroTraducido[posFinal]= tableroTraducido[posInicial];
    tableroTraducido[posInicial] = 0;




    return tableroTraducido;
}

