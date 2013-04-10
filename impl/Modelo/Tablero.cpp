#include "../../headers/Modelo/Tablero.h"



Tablero::Tablero() :
    columnas("ABCDEFGH")
  , ObjetoOgre("Tablero")
{

}
Tablero::~Tablero()
{
}

bool Tablero::creaTableroYCasillas(Ogre::SceneManager* sceneMgr)
{
    mSceneMgr = sceneMgr;
    creaModelo3D(mSceneMgr, "Tablero", TABLERO);

    mSceneMgr->getRootSceneNode()->addChild(getNodoOgre());
    creaCasillas();
}

void Tablero::creaCasillas()
{
    int contFila = 0;
    int contColumna = 0;
    std::stringstream saux;
    Casilla* objeto;

    for (int i = 0; i < 64; ++i)
    {
        if (contColumna == 8)
        {
            contFila++;
            contColumna = 0;
            std::cout  <<"/"<< std::endl;

        }
        saux.str("");
        saux  << Ogre::StringConverter::toString( contFila + 1 )<<  columnas[contColumna];
        std::cout  <<(contFila*8)+contColumna<< std::ends;



        objeto = new Casilla(saux.str());
        objeto->creaModelo3D(mSceneMgr, "Casilla", CASILLA);

        //SI ES COLUMNA PAR Y FILA IMPAR: CASILLA NEGRA
        if ((i%2 == 0
             && contFila % 2 != 0)
                ||(i%2 != 0
                   && contFila % 2 == 0) )
        {
            objeto->esNegra = true;
            objeto->cambiaMaterial("MaterialCasillaNegra");
        }
        objeto->setPosicion(contFila, contColumna);
        objeto->trasladarAPunto();
        agregaHijo(objeto);
        contColumna++;
    }
}

bool Tablero::creaFichasAjedrez(Ogre::SceneManager* mSceneMgr)
{
    creaVasallos();
    creaNobleza();
    creaPeones();

}

void Tablero::creaVasallos()
{
    std::stringstream saux;
    //Ogre::String posCasilla;
    int posCasilla;

    Ficha* objeto;

    //CREA LAS PIEZAS DOBLES
    for (int i = 0; i < 4; ++i)
    {
        saux.str("");
        saux <<"(T)Torre"<< Ogre::StringConverter::toString(i);

        objeto = new FichaTorre(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr, "Torre", BLANCAS);

            posCasilla = (7*(i/2));
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Torre",NEGRAS);

            objeto->cambiaMaterial("MaterialFichaNegra");

            objeto->rota(180);

            objeto->trasladar(70,70);
            posCasilla = (7*(i/2))+ (7*8);
        }
        std::cout  << "gethijo " << std::endl;


        getHijo(posCasilla)->agregaHijo(objeto);

        std::cout  << "acabarModoCamara " << std::endl;

        saux.str("");
        saux <<"(C)Caballo"<< Ogre::StringConverter::toString(i);

        objeto = new FichaCaballo( saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Caballo",BLANCAS);

            posCasilla = (1+5*(i/2));
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Caballo",NEGRAS);

            objeto->cambiaMaterial("MaterialFichaNegra");

            objeto->rota(180);
            objeto->trasladar(70,70);
            posCasilla = (1+5*(i/2))+ (7*8);
        }
        getHijo(posCasilla)->agregaHijo(objeto);

        saux.str("");
        saux <<"(A)Alfil"<< Ogre::StringConverter::toString(i);

        objeto = new FichaAlfil(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Alfil",BLANCAS);
            posCasilla = (2+3*(i/2));
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Alfil",NEGRAS);
            objeto->cambiaMaterial("MaterialFichaNegra");
            objeto->rota(180);
            objeto->trasladar(70,70);
            posCasilla = (2+3*(i/2))+ (7*8);
        }

        getHijo(posCasilla)->agregaHijo(objeto);
    }
}

void Tablero::creaNobleza()
{
    std::stringstream saux;
    int posCasilla;
    Ficha* objeto;

    //CREA LAS PIEZAS UNICAS
    for (int i = 0; i < 2; ++i)
    {
        saux.str("");
        saux <<"(D)Reina"<< Ogre::StringConverter::toString(i);
        objeto = new FichaReina(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Reina",BLANCAS);
            posCasilla = 3;
        }else
        {
            objeto->creaModelo3D(mSceneMgr,"Reina",NEGRAS);
            posCasilla = 3+ (7*8);
            objeto->cambiaMaterial("MaterialFichaNegra");
            objeto->rota(180);
            objeto->trasladar(70,70);
        }
        getHijo(posCasilla)->agregaHijo(objeto);

        saux.str("");
        saux <<"(R)Rey"<< Ogre::StringConverter::toString(i);

        objeto = new FichaRey(saux.str());
        if (i%2 != 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Rey",BLANCAS);
            posCasilla = 4;
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Rey",NEGRAS);
            objeto->cambiaMaterial("MaterialFichaNegra");
            posCasilla = 4+(7*8);
            objeto->rota(180);
            objeto->trasladar(70,70);
        }
        getHijo(posCasilla)->agregaHijo(objeto);
    }
}

void Tablero::creaPeones()
{
    std::stringstream saux;
    int posCasilla;

    Ficha* objeto;

    //CREA LOS PEONES
    for (int i = 0; i < 16; ++i)
    {
        saux.str("");
        saux <<"(P)Peon_"<< Ogre::StringConverter::toString(i);
        objeto = new FichaPeon(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Peon",BLANCAS);
            posCasilla = (i/2)+ 8;
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Peon",NEGRAS);
            objeto->cambiaMaterial("MaterialFichaNegra");
            //objeto->rota(180);
            // objeto->trasladar(70,70);
            posCasilla = (i/2)+(6*8);
        }
        getHijo(posCasilla)->agregaHijo(objeto);
    }
}

bool Tablero::verificaCamino(int diferencia[2], int final[2], int camino)
{
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
