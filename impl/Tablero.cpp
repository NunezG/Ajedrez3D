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



