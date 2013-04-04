#include "../../headers/Modelo/Tablero.h"



Tablero::Tablero() :
    columnas("ABCDEFGH")




{

}
Tablero::~Tablero()
{


}






bool Tablero::creaTableroYCasillas(Ogre::SceneManager* sceneMgr){

    mSceneMgr = sceneMgr;
    Ogre::Entity *entTablero = mSceneMgr->createEntity("test12", "Tablero.mesh");
    entTablero->setQueryFlags(TABLERO);

    objetoOgreAsociado = new ObjetoOgre(mSceneMgr, "Tablero");

    objetoOgreAsociado->creaModelo3D("Tablero");




    nodoTablero = mSceneMgr->createSceneNode("NodoTablero");

    nodoTablero->attachObject(entTablero);

    mSceneMgr->getRootSceneNode()->addChild(nodoTablero);

    nodoCasillero = mSceneMgr->createSceneNode("NodoCasillero");


    nodoTablero->addChild(nodoCasillero);

    creaCasillas();



}




void Tablero::creaCasillas()
{
    Ogre::Entity *mCasilla;
    Ogre::SceneNode *mNodoCasilla;
    int contFila = 0;
    int contColumna = 0;
    //const char* columnas = "ABCDEFGH";
    bool inversa = false;
    std::stringstream saux;


    for (int i = 0; i < 8; ++i)
    {

        for (int y = 0; y < 8; ++y)
        {


        }

    }

    for (int i = 0; i < 64; ++i)
    {
        if (contColumna == 8)
        {
            contFila++;
            contColumna = 0;

        }
        saux.str("");
        saux << columnas[contColumna] << Ogre::StringConverter::toString( contFila + 1 );

        //SI ES COLUMNA PAR Y FILA IMPAR: CASILLA NEGRA
        if ((i%2 == 0
             && contFila % 2 != 0)
                ||(i%2 != 0
                   && contFila % 2 == 0) )
        {
            mCasilla = mSceneMgr->createEntity("(N)"+saux.str(), "Casilla.mesh");
            mCasilla->setMaterialName("MaterialCasillaNegra");
        } else mCasilla = mSceneMgr->createEntity("(B)"+saux.str(), "Casilla.mesh");

        mCasilla->setQueryFlags(CASILLA);

        ObjetoOgre* objeto = new ObjetoOgre( mSceneMgr, "Casilla" + saux.str() );

        objeto->creaModelo3D("Casilla");

        mNodoCasilla = mSceneMgr->createSceneNode(saux.str());
        mNodoCasilla->translate(-10*contFila,0,-10*contColumna);
        mNodoCasilla->attachObject(mCasilla);
        //std::cout  << "AÑADE CASILLA " << mCasilla->getName() << std::endl;

        nodoCasillero->addChild(mNodoCasilla);


        contColumna++;
    }
}


bool Tablero::creaFichasAjedrez(Ogre::SceneManager* mSceneMgr){






    creaFichas();

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


    // return nodoTablero;

}



void Tablero::creaFichas()
{
    creaVasallos();
    creaPeones();
    creaNobleza();
}

void Tablero::creaVasallos(){
    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;
    Ogre::String nombreFicha;

    //CREA LAS PIEZAS DOBLES
    for (int i = 0; i < 4; ++i)
    {



        saux.str("");
        saux <<"(T)Torre"<< Ogre::StringConverter::toString(i);

        ObjetoOgre* objeto = new ObjetoOgre(mSceneMgr, saux.str());
        objeto->creaModelo3D("Torre");

        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Torre.mesh");
            mFicha->setQueryFlags(BLANCAS);
            // mFicha->setMaterialName("MaterialFichaBlanca");

            //       mNodoFicha->translate(0,0,-70*(i/2));
            nombreFicha = columnas[7*(i/2)]+ Ogre::String("1");
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Torre.mesh");

            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[7*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);

        nodoCasillero->getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(C)Caballo"<< Ogre::StringConverter::toString(i);



        objeto = new ObjetoOgre(mSceneMgr, saux.str());
        objeto->creaModelo3D("Caballo");


        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+ saux.str(), "Caballo.mesh");
            mFicha->setQueryFlags(BLANCAS);
            // mNodoFicha->translate(0,0,-10-50*(i/2));
            nombreFicha = columnas[1+5*(i/2)]+ Ogre::String("1");
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+ saux.str(), "Caballo.mesh");
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[1+5*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero->getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(A)Alfil"<< Ogre::StringConverter::toString(i);

        mNodoFicha = mSceneMgr->createSceneNode(saux.str());

        objeto = new ObjetoOgre(mSceneMgr, saux.str());
        objeto->creaModelo3D("Alfil");

        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Alfil.mesh");

            nombreFicha = columnas[2+3*(i/2)]+ Ogre::String("1");
            mFicha->setQueryFlags(BLANCAS);
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Alfil.mesh");

            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[2+3*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero-> getChild(nombreFicha)->addChild(mNodoFicha);
    }
}

void Tablero::creaNobleza(){

    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;
    Ogre::String nombreFicha;


    //CREA LAS PIEZAS UNICAS
    for (int i = 0; i < 2; ++i)
    {
        saux.str("");
        saux <<"(D)Reina"<< Ogre::StringConverter::toString(i);



        ObjetoOgre* objeto = new ObjetoOgre(mSceneMgr, saux.str());
        objeto->creaModelo3D("Reina");


        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Reina.mesh");
            mFicha->setQueryFlags(BLANCAS);
            nombreFicha = columnas[3]+ Ogre::String("1");
        }else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Reina.mesh");
            nombreFicha = columnas[3]+ Ogre::String("8");

            mFicha->setQueryFlags(NEGRAS);
            mFicha->setMaterialName("MaterialFichaNegra");
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero-> getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(R)Rey"<< Ogre::StringConverter::toString(i);


        objeto = new ObjetoOgre(mSceneMgr, saux.str());
        objeto->creaModelo3D("Rey");


        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 != 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Rey.mesh");
            mFicha->setQueryFlags(BLANCAS);
            nombreFicha = columnas[4]+ Ogre::String("1");
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Rey.mesh");
            nombreFicha = columnas[4]+ Ogre::String("8");
            mFicha->setQueryFlags(NEGRAS);
            mFicha->setMaterialName("MaterialFichaNegra");
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero-> getChild(nombreFicha)->addChild(mNodoFicha);
    }


}

void Tablero::creaPeones(){

    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;
    Ogre::String nombreFicha;


    //CREA LOS PEONES
    for (int i = 0; i < 16; ++i)
    {
        saux.str("");
        saux <<"(P)Peon_"<< Ogre::StringConverter::toString(i);
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());


        ObjetoOgre* objeto = new ObjetoOgre(mSceneMgr, saux.str());
        objeto->creaModelo3D("Peon");


        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Peon.mesh");
            nombreFicha = columnas[i/2]+ Ogre::String("2");
            mFicha->setQueryFlags(BLANCAS);
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Peon.mesh");
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);

            nombreFicha = columnas[i/2]+ Ogre::String("7");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero -> getChild(nombreFicha)->addChild(mNodoFicha);
    }


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
