#include "../../headers/Modelo/Autorizaciones.h"



bool Autorizaciones::autorizaCasilla(Tablero* miTablero)
{
    Casilla* nodoSeleccionado = miTablero->getNodoCasillaSeleccionada();
     Casilla* nodoSobrevolado = miTablero->getNodoCasillaSobrevolada();

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

        return autorizaRey(diferencia,nodoSobrevolado->getPosicion(), miTablero, miTablero->getTurnoNegras());
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


        return autorizaPeon(diferencia, nodoSobrevolado, seleccionado, miTablero->getTurnoNegras(), miTablero);
        break;

    default:
        return false;
        break;
    }
}


bool Autorizaciones::evaluaJaque(int casillasInt[144], bool turnoNegras)
{
    int posRey = 999;
    int fichaRey = 6;

    int fichaReina = 5;
    int fichaPeon = 1;
    int fichaAlfil = 3;
    int fichaCaballo = 2;
    int fichaTorre = 4;

    if (!turnoNegras)
    {
        fichaRey = -6;

        fichaReina = -5;
        fichaPeon = -1;
        fichaAlfil = -3;
        fichaCaballo = -2;
        fichaTorre = -4;
    }

    for (int i=0; i<144;i++)
    {
        if (casillasInt[i] == -fichaRey)
        {
            posRey = i;
        }
    }

    if (posRey != 999)
    {
        //HACER PARA BLANCAS Y NEGRAS

        //N
        int ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*12)];

            if (i==1)
            {
                //REY
                if(ficha == fichaRey)
                {
                    std::cout << "REY NORTE" << std::endl;
                    return true;
                }
            }

            //REINA                             //TORRE
            if(ficha == fichaReina || ficha == fichaTorre)
            {

                if(ficha == fichaTorre)std::cout << "TORRE NORTE" << std::endl;
                else std::cout << "REINA NORTE" << std::endl;

                return true;
            }

            //cualquier otra ficha en medio
            if(ficha != 0)
            {

                break;
            }
        }

        //S
        ficha= 4;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*12)];

            if (i==1)
            {
                //REY
                if(ficha == fichaRey)
                {
                    std::cout << "REY SUR" << std::endl;

                    return true;
                }
            }

            //REINA                             //TORRE
            if(ficha == fichaReina || ficha == fichaTorre)
            {


                if(ficha == fichaTorre)std::cout << "TORRE SUR " << std::endl;
                else std::cout << "REINA SUR " << std::endl;
                return true;
            }

            //ficha en medio
            if(ficha != 0)
            {
                break;
            }
        }

        //E
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+i];

            if (i==1)
            {
                //REY
                if(ficha == fichaRey)
                {

                    std::cout << "REY ESTE" << std::endl;
                    return true;
                }
            }

            //REINA                             //TORRE
            if(ficha == fichaReina || ficha == fichaTorre)
            {


                if(ficha == fichaTorre)std::cout << "TORRE ESTE" << std::endl;
                else std::cout << "REINA ESTE" << std::endl;

                return true;
            }

            //ficha en medio
            if(ficha != 0)
            {
                break;
            }
        }

        //O
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {

            ficha = casillasInt[posRey-i];

            if (i==1)
            {
                //REY
                if(ficha == fichaRey)
                {

                    std::cout << "REY OESTE " << std::endl;
                    return true;

                }
            }

            //REINA                             //TORRE
            if(ficha == fichaReina || ficha == fichaTorre)
            {

                if(ficha == fichaTorre)std::cout << "TORRE OESTE " << std::endl;
                else std::cout << "REINA OESTE" << std::endl;

                return true;

            }
            //ficha en medio
            if(ficha != 0)
            {
                break;

            }
        }

        //NE


        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*11)];

            if (i==1)
            {
                //REY                               //PEON NEGRO
                if(ficha == fichaRey || (!turnoNegras && ficha == fichaPeon))
                {
                    if(ficha == fichaRey)std::cout << "REY NORESTE" << std::endl;
                    else std::cout << "PEON NEGRO NORESTE " << std::endl;

                    return true;
                }
            }

            //REINA                             //ALFIL
            if(ficha == fichaReina || ficha == fichaAlfil)
            {
                if(ficha == fichaAlfil)std::cout << "ALFIL NORESTE" << std::endl;
                else std::cout << "REINA NORESTE" << std::endl;
                return true;
            }

            //ficha en medio
            if(ficha != 0)
            {
                break;

            }
        }

        //NO
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*13)];
            if (i==1)
            {
                //REY                               //PEON NEGRO
                if(ficha == fichaRey || (!turnoNegras && ficha ==fichaPeon))
                {

                    if(ficha == fichaRey)std::cout << "REY NOROESTE " << std::endl;
                    else std::cout << "PEON NEGRO NOROESTE" << std::endl;
                    return true;
                }
            }
            //REINA                             //ALFIL
            if(ficha == fichaReina || ficha == fichaAlfil)
            {
                if(ficha == fichaAlfil)std::cout << "ALFIL NOROESTE " << std::endl;
                else std::cout << "REINA NOROESTE " << std::endl;
                return true;
            }
            //ficha en medio
            if(ficha != 0)
            {
                break;
            }
        }

        //SE

        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {

            ficha = casillasInt[posRey-(i*11)];


            if (i==1)
            {
                //REY                               //PEON BLANCO
                if(ficha == fichaRey || (turnoNegras && ficha ==fichaPeon))
                {

                    if(ficha == fichaRey)std::cout << "REY SUDESTE" << std::endl;
                    else std::cout << "PEON BLANCO SUDESTE " << std::endl;

                    return true;

                }
            }

            //REINA                             //ALFIL
            if(ficha == fichaReina || ficha == fichaAlfil)
            {

                if(ficha == fichaAlfil)std::cout << "ALFIL SUDESTE" << std::endl;
                else std::cout << "REINA SUDESTE" << std::endl;
                return true;

            }




            //ficha en medio
            if(ficha != 0)
            {
                break;

            }



        }

        //SO
        ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*13)];

            if (i==1)
            {
                //REY                               //PEON BLANCO
                if(ficha == fichaRey || (turnoNegras && ficha ==fichaPeon))
                {

                    if(ficha == fichaRey)std::cout << "REY SUDOESTE" << std::endl;
                    else std::cout << "PEON BLANCO SUDOESTE" << std::endl;
                    return true;
                }
            }

            //REINA                             //ALFIL
            if(ficha == fichaReina || ficha == fichaAlfil)
            {

                if(ficha == fichaAlfil)std::cout << "ALFIL SUDOESTE " << std::endl;
                else std::cout << "REINA SUDOESTE" << std::endl;
                return true;

            }

            //ficha en medio
            if(ficha != 0)
            {
                break;
            }
        }
        int caballo;

        caballo= posRey-10;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
        {

            std::cout << "CABALLO 1" << std::endl;
            return true;

        }
        caballo= posRey-14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
        {

            std::cout << "CABALLO 2" << std::endl;
            return true;

        }
        caballo= posRey-23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
        {

            std::cout << "CABALLO 3" << std::endl;
            return true;

        }

        caballo= posRey-25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
        {

            std::cout << "CABALLO 4" << std::endl;
            return true;

        }

        caballo= posRey+10;
        ficha = casillasInt[caballo];

        if(ficha == fichaCaballo)
        {

            std::cout << "CABALLO 5" << std::endl;
            return true;

        }

        caballo= posRey+14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
        {

            std::cout << "CABALLO 6" << std::endl;
            return true;

        }
        caballo= posRey+23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
        {

            std::cout << "CABALLO 7" << std::endl;
            return true;

        }
        caballo= posRey+25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
        {
            std::cout << "CABALLO 8" << std::endl;
            return true;
        }
    }
    return false;
}

