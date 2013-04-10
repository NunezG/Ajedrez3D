#include "../../headers/Modelo/Autorizaciones.h"

Autorizaciones::Autorizaciones(void)
{
}

Autorizaciones::~Autorizaciones(void)
{
}

bool Autorizaciones::autorizaCasilla(Tablero* miTablero,Casilla* nodoSeleccionado, Casilla* nodoSobrevolado, bool turnoNegras)
{
    // elTablero = miTablero;
    posicion seleccionado = nodoSeleccionado->getPosicion();
    // Ogre::Vector3 nuevo = nodoSobrevolado->getNodoOgre()->getPosition();
    posicion diferencia;

    diferencia.Fila = nodoSobrevolado->getPosicion().Fila - nodoSeleccionado->getPosicion().Fila;
    diferencia.Columna = nodoSobrevolado->getPosicion().Columna - nodoSeleccionado->getPosicion().Columna;


    // if(diferencia.Fila != 0)   diferencia= diferencia;
    // else diferencia= diferenciaZ;

    Ficha *mFicha = static_cast<Ficha*>(nodoSeleccionado->getHijo(0));
    tipoFicha tipo = mFicha->tipo_Ficha;
    //  std::cout  << "PRUEBA DE AUTORIZACIONES CON CLASES "<< std::endl;

    //std::cout  <<purebaCasilla->fichaAsociada->Tipo << std::endl;

    std::cout << "switch: " << std::endl;


    switch (tipo)
    {
    case Rey: //REY SELECCIONADO
        std::cout << "rey" << std::endl;

        return autorizaRey(diferencia,nodoSobrevolado->getPosicion(), miTablero, turnoNegras);
        break;

    case Reina: //REINA SELECCIONADO
        std::cout << "reina" << std::endl;

        return autorizaReina(diferencia, nodoSobrevolado->getPosicion(), miTablero);
        break;

    case Alfil: //ALFIL SELECCIONADO
        std::cout << "alfil" << std::endl;

        return autorizaAlfil(diferencia, nodoSobrevolado->getPosicion(), miTablero);
        break;

    case Torre: //TORRE SELECCIONADA
        std::cout << "torre" << std::endl;

        return autorizaTorre(diferencia, nodoSobrevolado->getPosicion(), miTablero);
        break;

    case Caballo: //CABALLO SELECCIONADO
        std::cout << "caballo" << std::endl;

        return autorizaCaballo(diferencia);
        break;

    case Peon: //PEON SELECCIONADO
        std::cout << "peon" << std::endl;


        return autorizaPeon(diferencia, nodoSobrevolado, seleccionado, turnoNegras, miTablero);
        break;

    default:
        return false;
        break;
    }
}

