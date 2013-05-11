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

    miTablero->casillasInt = miTablero->traduceTablero();

    if (miTablero->getTurnoNegras())normalizaTablero(miTablero->casillasInt);

    switch (tipo)
    {
    case Rey: //REY SELECCIONADO
        std::cout << "rey" << std::endl;

        return autorizaRey(diferencia,nodoSobrevolado->getPosicion(), miTablero);
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


        return autorizaPeon(diferencia, nodoSobrevolado, seleccionado, miTablero);
        break;

    default:
        return false;
        break;
    }
}


bool Autorizaciones::evaluaJaque(int casillasInt[144], bool turnoNegras)
{
    int posRey = 999;
    int fichaRey = -6;

    int fichaReina = -5;
    int fichaPeon = -1;
    int fichaAlfil = -3;
    int fichaCaballo = -2;
    int fichaTorre = -4;


    for (int i=0; i<144;i++)
    {
        if (casillasInt[i] == -fichaRey)
        {
            posRey = i;
        }
    }

    if (posRey != 999)
    {

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

bool Autorizaciones::autorizaPeon(posicion diferencia, Casilla* nodoSobrevolado, posicion seleccionado, Tablero* miTablero)
{


    if (miTablero->getTurnoNegras())
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

    std::cout  << "turnonegras una ez mas " <<miTablero->getTurnoNegras()<<std::endl;
    std::cout  << "sobrevolado: "<<  nodoSobrevolado->getNombre() << "diferencia; "<<diferencia.Fila<<" col: "<< diferencia.Columna<<std::endl;

    if (diferencia.Columna == 0)
    {
        if (diferencia.Fila== 2
                && ((seleccionado.Fila == 1 && !miTablero->getTurnoNegras()) || (seleccionado.Fila == 6 && miTablero->getTurnoNegras())))
        {
            std::cout  << "MIRA SI HAY FICHAS EN MEDIO " <<std::endl;

            //SALTA 2 CASILLAS (ESCAQUES)
            if (miTablero->getTurnoNegras()) return verificaCamino(diferencia.Fila, nodoSobrevolado->getPosicion(), 2, miTablero->casillasInt);
            else return verificaCamino(diferencia.Fila, nodoSobrevolado->getPosicion(), 1, miTablero->casillasInt);

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
        }else if(miTablero->getAlPaso() >= 0)
        {

            //AL PASO
            posicion casillaLateral;
            // int casillaLateral = (seleccionado.Fila*8) + seleccionado.Columna;


           std::cout  << "diferencia 1 "<<std::endl;

           casillaLateral.Fila = seleccionado.Fila;

            casillaLateral.Columna = nodoSobrevolado->getPosicion().Columna;

           std::cout  << "casillaLateral.Fila "<<casillaLateral.Fila<<std::endl;

           std::cout  << "casillaLateral.col "<<casillaLateral.Columna<<std::endl;

           int posCasilla = 24+(casillaLateral.Fila*12) + casillaLateral.Columna+2;

           if (miTablero->getAlPaso() == posCasilla)
           {

                return true;
           }




        }


    }



    return false;

}

bool Autorizaciones::autorizaAlfil(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero)
{
    if (diferencia.Columna - diferencia.Fila == 0
            && diferencia.Columna > 0) //Columnas DESCENDENTES Y Filas DESCENDENTES
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 8, elTablero->casillasInt);

    else if (diferencia.Columna + diferencia.Fila == 0
             && diferencia.Columna > 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR DERECHA)
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 7, elTablero->casillasInt);

    else if(diferencia.Columna + diferencia.Fila == 0
            && diferencia.Columna < 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO IZQUIERDA)
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 6, elTablero->casillasInt);

    else if(diferencia.Columna - diferencia.Fila == 0
            && diferencia.Columna  < 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ABAJO DERECHA)
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 5, elTablero->casillasInt);

    else return false;
}

bool Autorizaciones::autorizaReina(posicion diferencia, posicion nodoSobrevolado, Tablero* miTablero)
{
    if (autorizaAlfil(diferencia, nodoSobrevolado, miTablero))
        return true;
    else return autorizaTorre(diferencia, nodoSobrevolado, miTablero);
}