bool Autorizaciones::autorizaPeon(posicion diferencia, Casilla* nodoSobrevolado, posicion seleccionado, bool turnoNegras, Tablero* miTablero)
{


    if (turnoNegras)
    {
        //Invierte la coordenada X de los peones negros
        // seleccionado.Fila = 7 - seleccionado.Fila;
        diferencia.Fila = -diferencia.Fila;
        diferencia.Columna = enColummas(-diferencia.Columna);

    }


    //if (diferencia.Fila < 0) diferencia.Fila = -diferencia.Fila;

    //if (diferencia.Columna < 0) diferencia.Columna = -diferencia.Columna;

    //if (turnoNegras)diferencia= -diferencia;

    std::cout  << "sel " <<seleccionado.Fila<<std::endl;

    std::cout  << "sel " <<seleccionado.Columna<<std::endl;

    std::cout  << "sobrevolado: "<<  nodoSobrevolado->getNombre() << "diferencia; "<<diferencia.Fila<<" col: "<< diferencia.Columna<<std::endl;

    if (diferencia.Columna == 0)
    {
        if (diferencia.Fila== 2
                && ((seleccionado.Fila == 1 && !turnoNegras) || (seleccionado.Fila == 6 && turnoNegras)))
        {
            //SALTA 2 CASILLAS (ESCAQUES)
            if (turnoNegras) return verificaCamino(diferencia.Fila, nodoSobrevolado->getPosicion(), 2, miTablero);
            else return verificaCamino(diferencia.Fila, nodoSobrevolado->getPosicion(), 1, miTablero);

        }

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
    }else  if((diferencia.Fila == 1 &&( diferencia.Columna == -1
                                        || diferencia.Columna == 1)))
    {

        std::cout  << "comprueba laterales "<<std::endl;

        //COME
        if (nodoSobrevolado->getNodoOgre()->getChildIterator().hasMoreElements())
        {
            return true;
        }else
        {
            //AL PASO, HAY QUE MEJORARLO SABIENDO QUE SOLO PUEDE HABER UNA FICHA QUE SALTE A LA VEZ (SE PUEDE GUARDAR EN UN INT LA POSICION O 0 SI NO HAY FICHA AL PASO)
            posicion casillaLateral;
            // int casillaLateral = (seleccionado.Fila*8) + seleccionado.Columna;


            std::cout  << "diferencia 1 "<<std::endl;

            casillaLateral.Fila = seleccionado.Fila;

            casillaLateral.Columna = nodoSobrevolado->getPosicion().Columna;

            std::cout  << "casillaLateral.Fila "<<casillaLateral.Fila<<std::endl;

            std::cout  << "casillaLateral.col "<<casillaLateral.Columna<<std::endl;

            int posCasilla = (casillaLateral.Fila*8) + casillaLateral.Columna;

            if (miTablero->getAlPaso() == (casillaLateral.Fila*8)+casillaLateral.Columna)
            {
              //  Casilla* casilla = static_cast<Casilla*>(miTablero->getHijo(posCasilla));
             //   if (!casilla->sinHijos())

               // {
                    std::cout  << "tiene ficha "<<std::endl;


                   // Ficha* fichaLateral = static_cast<Ficha*>(casilla->getHijo(0));

                  //  if (fichaLateral->salto)
                  //  {
                        std::cout  << "COME AL PASO "<<std::endl;

                        return true;
                  //  }else  std::cout  << "no salta "<<std::endl;


               // }
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
    if (diferencia.Columna < 0) diferencia.Columna = enColummas(-diferencia.Columna);

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