bool Autorizaciones::autorizaPeon(posicion diferencia, Casilla* nodoSobrevolado, posicion seleccionado, bool turnoNegras, Tablero* miTablero)
{


    if (turnoNegras)
    {
        //Invierte la coordenada X de los peones negros
        // seleccionado.Fila = 7 - seleccionado.Fila;
        diferencia.Fila = -diferencia.Fila;
        diferencia.Columna = -diferencia.Columna;

    }


    //if (diferencia.Fila < 0) diferencia.Fila = -diferencia.Fila;

    //if (diferencia.Columna < 0) diferencia.Columna = -diferencia.Columna;

    //if (turnoNegras)diferencia= -diferencia;

    std::cout  << "sel " <<seleccionado.Fila<<std::endl;

    std::cout  << "sel " <<seleccionado.Columna<<std::endl;

    std::cout  << "sobrevolado: "<<  nodoSobrevolado->getNombre() << "diferencia; "<<diferencia.Fila<<" col: "<< diferencia.Columna<<std::endl;


    bool salto = false;

    if (diferencia.Columna == 0)
    {
        if (diferencia.Fila== 2
                && ((seleccionado.Fila == 1 && !turnoNegras) || (seleccionado.Fila == 6 && turnoNegras)))  salto = true;

        else if (diferencia.Fila == 1)
        {
            if (nodoSobrevolado->getNodoOgre()->getChildIterator().hasMoreElements())
            {
                return false;
            }
            else return true;

        }
        //  else if(diferencia.Fila == 1 && (diferencia.Columna == 1)){


        //}
    }
    if(salto)
    {
        //HAY QUE CAMBIAR COSAS PARA IMPLEMENTAR EL COMER AL PASO

        //  nodoSobrevolado->getHijo(0);

        std::cout  << "verifica "<<std::endl;


        // if (!turnoNegras)
        return verificaCamino(diferencia.Fila, nodoSobrevolado->getPosicion(), 2, miTablero);
        // else return verificaCamino(diferencia.Fila, nodoSobrevolado->getPosicion(), 2, miTablero);

    }
    if ((diferencia.Fila == 1 &&( diferencia.Columna == -1
                                  || diferencia.Columna == 1)))
    {

        std::cout  << "comprueba laterales "<<std::endl;


        if (nodoSobrevolado->getNodoOgre()->getChildIterator().hasMoreElements())
        {
            return true;
        }else
        {
            posicion casillaLateral;
            // int casillaLateral = (seleccionado.Fila*8) + seleccionado.Columna;


            std::cout  << "diferencia 1 "<<std::endl;

            casillaLateral.Fila = seleccionado.Fila;

            casillaLateral.Columna = nodoSobrevolado->getPosicion().Columna;

            std::cout  << "casillaLateral.Fila "<<casillaLateral.Fila<<std::endl;

            std::cout  << "casillaLateral.col "<<casillaLateral.Columna<<std::endl;

            int posCasilla = (casillaLateral.Fila*8) + casillaLateral.Columna;
            Casilla* casilla = static_cast<Casilla*>(miTablero->getHijo(posCasilla));
            if (!casilla->sinHijos())

            {
                std::cout  << "tiene ficha "<<std::endl;


                Ficha* fichaLateral = static_cast<Ficha*>(casilla->getHijo(0));

                if (fichaLateral->salto)
                {
                    std::cout  << "SALTA "<<std::endl;

                    return true;
                }else  std::cout  << "no salta "<<std::endl;


            }



        }


    }
    return false;

}

bool Autorizaciones::autorizaAlfil(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero)
{
    if (diferencia.Columna - diferencia.Fila == 0
            && diferencia.Columna > 0) //Columnas DESCENDENTES Y Filas DESCENDENTES
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 8, elTablero);

    else if (diferencia.Columna + diferencia.Fila == 0
             && diferencia.Columna > 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR DERECHA)
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 7, elTablero);

    else if(diferencia.Columna + diferencia.Fila == 0
            && diferencia.Columna < 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO IZQUIERDA)
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 6, elTablero);

    else if(diferencia.Columna - diferencia.Fila == 0
            && diferencia.Columna  < 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ABAJO DERECHA)
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 5, elTablero);

    else return false;
}

bool Autorizaciones::autorizaReina(posicion diferencia, posicion nodoSobrevolado, Tablero* miTablero)
{
    if (autorizaAlfil(diferencia, nodoSobrevolado, miTablero))
        return true;
    else return autorizaTorre(diferencia, nodoSobrevolado, miTablero);
}

bool Autorizaciones::autorizaRey(posicion diferencia, posicion nodoSobrevolado, Tablero* miTablero, bool turnoNegras)
{
    if ((diferencia.Fila==1||diferencia.Fila==-1||diferencia.Fila==0)
            && (diferencia.Columna==1||diferencia.Columna==-1||diferencia.Columna==0))
        return true;
    else{
        //ENROQUE!!!
        if( diferencia.Fila == 0){
             Casilla* casilla = NULL;
             int posCasilla = nodoSobrevolado.Fila*8;


             std::cout  << "DIFERENCIA EN EL REY: "<< diferencia.Columna<<std::endl;

            if(diferencia.Columna == 2)
            {
             casilla  = static_cast<Casilla*>(miTablero->getHijo(posCasilla+7));



            }
             if(diferencia.Columna == -2){

                 casilla  = static_cast<Casilla*>(miTablero->getHijo(posCasilla));


             }


             if (casilla != NULL && !casilla->sinHijos())
             {

                 Ficha* ficha =  static_cast<Ficha*>(casilla->getHijo(0));

                 if(ficha->tipo_Ficha == Torre)
                 {

                     if ((!turnoNegras && nodoSobrevolado.Fila == 0) ||
                             (turnoNegras && nodoSobrevolado.Fila == 7)){


                         if(diferencia.Columna == 2)
                         {
                             std::cout  << "mueve a la derecha "<<std::endl;

                          return verificaCamino(diferencia.Columna, nodoSobrevolado, 4, miTablero);
                         }


                         if(diferencia.Columna == -2)
                         {
                             std::cout  << "mueve a la izquierda "<<std::endl;

                         return verificaCamino(diferencia.Columna, nodoSobrevolado, 3, miTablero);
                         }




                     }
                 }

             }



        }


        return false;

    }
}

