
#include "../headers/Movimientos.h"

//-------------------------------------------------------------------------------------
Movimientos::Movimientos(void)

{



}
//-------------------------------------------------------------------------------------
Movimientos::~Movimientos(void)
{

}


bool Movimientos::caminoDerecha(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";

    //  std::cout << "MOVIMIENTO A LA DERECHA DE CAMINODERECHA " <<std::endl;
    //MOVIMIENTO A LA DERECHA
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();
    for (int i = 1; i < -distancia.x/10; i++){
        // std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-(nuevo.z/10)] + Ogre::StringConverter::toString(-((nuevo.x/10)+i)+1) << std::endl;
        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-(nuevo.z/10)] + Ogre::StringConverter::toString(-((nuevo.x/10)+i)+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){
            //  std::cout << "HA ENCONTRADO UN NODO INTERMEDIO EN CAMINODERECHA!!!" << std::endl;
            return false;

        }
        //else std::cout << "nodo vacío!!!" << std::endl;

    }

    return true;


}


bool Movimientos::caminoIzquierda(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    std::cout << "MOVIMIENTO A LA IZQUIERDA " <<std::endl;
    //MOVIMIENTO A LA IZQUIERDA
    for (int i = 1; i < distancia.x/10; i++){
        std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-(nuevo.z/10)] + Ogre::StringConverter::toString(-((nuevo.x/10)-i)+1) << std::endl;
        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-(nuevo.z/10)] + Ogre::StringConverter::toString(-((nuevo.x/10)-i)+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){
            std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
            return false;
        }
        else std::cout << "nodo vacío!!!" << std::endl;

    }

    return true;


}

bool Movimientos::caminoArriba(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    std::cout << "MOVIMIENTO HACIA ARRIBA " <<std::endl;
    //MOVIMIENTO HACIA ARRIBA
    for (int i = 1; i < distancia.z/10; i++){
        std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-(nuevo.z/10)+i] + Ogre::StringConverter::toString(-(nuevo.x/10)+1) << std::endl;
        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-(nuevo.z/10)+i] + Ogre::StringConverter::toString(-(nuevo.x/10)+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){
            std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
            return false;

        }
        else std::cout << "nodo vacío!!!" << std::endl;

    }

    return true;


}


bool Movimientos::caminoAbajo(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    std::cout << "MOVIMIENTO HACIA ABAJO " <<std::endl;
    //MOVIMIENTO HACIA ABAJO
    for (int i = 1; i < -distancia.z/10; i++){
        std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-(nuevo.z/10)-i] + Ogre::StringConverter::toString(-(nuevo.x/10)+1) << std::endl;
        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-(nuevo.z/10)-i] + Ogre::StringConverter::toString(-(nuevo.x/10)+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){
            std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
            return false;
        }
        else std::cout << "nodo vacío!!!" << std::endl;

    }


    return true;


}





bool Movimientos::caminoDiagArrIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();


    //LETRAS DESCENDENTES Y NUMEROS DESCENDENTES

    for (int i = 1; i < distancia.z/10; i++){
        // std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-((nuevo.z/10)-i)] + Ogre::StringConverter::toString(-(((nuevo.x/10)-i))+1) << std::endl;

        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-((nuevo.z/10)-i)] + Ogre::StringConverter::toString(-(((nuevo.x/10)-i))+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){

            //  std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
            return false;
        }
        //else std::cout << "nodo vacío!!!" << std::endl;
    }



    return true;


}


bool Movimientos::caminoDiagArrDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES
    // std::cout << "CASO 2: LETRAS DESCENDENTES Y NUMEROS ASCENDENTES: " <<std::endl;

    for (int i = 1; i < distancia.z/10; i++){
        // std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-((nuevo.z/10)-i)] + Ogre::StringConverter::toString(-(((nuevo.x/10)+i))+1) << std::endl;

        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-((nuevo.z/10)-i)] + Ogre::StringConverter::toString(-(((nuevo.x/10)+i))+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){

            // std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
            return false;
        }
        //else std::cout << "nodo vacío!!!" << std::endl;
    }


    return true;


}


bool Movimientos::caminoDiagAbIzq(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES
    // std::cout << "CASO 3: LETRAS ASCENDENTES Y NUMEROS DESCENDENTES: " <<std::endl;


    for (int i = 1; i < distancia.x/10; i++){
        //std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-((nuevo.z/10)+i)] + Ogre::StringConverter::toString(-((nuevo.x/10)-i)+1) << std::endl;

        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-((nuevo.z/10)+i)] + Ogre::StringConverter::toString(-((nuevo.x/10)-i)+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){
            return false;
            //  std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
        }
        //else std::cout << "nodo vacío!!!" << std::endl;
    }

    return true;


}


bool Movimientos::caminoDiagAbDer(Ogre::Vector3 distancia, Ogre::SceneNode *_nodoNuevo){
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

    //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES
    std::cout << "CASO 3: LETRAS ASCENDENTES Y NUMEROS ASCENDENTES: " <<std::endl;


    for (int i = 1; i < -distancia.x/10; i++){
        std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-((nuevo.z/10)+i)] + Ogre::StringConverter::toString(-((nuevo.x/10)+i)+1) << std::endl;

        Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
        Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-((nuevo.z/10)+i)] + Ogre::StringConverter::toString(-((nuevo.x/10)+i)+1)));
        if   (nodoTrayectoria->getChildIterator().hasMoreElements()){
            return false;
            std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
        }
        //else std::cout << "nodo vacío!!!" << std::endl;
    }


    return true;


}