bool Autorizaciones::autorizaRey(posicion diferencia, posicion nodoSobrevolado, Tablero* miTablero)
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

                    if ((!miTablero->getTurnoNegras() && nodoSobrevolado.Fila == 0) ||
                            (miTablero->getTurnoNegras() && nodoSobrevolado.Fila == 7)){


                        if(diferencia.Columna == 2)
                        {
                            std::cout  << "mueve a la derecha "<<std::endl;

                            return verificaCamino(diferencia.Columna, nodoSobrevolado, 4, miTablero->casillasInt);
                        }


                        if(diferencia.Columna == -2)
                        {
                            std::cout  << "mueve a la izquierda "<<std::endl;

                            return verificaCamino(diferencia.Columna, nodoSobrevolado, 3, miTablero->casillasInt);
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
        return verificaCamino(diferencia.Fila, nodoSobrevolado, 2, elTablero->casillasInt);

    else if (diferencia.Columna==0
             && diferencia.Fila > 0 )  //MOVIMIENTO A LA IZQUIERDA
        return verificaCamino(diferencia.Fila, nodoSobrevolado, 1, elTablero->casillasInt);

    else if (diferencia.Fila==0
             && diferencia.Columna > 0 )  //MOVIMIENTO ARRIBA
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 4, elTablero->casillasInt);

    else if (diferencia.Fila==0
             && diferencia.Columna < 0 ) //MOVIMIENTO ABAJO
        return verificaCamino(diferencia.Columna, nodoSobrevolado, 3, elTablero->casillasInt);

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

bool Autorizaciones::verificaCamino(int distancia, posicion _nodoNuevo, int camino, int* casillas)
{
    bool invertido;
    if (distancia < 0)
    {
        invertido = true;
        distancia = -distancia;


    }

    std::cout  << "posicion FILA: "<<_nodoNuevo.Fila <<" COL: "<<_nodoNuevo.Columna<<std::endl;

    int colDestino = _nodoNuevo.Columna;//-(nuevo.z/10);
    int filaDestino =_nodoNuevo.Fila; //-(nuevo.x/10);


    for (int i = 1; i < distancia; i++)
    {
      //  std::cout  << "FOR! " <<std::endl;

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

        std::cout  << "VERIFICA: "<<( 24+(filaDestino*12) + (colDestino)+2)<<std::endl;


        if (casillas[24+(filaDestino*12) + colDestino+2] != 0)
            return false;
    }
    return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Autorizaciones::generaMovimientos(TableroPrueba* miTablero)
{
    // TableroPrueba nuevoTablero;
    //  std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!" << std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    std::cout << "generamov"<< std::endl;


    miTablero->vectorMov.clear();

    std::cout << "generamov222"<< std::endl;


    int rey = 6;
    int reina = 5;
    int torre = 4;
    int alfil = 3;
    int caballo = 2;
    int peon = 1;

    if (miTablero->turnoN){
        normalizaTablero(miTablero->casillasInt);
    }


    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {
           // std::cout << "FOR"<< miTablero->casillasInt[(i*12)+y] << std::endl;


            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (miTablero->casillasInt[(i*12)+y] == rey)
            {
                std::cout << "REY"<< std::endl;


                //ENCUENTRA REY BLANCO

                mueveRey(miTablero, (i*12)+y);

            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (miTablero->casillasInt[(i*12)+y] == reina)
            {

                //ENCUENTRA REY BLANCO

                mueveReina(miTablero, (i*12)+y);

            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (miTablero->casillasInt[(i*12)+y] == torre)
            {

                //ENCUENTRA REY BLANCO

                mueveTorre(miTablero, (i*12)+y);

            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (miTablero->casillasInt[(i*12)+y] == alfil)
            {


                //ENCUENTRA REY BLANCO

                mueveAlfil(miTablero, (i*12)+y);

            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (miTablero->casillasInt[(i*12)+y] == caballo)
            {

                //ENCUENTRA REY BLANCO

                mueveCaballo(miTablero, (i*12)+y);

            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (miTablero->casillasInt[(i*12)+y] == peon)
            {
                std::cout << "!!!!!!!!!!!!!!!!!!UN MUEVE PEON!!!!!!!!!!!!!!!!!!!" << std::endl;


                //ENCUENTRA REY BLANCO

                muevePeon(miTablero, (i*12)+y);
                //   std::cout << "!!!!!!!!!!!!!!!!!!ACABA MUEVE PEON!!!!!!!!!!!!!!!!!!!" << std::endl;


            }


        }
    }

    std::cout << "!!!!!!!!!!!!!!!!!!ACABA MOVI!!!!!!!!!!!!!!!!!!!: "<<  miTablero->vectorMov.size()<< std::endl;
    if (miTablero->turnoN){
        normalizaTablero(miTablero->casillasInt);
    }

    if (miTablero->vectorMov.size() == 0){
        std::cout << "JAQUE MATE O AHOGADO!!!!!!!!!!: "<< std::endl;

    }
    //  std::cout << "generamov"<< std::endl;



}

//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?



bool Autorizaciones::mueveTorre(TableroPrueba* miTablero,const int casilla)
{
    //mueve a todas las casillas posibles

    //mira si esta ocupada

    int nuevaCasilla = casilla-1;
    bool come = false;
    bool pasa = false;

    while(nuevaCasilla%12 >2)
    {

        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;
        } else break;

        nuevaCasilla = nuevaCasilla-1;
    }

    nuevaCasilla = casilla+1;
    pasa = false;
    while(nuevaCasilla%12 <10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;

        } else break;
        nuevaCasilla = nuevaCasilla+1;
    }

    nuevaCasilla = casilla-12;
    pasa = false;
    while(nuevaCasilla/12 > 2)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;

        } else break;
        nuevaCasilla = nuevaCasilla-12;
    }

    nuevaCasilla = casilla+12;
    pasa = false;
    while(nuevaCasilla/12 < 10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;
        } else break;
        nuevaCasilla = nuevaCasilla+12;
    }
}


bool Autorizaciones::mueveReina(TableroPrueba* miTablero, int casilla)
{
    mueveTorre(miTablero, casilla);
    mueveAlfil(miTablero, casilla);
}

void Autorizaciones::muevePeon(TableroPrueba* miTablero, int casilla)
{
    int nuevaCasilla;
    int casillaCome;
    int casillaComeSec;
    int salto;


    //FALTA AL PASO!!!!!!!!!!!!!!!!!!!!!



    if (miTablero->turnoN)
    {
        //  std::cout << "!!!!!!!!!!!TURNO NEGRAS!!!!!!!!!!" << std::endl;
        salto = casilla-24;
        nuevaCasilla = casilla-12;
        casillaCome = casilla-11;
        casillaComeSec= casilla-13;
        //  std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        // std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if(casilla > 96 && miTablero->casillasInt[salto] == 0)
        {

            aplicaMovimiento(*miTablero, casilla, salto);
        }

        if(miTablero->casillasInt[nuevaCasilla] == 0)
        {
            //PROMOCION A REINA
            if (nuevaCasilla < 36)
            {
                //        miTablero->casillasInt[nuevaCasilla] = 0;
                //        peonEnemigo == true;

                miTablero->casillasInt[casilla] = 5;
            }

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }

        //   nuevaCasilla = casilla+1;
        //    bool peonEnemigo = false;

        if (miTablero->casillasInt[casillaCome] < 0 || (miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaCome] == 0))
        {

            std::cout << "NEGRAS COME O AL PASO 1"<< std::endl;



            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if (miTablero->casillasInt[casillaComeSec] < 0 || (miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaComeSec] == 0))
        {
            std::cout << "NEGRAS COME O AL PASO 2"<< std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }
    }else
    {
        salto = casilla+24;
        nuevaCasilla = casilla+12;
        casillaCome = casilla+11;
        casillaComeSec= casilla+13;



        if(casilla < 48 && miTablero->casillasInt[salto] == 0 )
        {
              std::cout << "!MIRA SI LAS BLANCAS SALTAN!!!!!!" << std::endl;

            aplicaMovimiento(*miTablero, casilla, salto);
        }


        //   std::cout << "!!!!!!!!!!!TURNO BLANCAS!!!!!!!!!!" << std::endl;
        if (miTablero->casillasInt[nuevaCasilla] == 0)
        {
            if (nuevaCasilla > 122){
                miTablero->casillasInt[casilla] = 5;
            }
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }
        //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        //std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if (miTablero->casillasInt[casillaCome] < 0 || (miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaCome] == 0 ))
        {
            std::cout << "BLANCAS COME O AL PASO 1"<< std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if (miTablero->casillasInt[casillaComeSec] < 0 || (miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaComeSec] == 0))
        {
            std::cout << "BLANCAS COME O AL PASO 2"<< std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }
    }

    // std::cout << "!!!!FIN!!!!!!!!!!!!!!!: "  <<std::endl;

    //  for (int i = 0;  i< miTablero->vectorMov.size(); i++)
    //    {
    //     TableroPrueba puntTab = miTablero->vectorMov.at(i);
    //      std::cout << "!!!MUEVE DE: " <<    puntTab.movimiento[0]  << std::endl;
    //      std::cout << "!!!A: " <<    puntTab.movimiento[1]  << std::endl;

    //  }
}

