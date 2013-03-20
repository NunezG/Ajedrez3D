#include "../headers/Tablero.h"



Tablero::Tablero()



{

}
Tablero::~Tablero()
{


}


bool Tablero::verificaCamino(int diferencia[2], int final[2], int camino)
{
    // fichas = new Ficha**;

    //Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());

    // Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    // const String columnas = "ABCDEFGH";

    int colDestino = -(final[1]/10);
    int filaDestino = -(final[0]/10)+1;
    int numCasillasX = diferencia[0]/10;
    int numCasillasZ = diferencia[1]/10;

    int colZ, filaX, dist;

    if (camino == 1)  //MOVIMIENTO A LA DERECHA
    {
        colZ = colDestino;
        dist = -numCasillasX;
    }
    else if (camino == 2) //MOVIMIENTO A LA IZQUIERDA
    {
        colZ = colDestino;
        dist = numCasillasX;
    }
    else if (camino == 3) //MOVIMIENTO HACIA ARRIBA
    {
        filaX = filaDestino;
        dist = numCasillasZ;
    }
    else if (camino == 4) //MOVIMIENTO HACIA ABAJO
    {
        filaX = filaDestino;
        dist = -numCasillasZ;
    }
    else if (camino == 5) dist = numCasillasZ; //MOVIMIENTO DIAGONAL ARRIBA IZQUIERDA
    else if (camino == 6) dist = numCasillasZ; //MOVIMIENTO DIAGONAL ARRIBA DERECHA
    else if (camino == 7) dist = -numCasillasZ; //MOVIMIENTO DIAGONAL ABAJO IZQUIERDA
    else if (camino == 8) dist = -numCasillasZ; //MOVIMIENTO DIAGONAL ABAJO DERECHA

    for (int i = 1; i < dist; i++)
    {
        if (camino == 1) filaX = filaDestino-i;  // DERECHA
        else if (camino == 2) filaX = filaDestino+i; // IZQUIERDA
        else if (camino == 3) colZ = colDestino+i; // MOVIMIENTO HACIA ARRIBA
        else if (camino == 4) colZ = colDestino-i; // MOVIMIENTO HACIA ABAJO
        else if (camino == 5)
        { //MOVIMIENTO DIAGONAL ARRIBA IZQUIERDA
            colZ = colDestino+i;
            filaX = filaDestino+i;
        }
        else if (camino == 6)
        { //MOVIMIENTO DIAGONAL ARRIBA DERECHA
            colZ = colDestino+i;
            filaX = filaDestino-i;
        }
        else if (camino == 7) //MOVIMIENTO DIAGONAL ABAJO IZQUIERDA
        {
            colZ = colDestino-i;
            filaX = filaDestino+i;
        }
        else if (camino == 8) //MOVIMIENTO DIAGONAL ABAJO DERECHA
        {
            colZ = colDestino-i;
            filaX = filaDestino-i;
        }

        // Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[colZ] + Ogre::StringConverter::toString(filaX)));
        if (casillas[colZ][filaX] > 0)
            return false;
    }
    return true;



}

bool Tablero::creaFichas(){

    fichasNegras[0] = new FichaReina(true);
    casillas[5][7] = 0;
    fichasBlancas[0]= new FichaReina(false);
     casillas[5][0] = 1;
    fichasNegras[1] = new FichaRey(true);
    fichasBlancas[1] = new FichaRey(false);



    ////////////////////////////////////////////////////////////////////////////////////////////////////////


    //CREA LAS PIEZAS DOBLES
    for (int i = 2; i < 4; ++i)
    {
        fichasNegras[i] = new FichaTorre(true);
        fichasBlancas[i] = new FichaTorre(false);

        fichasNegras[i+2] = new FichaTorre(true);
        fichasBlancas[i+2] = new FichaTorre(false);

        fichasNegras[i+4] = new FichaAlfil(true);
        fichasBlancas[i+4] = new FichaAlfil(false);

        fichasNegras[i+6] = new FichaCaballo(true);
        fichasBlancas[i+6] = new FichaCaballo(false);

    }


    //CREA LOS PEONES
    for (int i = 10; i < 18; ++i)
    {
        fichasNegras[i] = new FichaPeon(true);
        fichasBlancas[i] = new FichaPeon(false);
    }






    /////////////////////////////////////////////////////////////////////////////////////////////////////


    //Ficha* fichaRey = new FichaReina();



    //tablero = Tablero.
    //entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");


}

/*
board type
    This type contains all information specific to the current state of the game, including layout of the board and current player.

score type
    This data type indicates piece advantage, strategic advantage, and possible wins. In most games, strategic advantage includes the number of moves available to each player with the goal of minimizing the opponent's mobility.

neg_infinity and pos_infinity
    The most extreme scores possible in the game, each most disadvantageous for one player in the game.

generate_moves
    This function takes the current board and generates a list of possible moves for the current player.

apply_move
    This function takes a board and a move, returning the board with all the updates required by the given move.

null_move
    If the chosen game allows or requires a player to forfeit moves in the case where no moves are available, this function takes the current board and returns it, after switching the current player.

static_evaluation
    This function takes the board as input and returns a score for the game.

compare_scores
    This function takes 2 scores to compare and a player, returning the score that is more advantageous for the given player. If scores are stored as simple integers, this function can be the standard < and > operators.

*/
