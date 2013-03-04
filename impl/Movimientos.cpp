
#include "../headers/Movimientos.h"

//-------------------------------------------------------------------------------------
Movimientos::Movimientos(void)

{



}
//-------------------------------------------------------------------------------------
Movimientos::~Movimientos(void)
{

}



bool Movimientos::FichaComestible(Ogre::SceneNode* nodoSobrevolado, bool turnoNegras){

    Ogre::Node::ChildNodeIterator iterator = nodoSobrevolado->getChildIterator();

    if(iterator.hasMoreElements()){
        Ogre::SceneNode* child = (Ogre::SceneNode *)iterator.getNext();
        Ogre::SceneNode::ObjectIterator oi = child->getAttachedObjectIterator();

        if(oi.hasMoreElements()){
            Ogre::Entity* ent = (Ogre::Entity *)oi.getNext();


            if(!turnoNegras && ent->getName()[1] == 'N'){
                //  std::cout << "FICHA NEGRA ATACADA POR UNA BLANCA!!!!!!" << std::endl;

                nodoSobrevolado->showBoundingBox(true);

                Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(nodoSobrevolado->getAttachedObject(0));
                if (nodoSobrevolado->getAttachedObject(0)->getName()[1] == 'B'){
                    mEntidadCasilla->setMaterialName("MaterialBlancoIluminado");
                }else mEntidadCasilla->setMaterialName("MaterialNegroIluminado");
                return true;
            }else if(turnoNegras && ent->getName()[1] == 'B'){
                // std::cout << "FICHA BLANCA ATACADA POR UNA NEGRA!!!!!!" << std::endl;

                nodoSobrevolado->showBoundingBox(true);

                Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(nodoSobrevolado->getAttachedObject(0));
                if (nodoSobrevolado->getAttachedObject(0)->getName()[1] == 'B'){
                    mEntidadCasilla->setMaterialName("MaterialBlancoIluminado");
                }else mEntidadCasilla->setMaterialName("MaterialNegroIluminado");
                return true;
            }

        }
    }
    return false;
}


bool Movimientos::autorizaCasilla(Ogre::SceneNode* nodoSeleccionado, Ogre::SceneNode* nodoSobrevolado, bool turnoNegras){



    Ogre::Vector3 seleccionado = nodoSeleccionado->getParent()->getPosition();
    Ogre::Vector3 nuevo = nodoSobrevolado->getPosition();

    //AÑADE EL NOMBRE DE LA CASILLA AL OVERLAY
    //textoOverlay = nodoSobrevolado->getName();

    Ogre::Vector3 diferencia= nuevo-seleccionado;
    const Ogre::String mNombreUsado =  nodoSeleccionado->getName();


    /*    std::cout << "posicion del nodo sobevolado: "<< nuevo <<std::endl;
        std::cout << "posicion del nodo seleccionado: "<< seleccionado <<std::endl;
        std::cout << "diferencia: "<< diferencia <<std::endl;
*/

    switch (mNombreUsado[1]){
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
        if (!turnoNegras){
            return autorizaPeonBlanco(diferencia, nodoSobrevolado, seleccionado);
        }else{
          return autorizaPeonNegro(diferencia, nodoSobrevolado, seleccionado);
        }
        break;

    default:
        return false;
        break;
    }



}


bool Movimientos::autorizaPeonNegro(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado, Ogre::Vector3 seleccionado){


    if  (diferencia==Ogre::Vector3(10,0,0)
         || (diferencia==Ogre::Vector3(20,0,0)
             && seleccionado.x == -60)){

        //  std::cout << "AUTORIZA POR LA VIA HABITUAL!!!!!" << std::endl;

        if (nodoSobrevolado->getChildIterator().hasMoreElements()){

            //   std::cout << "ENCUENTRA UNA FICHA JUSTO DELANTE Y SE SUPONE QUE NO AUTORIZA" << std::endl;
            return false;

        }else return true;

    } else if (nodoSobrevolado->getChildIterator().hasMoreElements()
               && (diferencia==Ogre::Vector3(10,0,10)
                   || diferencia==Ogre::Vector3(10,0,-10))){

        // std::cout << "AUTORIZA POR LA VIA COMESTIBLE!!!!!" << std::endl;
        return FichaComestible(nodoSobrevolado, true);

    }else return false;


}


