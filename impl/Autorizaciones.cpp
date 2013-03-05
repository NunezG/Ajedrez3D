#include "../headers/Autorizaciones.h"

Autorizaciones::Autorizaciones(void)
{
}

Autorizaciones::~Autorizaciones(void)
{
}

bool Autorizaciones::autorizaCasilla(Ogre::SceneNode* nodoSeleccionado, Ogre::SceneNode* nodoSobrevolado, bool turnoNegras)
{
    Ogre::Vector3 seleccionado = nodoSeleccionado->getParent()->getPosition();
    Ogre::Vector3 nuevo = nodoSobrevolado->getPosition();
    Ogre::Vector3 diferencia= nuevo-seleccionado;

    Ogre::Entity *mEntidadFicha = static_cast<Ogre::Entity*>(nodoSeleccionado->getAttachedObject(0));
    Ogre::String mNombreUsado = mEntidadFicha->getName();

    switch (mNombreUsado[4])
    {
    case 'R': //REY SELECCIONADO
        return autorizaRey(diferencia);
        break;

    case 'N': //REINA SELECCIONADO
        return autorizaReina(diferencia, nodoSobrevolado);
        break;

    case 'A': //ALFIL SELECCIONADO
        return autorizaAlfil(diferencia, nodoSobrevolado);
        break;

    case 'T': //TORRE SELECCIONADA
        return autorizaTorre(diferencia, nodoSobrevolado);
        break;

    case 'C': //CABALLO SELECCIONADO
        return autorizaCaballo(diferencia);
        break;

    case 'P': //PEON SELECCIONADO

        if (mNombreUsado[1] == 'N')
        { //Invierte la coordenada X de los peones negros
            seleccionado.x = -(70 + seleccionado.x);
            diferencia.x = -diferencia.x;
        }
        return autorizaPeon(diferencia, nodoSobrevolado, seleccionado);
        break;

    default:
        return false;
        break;
    }
}

bool Autorizaciones::autorizaPeon(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado, Ogre::Vector3 seleccionado)
{
    if (diferencia==Ogre::Vector3(-10,0,0)
            || (diferencia==Ogre::Vector3(-20,0,0)
                && seleccionado.x == -10))
    {
        if (nodoSobrevolado->getChildIterator().hasMoreElements())
            return false;
        else return true;

    } else if (nodoSobrevolado->getChildIterator().hasMoreElements()
               && (diferencia==Ogre::Vector3(-10,0,10)
                   || diferencia==Ogre::Vector3(-10,0,-10)))
        return true;
    else return false;
}

bool Autorizaciones::autorizaAlfil(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado)
{
    if (diferencia.z - diferencia.x == 0
            && diferencia.z > 0) //LETRAS DESCENDENTES Y NUMEROS DESCENDENTES
        return verificaCamino(diferencia, nodoSobrevolado, 5);

    else if (diferencia.z + diferencia.x == 0
             && diferencia.z > 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR DERECHA)
        return verificaCamino(diferencia, nodoSobrevolado, 6);

    else if(diferencia.z + diferencia.x == 0
            && diferencia.z < 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO IZQUIERDA)
        return verificaCamino(diferencia, nodoSobrevolado, 7);

    else if(diferencia.z - diferencia.x == 0
            && diferencia.z < 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ABAJO DERECHA)
        return verificaCamino(diferencia, nodoSobrevolado, 8);

    else return false;
}

bool Autorizaciones::autorizaReina(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado)
{
    if (autorizaAlfil(diferencia, nodoSobrevolado))
        return true;
    else return autorizaTorre(diferencia, nodoSobrevolado);
}

bool Autorizaciones::autorizaRey(Ogre::Vector3 diferencia)
{
    if ((diferencia.x==10||diferencia.x==-10||diferencia.x==0)
            && (diferencia.z==10||diferencia.z==-10||diferencia.z==0))
        return true;
    else return false;
}

bool Autorizaciones::autorizaTorre(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado)
{
    if (diferencia.z==0
            && diferencia.x < 0 ) //MOVIMIENTO A LA DERECHA
        return verificaCamino(diferencia, nodoSobrevolado, 1);

    else if (diferencia.z==0
             && diferencia.x > 0 )  //MOVIMIENTO A LA IZQUIERDA
        return verificaCamino(diferencia, nodoSobrevolado, 2);

    else if (diferencia.x==0
             && diferencia.z > 0 )  //MOVIMIENTO ARRIBA
        return verificaCamino(diferencia, nodoSobrevolado, 3);

    else if (diferencia.x==0
             && diferencia.z < 0 ) //MOVIMIENTO ABAJO
        return verificaCamino(diferencia, nodoSobrevolado, 4);

    else return false;
}

bool Autorizaciones::autorizaCaballo(Ogre::Vector3 diferencia)
{
    if (diferencia==Ogre::Vector3(-20,0,10)
            || diferencia==Ogre::Vector3(20,0,10)
            || diferencia==Ogre::Vector3(-20,0,-10)
            || diferencia==Ogre::Vector3(20,0,-10)
            || diferencia==Ogre::Vector3(10,0,20)
            || diferencia==Ogre::Vector3(10,0,-20)
            || diferencia==Ogre::Vector3(-10,0,20)
            || diferencia==Ogre::Vector3(-10,0,-20))
        return true;
    else return false;
}

bool Autorizaciones::verificaCamino(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo, int camino)
{
    Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());

    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    const Ogre::String columnas = "ABCDEFGH";

    int colDestino = -(nuevo.z/10);
    int filaDestino = -(nuevo.x/10)+1;
    int numCasillasX = distancia.x/10;
    int numCasillasZ = distancia.z/10;

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
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[colZ] + Ogre::StringConverter::toString(filaX)));
        if (nodoTrayectoria->getChildIterator().hasMoreElements())
            return false;
    }
    return true;
}