bool Autorizaciones::autorizaTorre(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero)
{

    std::cout  << "autoriza torre: "<<diferencia.Fila << "col "<<diferencia.Columna <<std::endl;

    if (diferencia.Columna==0
            && diferencia.Fila < 0 ) //MOVIMIENTO A LA DERECHA
        return verificaCamino(diferencia.Fila, nodoSobrevolado, 2, elTablero);

    else if (diferencia.Columna==0
             && diferencia.Fila > 0 )  //MOVIMIENTO A LA IZQUIERDA
        return verificaCamino(diferencia.Fila, nodoSobrevolado, 1, elTablero);

    else if (diferencia.Fila==0
             && diferencia.Columna > 0 )  //MOVIMIENTO ARRIBA
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 4, elTablero);

    else if (diferencia.Fila==0
             && diferencia.Columna < 0 ) //MOVIMIENTO ABAJO
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 3, elTablero);

    else return false;
}

/*

//-------------------------------------------------------------------------------------
void Autorizaciones::FichaComestible()
{

   Ogre::SceneNode* child = casillaOcupada(getNodoCasillaSobrevolada());

    //Mira si la casilla está ocupada y por quién
   // Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (_nodoNuevo->getChild(0));
    Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

    if((!escenaAjedrez->esTurnoNegras() && ent->getName()[1] == 'N')
            || (escenaAjedrez->esTurnoNegras() && ent->getName()[1] == 'B'))
    {
        escenaAjedrez->iluminaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());
    }
}
*/

bool Autorizaciones::autorizaCaballo(posicion diferencia)
{
    if (diferencia.Fila < 0) diferencia.Fila = -diferencia.Fila;
    if (diferencia.Columna < 0) diferencia.Columna = -diferencia.Columna;

    if ((diferencia.Fila == 2 && diferencia.Columna == 1)
            || (diferencia.Fila == 1 && diferencia.Columna == 2))
        return true;
    else return false;
}

bool Autorizaciones::verificaCamino(int distancia, posicion _nodoNuevo, int camino, Tablero* elTablero)
{

    bool invertido;
    if (distancia < 0){
        invertido = true;
        distancia = -distancia;


    }

    std::cout  << "posicion FILA: "<<_nodoNuevo.Fila <<" COL: "<<_nodoNuevo.Columna<<std::endl;

    int colDestino = _nodoNuevo.Columna;//-(nuevo.z/10);
    int filaDestino =_nodoNuevo.Fila; //-(nuevo.x/10);


    for (int i = 1; i < distancia; i++)
    {
        std::cout  << "FOR! " <<std::endl;

        if (camino == 1) filaDestino = filaDestino-1;  // DERECHA
        else if (camino == 2) filaDestino = filaDestino+1; // IZQUIERDA
        else if (camino == 3) colDestino = colDestino+1; // MOVIMIENTO HACIA ARRIBA
        else if (camino == 4) colDestino = colDestino-1; // MOVIMIENTO HACIA ABAJO
        else if (camino == 5)
        { //MOVIMIENTO DIAGONAL ARRIBA IZQUIERDA
            colDestino = colDestino+1;
            filaDestino = filaDestino+1;
        }
        else if (camino == 6)
        { //MOVIMIENTO DIAGONAL ARRIBA DERECHA
            colDestino = colDestino+1;
            filaDestino = filaDestino-1;
        }
        else if (camino == 7) //MOVIMIENTO DIAGONAL ABAJO IZQUIERDA
        {
            colDestino = colDestino-1;
            filaDestino = filaDestino+1;
        }
        else if (camino == 8) //MOVIMIENTO DIAGONAL ABAJO DERECHA
        {
            colDestino = colDestino-1;
            filaDestino = filaDestino-1;
        }

        std::cout  << "VERIFICA: "<<( (filaDestino*8) + (colDestino))<<std::endl;


        Casilla* nodoTrayectoria = static_cast<Casilla*>(elTablero->getHijo((filaDestino*8) + (colDestino)));
        if (nodoTrayectoria->sinHijos() == false)
            return false;
    }
    return true;
}