bool Autorizaciones::mueveAlfil(TableroPrueba* miTablero, int casilla)
{
    int nuevaCasilla = casilla-13;

    bool pasa = false;
    bool come;

    while(nuevaCasilla%12 >2 && nuevaCasilla/12 >2)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;

        } else break;

        nuevaCasilla = nuevaCasilla-13;
    }

    nuevaCasilla = casilla-11;
    pasa = false;
    while(nuevaCasilla%12 < 10 && nuevaCasilla/12 >2)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;

        } else break;

        nuevaCasilla = nuevaCasilla-11;
    }

    nuevaCasilla = casilla+13;
    pasa = false;
    while(nuevaCasilla%12 < 10 && nuevaCasilla/12 < 10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;
        } else break;

        nuevaCasilla = nuevaCasilla+13;
    }

    nuevaCasilla = casilla+11;
    pasa = false;
    while(nuevaCasilla%12 >2 && nuevaCasilla/12 < 10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;
        } else break;

        nuevaCasilla = nuevaCasilla+11;
    }
}

bool Autorizaciones::mueveCaballo(TableroPrueba* miTablero, int casilla)
{
    //HAY QUE HACERLO A PARTIR DE UNA POSICION

    int nuevaCasilla;

    nuevaCasilla = casilla-25;


    bool pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }

    nuevaCasilla = casilla-23;



    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }




    nuevaCasilla = casilla+25;


    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla+23;


    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla-10;


    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla-14;


    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla+10;


    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla+14;


    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }


    /*
    diferencia[0]=-dif2;
    diferencia[1] = dif1;
    diferencia[1] = -dif1;



    diferencia[0] = dif2;
    diferencia[1] = dif1;
    diferencia[1] = -dif1;



    diferencia[0] = dif1;
    diferencia[1] = dif2;
    diferencia[1] = -dif2;



    diferencia[0] == -dif1;
    diferencia[1] == dif2;
    diferencia[1] == -dif2;
*/
    // std::list<int> lista;

    //devuelve una lista con todas las nuevas posiciones?
}

