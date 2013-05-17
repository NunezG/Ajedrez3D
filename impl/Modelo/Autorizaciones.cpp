#include "../../headers/Modelo/Autorizaciones.h"



bool Autorizaciones::autorizaCasilla(ModeloTablero* miTablero,  tipoFicha tipo, int filaSel, int colSel,  int filaNueva, int colNueva)
{




    int filaDif = filaNueva - filaSel;
   int colDif = colNueva - colSel;


    int fichaSobrevolada = miTablero->casillasInt[24+(filaNueva*12)+colNueva+2];
    //MIRA SI ES COMESTIBLE (FICHA ENEMIGA)


    if(fichaSobrevolada <= 0)
    {

        switch (tipo)
        {
        case Rey: //REY SELECCIONADO

            return autorizaRey( filaDif, colDif,filaNueva,colNueva, miTablero);
            break;

        case Reina: //REINA SELECCIONADO

            return autorizaReina(filaDif, colDif,filaNueva,colNueva, miTablero->casillasInt);
            break;

        case Alfil: //ALFIL SELECCIONADO

            return autorizaAlfil(filaDif, colDif,filaNueva,colNueva, miTablero->casillasInt);
            break;

        case Torre: //TORRE SELECCIONADA

            return autorizaTorre(filaDif, colDif,filaNueva,colNueva, miTablero->casillasInt);
            break;

        case Caballo: //CABALLO SELECCIONADO

            return autorizaCaballo(filaDif, colDif);
            break;

        case Peon: //PEON SELECCIONADO


             return autorizaPeon(filaDif, colDif, filaNueva,colNueva, filaSel, miTablero);
            break;

        default:
            return false;
            break;
        }


    }

    if (miTablero->turnoN)normalizaTablero(miTablero->casillasInt);


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
            if(ficha != 0)
            {

                //REY
                if(i==1 && ficha == fichaRey)
                    return true;


                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;


                //cualquier otra ficha en medio

                break;
            }

        }

        //S
        ficha= 4;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*12)];

            if(ficha != 0)
            {
                //REY
                if(i==1 && ficha == fichaRey)
                    return true;



                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;


                //ficha en medio

                break;
            }

        }

        //E
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+i];

            if(ficha != 0)
            {
                //REY
                if(i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;


                //ficha en medio

                break;
            }

        }

        //O
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-i];

            if(ficha != 0)
            {
                //REY
                if (i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                //ficha en medio

                break;
            }
        }

        //NE
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*11)];
            if(ficha != 0)
            {
                //REY                               //PEON NEGRO
                if(i==1 && (ficha == fichaRey || (!turnoNegras && ficha == fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                else if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //NO
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*13)];
            if(ficha != 0)
            {
                //REY                               //PEON NEGRO
                if(i==1 && (ficha == fichaRey || (!turnoNegras && ficha ==fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //SE

        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*11)];

            if(ficha != 0)
            {
                //REY                               //PEON BLANCO
                if(i==1 && (ficha == fichaRey || (turnoNegras && ficha ==fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //SO
        ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*13)];

            if(ficha != 0)
            {
                //REY                               //PEON BLANCO
                if(i==1 && (ficha == fichaRey || (turnoNegras && ficha ==fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }
        int caballo;

        caballo= posRey-10;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey-14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey-23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;



        caballo= posRey-25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;

        caballo= posRey+10;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;
    }
    return false;
}

bool Autorizaciones::autorizaPeon (int filaDif, int colDif,  int filaNueva, int colNueva,  int filaSel, ModeloTablero* miTablero)
{
    std::cout << "!!!!!!!!!!!AUTORIZA PEON!!!!!!!!!!!!!!" << std::endl;


    if (miTablero->turnoN)
    {
        //Invierte el signo  de la diferencia de los peones negros
        filaDif = -filaDif;
        colDif = -colDif;

    }

    int filaSobreTraducida = 24 + (filaNueva * 12);

    //std::cout << "!!!!!!!!DIFERENCIA: " <<   diferencia.Fila<<" col!!!!!!!!: " <<diferencia.Columna << std::endl;
    //std::cout << "!!!!!!!!FILa sobrevolada: " <<   nodoSobrevolado.Fila  << std::endl;
    //std::cout << "!!!!!!!!COL sobrevolada: " <<   nodoSobrevolado.Columna<< std::endl;
    //std::cout << "!!!!!!!!FILa seleccionada: " <<   seleccionado.Fila<<" traducida!!!!!!!!" <<filaSobreTraducida << std::endl;
    //std::cout << "!!!!!!!!COL seleccionada: " <<   seleccionado.Columna<<" traducida!!!!!!!!" <<seleccionado.Columna+2 << std::endl;

    if (colDif == 0)
    {
        if (filaDif== 2
                && ((filaSel == 1 && !miTablero->turnoN) || (filaSel == 6 && miTablero->turnoN)))
        {
            //SALTA 2 CASILLAS (ESCAQUES)
            if (miTablero->turnoN)
                return verificaCamino(filaDif, filaNueva, colNueva, 2, miTablero->casillasInt);
            else
                return verificaCamino(filaDif, filaNueva, colNueva, 1, miTablero->casillasInt);
        }
        else if (filaDif == 1)
        {
            //PASA UNA CASILLA
            if (miTablero->casillasInt[filaSobreTraducida + colNueva+2] != 0)
                return false;
            else
                return true;
        }
    }else  if((filaDif == 1 &&( colDif == -1
                                        || colDif == 1)))
    {
        //COME
        if (miTablero->casillasInt[filaSobreTraducida + colNueva+2] != 0)
            return true;
        else if(miTablero->alPaso >= 0)
        {
            //AL PASO
            int filaLateral;
            int colLateral;

            filaLateral = 24 + (filaSel * 12);
            colLateral = colNueva;
            int posCasilla = filaLateral + colLateral + 2;

            if (miTablero->alPaso == posCasilla)
                return true;
        }
    }
    return false;
}

bool Autorizaciones::autorizaAlfil(int filaDif, int colDif,  int filaNueva, int colNueva,  int* elTablero)
{
    if (colDif - filaDif == 0
            && colDif > 0) //Columnas DESCENDENTES Y Filas DESCENDENTES
        return verificaCamino(colDif, filaNueva, colNueva, 8, elTablero);

    else if (colDif + filaDif == 0
             && colDif > 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR DERECHA)
        return verificaCamino(colDif, filaNueva, colNueva, 7, elTablero);

    else if(colDif + filaDif == 0
            && colDif < 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO IZQUIERDA)
        return verificaCamino(colDif, filaNueva, colNueva, 6, elTablero);

    else if(colDif - filaDif == 0
            && colDif  < 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ABAJO DERECHA)
        return verificaCamino(colDif, filaNueva, colNueva, 5, elTablero);

    else return false;
}

bool Autorizaciones::autorizaReina(int filaDif, int colDif,  int filaNueva, int colNueva, int* miTablero)
{
    if (autorizaAlfil(filaDif, colDif, filaNueva, colNueva, miTablero))
        return true;
    else return autorizaTorre(filaDif, colDif, filaNueva, colNueva, miTablero);
}

bool Autorizaciones::autorizaRey(int filaDif, int colDif,  int filaNueva, int colNueva, ModeloTablero* miTablero)
{
    if ((filaDif==1||filaDif==-1||filaDif==0)
            && (colDif==1||colDif==-1||colDif==0))
        return true;
    else{
        //ENROQUE
        if (filaDif == 0 && ((!miTablero->turnoN && filaNueva == 0) ||
                                     (miTablero->turnoN && filaNueva == 7)))
        {
            int posCasilla = filaNueva * 12; //ES SIEMPRE LA PRIMERA COLUMNA

            if(colDif == 2) //derecha (enroque corto)
            {
                if(miTablero->casillasInt[posCasilla+7] == Torre)
                    return verificaCamino(colDif+1, filaNueva, colNueva, 4, miTablero->casillasInt);

            }
            else if(colDif == -2)   //izquierda (enroque largo)
            {

                if(miTablero->casillasInt[posCasilla] == Torre)
                    return verificaCamino(colDif - 2, filaNueva, colNueva, 3, miTablero->casillasInt);
            }

        }
        return false;
    }
}

bool Autorizaciones::autorizaTorre(int filaDif, int colDif,  int filaNueva, int colNueva,  int* elTablero)
{


    if (colDif == 0
            && filaDif < 0 ) //MOVIMIENTO A LA DERECHA
        return verificaCamino(colDif, filaNueva, colNueva, 2, elTablero);

    else if (colDif==0
             && filaDif > 0 )  //MOVIMIENTO A LA IZQUIERDA
        return verificaCamino(colDif, filaNueva, colNueva, 1, elTablero);

    else if (filaDif==0
             && colDif > 0 )  //MOVIMIENTO ARRIBA
        return verificaCamino(colDif, filaNueva, colNueva, 4, elTablero);

    else if (filaDif==0
             && colDif < 0 ) //MOVIMIENTO ABAJO
        return verificaCamino(colDif, filaNueva, colNueva, 3, elTablero);

    else return false;
}



bool Autorizaciones::autorizaCaballo(int filaDif, int colDif)
{
    if (filaDif < 0) filaDif = -filaDif;
    if (colDif < 0) colDif = -colDif;

    if ((filaDif == 2 && colDif == 1)
            || (filaDif == 1 && colDif == 2))
        return true;
    else return false;
}

bool Autorizaciones::verificaCamino(int distancia,  int filaNueva,int colNueva, int camino, int* casillas)
{
    bool invertido;
    if (distancia < 0)
    {
        invertido = true;
        distancia = -distancia;


    }

    int colDestino = colNueva;//-(nuevo.z/10);
    int filaDestino =filaNueva; //-(nuevo.x/10);


    for (int i = 1; i < distancia; i++)
    {

        if (camino == 1) filaDestino = filaDestino-1;  // ABAJO
        else if (camino == 2) filaDestino = filaDestino+1; // ARRIBA
        else if (camino == 3) colDestino = colDestino+1; // DERECHA
        else if (camino == 4) colDestino = colDestino-1; // IZQUIERDA
        else if (camino == 5)
        { //MOVIMIENTO DIAGONAL ARRIBA DERECHA
            colDestino = colDestino+1;
            filaDestino = filaDestino+1;
        }
        else if (camino == 6)
        { //MOVIMIENTO DIAGONAL ABAJO DERECHA
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



        if (casillas[24+(filaDestino*12) + colDestino+2] != 0)
            return false;
    }
    return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Autorizaciones::generaMovimientos(ModeloTablero* miTablero)
{
    // ModeloTablero nuevoTablero;
    //  std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!" << std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS



    miTablero->vectorMov.clear();



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
                std::cout << "!!!!!!!!!!!!!!!!!!UN MUEVE PEON!!!!!!!!!!!!!!!!!!! EN CASILLA: "<<(i*12)+y << std::endl;


                //ENCUENTRA REY BLANCO

                muevePeon(miTablero, (i*12)+y);
                //   std::cout << "!!!!!!!!!!!!!!!!!!ACABA MUEVE PEON!!!!!!!!!!!!!!!!!!!" << std::endl;


            }


        }
    }

    if (miTablero->turnoN){
        normalizaTablero(miTablero->casillasInt);
    }

    if (miTablero->vectorMov.size() == 0){
        std::cout << "JAQUE MATE O AHOGADO!!!!!!!!!!: "<< std::endl;

    }
    //  std::cout << "generamov"<< std::endl;



}

//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?



bool Autorizaciones::mueveTorre(ModeloTablero* miTablero,const int casilla)
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


bool Autorizaciones::mueveReina(ModeloTablero* miTablero, int casilla)
{
    mueveTorre(miTablero, casilla);
    mueveAlfil(miTablero, casilla);
}

void Autorizaciones::muevePeon(ModeloTablero* miTablero, int casilla)
{
    int nuevaCasilla;
    int casillaCome;
    int casillaComeSec;
    int salto;

    if (miTablero->turnoN)
    {
        std::cout << "!!!!!!!!!!!TURNO NEGRAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla-24;
        nuevaCasilla = casilla-12;
        casillaCome = casilla-11;
        casillaComeSec= casilla-13;
        //  std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        // std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if(casilla > 96 && miTablero->casillasInt[salto] == 0)
        {
            std::cout << "!!!!!!!!!!!SALTA  NEGRAS!!!!!!!!" << std::endl;

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
            std::cout << "!!!!!!MUEVE NORMAL NEGRAS!!!!!!" << std::endl;

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }

        //   nuevaCasilla = casilla+1;
        //    bool peonEnemigo = false;

        if (miTablero->casillasInt[casillaCome] < 0)
        {
            std::cout << "NEGRAS COME 1"<< std::endl;
            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if(miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaCome] == 0)
        {
            std::cout << "NEGRAS COME AL PASO 1"<< std::endl;

            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }
        if (miTablero->casillasInt[casillaComeSec] < 0)
        {
            std::cout << "NEGRAS COME 2"<< std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }

        if ((miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaComeSec] == 0))
        {
            std::cout << "NEGRAS COME AL PASO 2"<< std::endl;
            aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }

    }else
    {
        std::cout << "!!!!!!!!!!!TURNO BLANCAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla+24;
        nuevaCasilla = casilla+12;
        casillaCome = casilla+11;
        casillaComeSec= casilla+13;



        if(casilla < 48 && miTablero->casillasInt[salto] == 0 )
        {
            std::cout << "!BLANCAS SALTAN!!!!!!" << std::endl;

            aplicaMovimiento(*miTablero, casilla, salto);
        }


        //   std::cout << "!!!!!!!!!!!TURNO BLANCAS!!!!!!!!!!" << std::endl;
        if (miTablero->casillasInt[nuevaCasilla] == 0)
        {
            if (nuevaCasilla > 122){
                miTablero->casillasInt[casilla] = 5;
            }
            std::cout << "!!!!!!!!!!! BLANCAS AVANZA!!!!!!!!!!" << std::endl;

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }
        //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        //std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if (miTablero->casillasInt[casillaCome] < 0)
        {
            std::cout << "BLANCAS COME 1"<< std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if ((miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaCome] == 0 ))
        {
            std::cout << "BLANCAS COME AL PASO 1"<< std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }


        if (miTablero->casillasInt[casillaComeSec] < 0 )
        {
            std::cout << "BLANCAS COME 2"<< std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }


        if ((miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaComeSec] == 0))
        {
            std::cout << " BLANCAS COME AL PASO 2, casilla: "<< casilla << " CASILLA COME SEC: "<<casillaComeSec << " ALPASO: "<<miTablero->alPaso<<std::endl;


            aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }
    }

    // std::cout << "!!!!FIN!!!!!!!!!!!!!!!: "  <<std::endl;

    //  for (int i = 0;  i< miTablero->vectorMov.size(); i++)
    //    {
    //     ModeloTablero puntTab = miTablero->vectorMov.at(i);
    //      std::cout << "!!!MUEVE DE: " <<    puntTab.movimiento[0]  << std::endl;
    //      std::cout << "!!!A: " <<    puntTab.movimiento[1]  << std::endl;

    //  }
}

bool Autorizaciones::mueveAlfil(ModeloTablero* miTablero, int casilla)
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

bool Autorizaciones::mueveCaballo(ModeloTablero* miTablero, int casilla)
{
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
}

bool Autorizaciones::mueveRey(ModeloTablero* miTablero, int casilla)
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
            tablero[i] = -tablero[i];
    }
}


void Autorizaciones::aplicaMovimiento(ModeloTablero &miTablero, int casOrigen, int casDestino)
{

    if(miTablero.casillasInt[casDestino] != 99)
    {
        ModeloTablero* TableroMovido = new ModeloTablero(miTablero);

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
            delete TableroMovido;
            //  std::cout << "!!!!!HA EVALUADO UN JAQUE (DESPUES DE MOVER) POR LO QUE NO AÑADE AL VECTOR!!!" << std::endl;
        }else
        {
            TableroMovido->turnoN = !miTablero.turnoN;

            miTablero.vectorMov.push_back(TableroMovido);

            // miTablero.numeroHijos++;
        }
    }
}