bool Movimientos::autorizaPeonBlanco(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado, Ogre::Vector3 seleccionado){

    if (diferencia==Ogre::Vector3(-10,0,0)
            || (diferencia==Ogre::Vector3(-20,0,0)
                && seleccionado.x == -10)){

        // std::cout << "AUTORIZA POR LA VIA HABITUAL!!!!!" << std::endl;

        if (nodoSobrevolado->getChildIterator().hasMoreElements()){

            //  std::cout << "ENCUENTRA UNA FICHA JUSTO DELANTE Y SE SUPONE QUE NO AUTORIZA" << std::endl;
            return false;

        }else return true;

    } else if (nodoSobrevolado->getChildIterator().hasMoreElements()
               && (diferencia==Ogre::Vector3(-10,0,10)
                   || diferencia==Ogre::Vector3(-10,0,-10))){

        // std::cout << "AUTORIZA POR LA VIA COMESTIBLE!!!!!" << std::endl;
        return FichaComestible(nodoSobrevolado, false);

    }else return false;



}

bool Movimientos::autorizaAlfil(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado){


    if (diferencia.z - diferencia.x == 0
            && diferencia.z > 0){

        //LETRAS DESCENDENTES Y NUMEROS DESCENDENTES
        return caminoDiagArrIzq(diferencia, nodoSobrevolado);

    }else if (diferencia.z + diferencia.x == 0
              && diferencia.z > 0){

        //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES
        return caminoDiagArrDer(diferencia, nodoSobrevolado);

    }else if(diferencia.z + diferencia.x == 0
             && diferencia.z < 0){

        //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES
        return caminoDiagAbIzq(diferencia, nodoSobrevolado);

    }else if(diferencia.z - diferencia.x == 0
             && diferencia.z < 0){

        //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES
        return caminoDiagAbDer(diferencia, nodoSobrevolado);

    }else return false;


}


bool Movimientos::autorizaReina(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado){

    if (diferencia.z==0
            && diferencia.x < 0 ){

        //MOVIMIENTO A LA DERECHA
        return caminoDerecha(diferencia, nodoSobrevolado);

    }else if (diferencia.z==0
              && diferencia.x > 0 ){

        //MOVIMIENTO A LA IZQUIERDA
        return caminoIzquierda(diferencia, nodoSobrevolado);

    }  else if (diferencia.x==0
                && diferencia.z > 0 ){

        //MOVIMIENTO ARRIBA
        return caminoArriba(diferencia, nodoSobrevolado);

    }  else if (diferencia.x==0
                && diferencia.z < 0 ){

        //MOVIMIENTO ABAJO
        return caminoAbajo(diferencia, nodoSobrevolado);

    }else  if (diferencia.z - diferencia.x == 0
               && diferencia.z > 0){

        //LETRAS DESCENDENTES Y NUMEROS DESCENDENTES
        return caminoDiagArrIzq(diferencia, nodoSobrevolado);

    }else if (diferencia.z + diferencia.x == 0
              && diferencia.z > 0){

        //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES
        return caminoDiagArrDer(diferencia, nodoSobrevolado);

    }else if(diferencia.z + diferencia.x == 0
             && diferencia.z < 0){

        //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES
        return caminoDiagAbIzq(diferencia, nodoSobrevolado);

    }else if(diferencia.z - diferencia.x == 0
             && diferencia.z < 0){

        //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES
        return caminoDiagAbDer(diferencia, nodoSobrevolado);

    }else return false;


}

bool Movimientos::autorizaRey(Ogre::Vector3 diferencia){

    if ((diferencia.x==10||diferencia.x==-10||diferencia.x==0)
            && (diferencia.z==10||diferencia.z==-10||diferencia.z==0)){

        return true;

    }else return false;

}


bool Movimientos::autorizaTorre(Ogre::Vector3 diferencia, Ogre::SceneNode* nodoSobrevolado){



    if (diferencia.z==0
            && diferencia.x < 0 ){

        //MOVIMIENTO A LA DERECHA
        return caminoDerecha(diferencia, nodoSobrevolado);

    }else if (diferencia.z==0
              && diferencia.x > 0 ){

        //MOVIMIENTO A LA IZQUIERDA
        return caminoIzquierda(diferencia, nodoSobrevolado);

    }  else if (diferencia.x==0
                && diferencia.z > 0 ){

        //MOVIMIENTO ARRIBA
        return caminoArriba(diferencia, nodoSobrevolado);

    }  else if (diferencia.x==0
                && diferencia.z < 0 ){

        //MOVIMIENTO ABAJO
        return caminoAbajo(diferencia, nodoSobrevolado);

    }else return false;


}



bool Movimientos::autorizaCaballo(Ogre::Vector3 diferencia){


    if (diferencia==Ogre::Vector3(-20,0,10)
            || diferencia==Ogre::Vector3(20,0,10)
            || diferencia==Ogre::Vector3(-20,0,-10)
            || diferencia==Ogre::Vector3(20,0,-10)
            || diferencia==Ogre::Vector3(10,0,20)
            || diferencia==Ogre::Vector3(10,0,-20)
            || diferencia==Ogre::Vector3(-10,0,20)
            || diferencia==Ogre::Vector3(-10,0,-20)){
        return true;
    }else return false;


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