bool Autorizaciones::mueveRey(TableroPrueba* miTablero, int casilla)
{
    std::cout << "MUEVE REY"<< miTablero->turnoN<< std::endl;



    int nuevaCasilla;



    bool pasa = false;



    if (casilla < 36)
    {
        //ENROQUE CORTO
        bool torre = false;
        nuevaCasilla = casilla-3;

        pasa = false;

        torre = miTablero->casillasInt[nuevaCasilla] == 4;

        if (torre && miTablero->casillasInt[casilla-2] == 0&& miTablero->casillasInt[casilla-1] == 0)
        {

            nuevaCasilla = casilla-2;

            miTablero->casillasInt[casilla-3] = 0;


            miTablero->casillasInt[casilla-1] = 4;


            std::cout << "APLICA MOVIMIENTO REY -3 (enroque)"<< std::endl;

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);

        }
    }

    if (casilla > 122)
    {
        //ENROQUE LARGO
        bool torre = false;
        nuevaCasilla = casilla+4;

        pasa = false;
        torre = miTablero->casillasInt[nuevaCasilla] == 4;

        if (torre && miTablero->casillasInt[casilla+2] == 0 && miTablero->casillasInt[casilla+1] == 0 && miTablero->casillasInt[casilla+3] == 0)
        {

            nuevaCasilla = casilla+2;

            miTablero->casillasInt[casilla+4] = 0;


            miTablero->casillasInt[casilla+1] = 4;

            std::cout << "APLICA MOVIMIENTO REY +4 (enroque)"<< std::endl;

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);

        }



    }

    //IZQUIERDA

    pasa = false;
    nuevaCasilla = casilla-1;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa){


        std::cout << "APLICA MOVIMIENTO REY -1"<< std::endl;


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }

    //DERECHA
    nuevaCasilla = casilla+1;
    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa){
        //  miTablero->fichaMovida = "REY!!!!";


        std::cout << "APLICA MOVIMIENTO REY +1"<< std::endl;


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);



    }

    //ATRAS
    nuevaCasilla = casilla-12;

    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa){


        std::cout << "APLICA MOVIMIENTO REY -12"<< std::endl;


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);

    }

    //ADELANTE
    nuevaCasilla = casilla+12;

    pasa = false;


    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        //  TableroMovido->fichaMovida = "REY!!!!";

        std::cout << "APLICA MOVIMIENTO REY +12"<< std::endl;


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);




    }

    //NE
    nuevaCasilla = casilla+13;

    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        //    TableroMovido->fichaMovida = "REY!!!!";

        std::cout << "APLICA MOVIMIENTO REY +13"<< std::endl;


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);





    }

    //NO
    nuevaCasilla = casilla+11;

    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        std::cout << "APLICA MOVIMIENTO REY +11"<< std::endl;


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }


    //SO
    nuevaCasilla = casilla-13;
    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";

        std::cout << "APLICA MOVIMIENTO REY -13"<< std::endl;


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);



    }


    //SE
    nuevaCasilla = casilla-11;
    pasa = false;

    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";

        std::cout << "APLICA MOVIMIENTO REY -11"<< std::endl;

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);

    }



}

void Autorizaciones::normalizaTablero(int* tablero)
{

    for (int i=0; i<144;i++)
    {
        if (tablero[i] != 0 && tablero[i] != 99)
        {
            tablero[i] = -tablero[i];
        }
    }

}


void Autorizaciones::aplicaMovimiento(TableroPrueba &miTablero, int casOrigen, int casDestino)
{

    if(miTablero.casillasInt[casDestino] != 99)
    {


        TableroPrueba* TableroMovido = new TableroPrueba(miTablero);

        TableroMovido->alPaso = -1;

        int fichaOrigen = miTablero.casillasInt[casOrigen];

        if (fichaOrigen == 1)
        {
            if (miTablero.casillasInt[casDestino] == 0)
            {

                if ((miTablero.alPaso == casDestino-12
                     && (casOrigen == casDestino-13
                         || casOrigen == casDestino-11))
                        ||( miTablero.alPaso == casDestino+12
                            &&(casOrigen == casDestino+13
                               || casOrigen == casDestino+11 )))
                {
                    std::cout << "!!!!!!!!!COME AL PASO!!!!!!:" << miTablero.alPaso << std::endl;
                    std::cout << "ORIGEN:" << casOrigen<< std::endl;

                    std::cout << "DESTINO:" <<casDestino << std::endl;

                    TableroMovido->casillasInt[miTablero.alPaso] == 0;
                    TableroMovido->casillasInt[1] == 0;
                }
            }

            if ((casDestino - casOrigen  == 24) || casOrigen - casDestino == 24)
            {

                TableroMovido->alPaso = casDestino;
                std::cout << "!!!!!!!!!DOBLE SALTO EN IA!!!!!!:" <<TableroMovido->alPaso <<std::endl;

            }

        }

        //   std::cout << "!!!!!!!!!FICHA ORIGEN!!!!!!:" << fichaOrigen << std::endl;

        //     std::cout << "!!!!!!!!!FICHA DESTINO!!!!!!:" << miTablero.casillasInt[casDestino] << std::endl;

        TableroMovido->casillasInt[casOrigen] = 0;

        TableroMovido->casillasInt[casDestino] = fichaOrigen;

        TableroMovido->movimiento[0] = casOrigen;
        TableroMovido->movimiento[1] = casDestino;


        //   std::cout << "!!!!!!LE METE AL VECTOR" << std::endl;

        if (evaluaJaque(TableroMovido->casillasInt, TableroMovido->turnoN))
        {

            //  std::cout << "!!!!!HA EVALUADO UN JAQUE (DESPUES DE MOVER) POR LO QUE NO AÑADE AL VECTOR!!!" << std::endl;

        }else
        {
            TableroMovido->turnoN = !miTablero.turnoN;

            miTablero.vectorMov.push_back(TableroMovido);

            // miTablero.numeroHijos++;
        }
    }
}
