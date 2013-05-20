#include "../../headers/Modelo/Autorizaciones.h"






bool Autorizaciones::autoriza(int* tablero,  tipoFicha tipo, int filaSel, int colSel,  int filaNueva, int colNueva, bool turnoNegas, int alPaso)
{
    int filaDif = filaNueva - filaSel;
    int colDif = colNueva - colSel;

    int fichaSobrevolada = tablero[24+(filaNueva*12)+colNueva+2];
    //MIRA SI ES COMESTIBLE (FICHA ENEMIGA)

    if(fichaSobrevolada <= 0)
    {
        switch (tipo)
        {
        case Rey: //REY SELECCIONADO

            return autorizaRey( filaDif, colDif,filaNueva,colNueva, tablero, turnoNegas);
            break;

        case Reina: //REINA SELECCIONADO

            return autorizaReina(filaDif, colDif,filaNueva,colNueva, tablero);
            break;

        case Alfil: //ALFIL SELECCIONADO

            return autorizaAlfil(filaDif, colDif,filaNueva,colNueva, tablero);
            break;

        case Torre: //TORRE SELECCIONADA

            return autorizaTorre(filaDif, colDif,filaNueva,colNueva, tablero);
            break;

        case Caballo: //CABALLO SELECCIONADO

            return autorizaCaballo(filaDif, colDif);
            break;

        case Peon: //PEON SELECCIONADO

            return autorizaPeon(filaDif, colDif, filaNueva,colNueva, filaSel, tablero,turnoNegas,alPaso);
            break;

        default:
            return false;
            break;
        }
    }
   // if (turnoNegas)normalizaTablero(tablero);
}

bool Autorizaciones::autorizaPeon (int filaDif, int colDif,  int filaNueva, int colNueva,  int filaSel, int* tablero, bool turnoNegras, int alPaso)
{
    std::cout << "!!!!!!!!!!!AUTORIZA PEON!!!!!!!!!!!!!!" << std::endl;

    if (turnoNegras)
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
                && ((filaSel == 1 && !turnoNegras) || (filaSel == 6 && turnoNegras)))
        {
            //SALTA 2 CASILLAS (ESCAQUES)
            if (turnoNegras)
                return verificaCamino(filaDif, filaNueva, colNueva, 2, tablero);
            else
                return verificaCamino(filaDif, filaNueva, colNueva, 1, tablero);
        }
        else if (filaDif == 1)
        {
            //PASA UNA CASILLA
            if (tablero[filaSobreTraducida + colNueva+2] != 0)
                return false;
            else
                return true;
        }
    }else  if((filaDif == 1 &&( colDif == -1
                                || colDif == 1)))
    {
        //COME
        if (tablero[filaSobreTraducida + colNueva+2] != 0)
            return true;
        else if(alPaso >= 0)
        {
            //AL PASO
            int filaLateral;
            int colLateral;

            filaLateral = 24 + (filaSel * 12);
            colLateral = colNueva;
            int posCasilla = filaLateral + colLateral + 2;

            if (alPaso == posCasilla)
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

bool Autorizaciones::autorizaRey(int filaDif, int colDif,  int filaNueva, int colNueva, int* miTablero, bool turnoNegras)
{
    if ((filaDif==1||filaDif==-1||filaDif==0)
            && (colDif==1||colDif==-1||colDif==0))
        return true;
    else{
        //ENROQUE
        if (filaDif == 0 && ((!turnoNegras && filaNueva == 0) ||
                             (turnoNegras && filaNueva == 7)))
        {
            int posCasilla = filaNueva * 12; //ES SIEMPRE LA PRIMERA COLUMNA

            if(colDif == 2) //derecha (enroque corto)
            {
                if(miTablero[posCasilla+7] == Torre)
                    return verificaCamino(colDif+1, filaNueva, colNueva, 4, miTablero);

            }
            else if(colDif == -2)   //izquierda (enroque largo)
            {

                if(miTablero[posCasilla] == Torre)
                    return verificaCamino(colDif - 2, filaNueva, colNueva, 3, miTablero);
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




bool Autorizaciones::mueveTorre(int* tablero,const int casilla)
{
    //mueve a todas las casillas posibles

    //mira si esta ocupada

    int nuevaCasilla = casilla-1;
    bool come = false;
    bool pasa = false;

    while(nuevaCasilla%12 >2)
    {

        pasa = tablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = tablero[nuevaCasilla] != 0;
            if (come) return true;
        } else return true; //

        nuevaCasilla = nuevaCasilla-1;
    }

    nuevaCasilla = casilla+1;
    pasa = false;
    while(nuevaCasilla%12 <10)
    {
        pasa = tablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = tablero[nuevaCasilla] != 0;
            if (come) return true;

        } else return true;
        nuevaCasilla = nuevaCasilla+1;
    }

    nuevaCasilla = casilla-12;
    pasa = false;
    while(nuevaCasilla/12 > 2)
    {
        pasa = tablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = tablero[nuevaCasilla] != 0;
            if (come) return true;

        } else return true;
        nuevaCasilla = nuevaCasilla-12;
    }

    nuevaCasilla = casilla+12;
    pasa = false;
    while(nuevaCasilla/12 < 10)
    {
        pasa = tablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = tablero[nuevaCasilla] != 0;
            if (come) return true;
        } else return true;
        nuevaCasilla = nuevaCasilla+12;
    }
}


bool Autorizaciones::mueveReina(int* tablero, int casilla)
{
    mueveTorre(tablero, casilla);
    mueveAlfil(tablero, casilla);
}

bool Autorizaciones::muevePeon(int* tablero, int casilla, bool turnoNegras, int alPaso)
{
    int nuevaCasilla;
    int casillaCome;
    int casillaComeSec;
    int salto;

    if (turnoNegras)
    {
        std::cout << "!!!!!!!!!!!TURNO NEGRAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla-24;
        nuevaCasilla = casilla-12;
        casillaCome = casilla-11;
        casillaComeSec= casilla-13;
        //  std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        // std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if(casilla > 96 && tablero[salto] == 0)
        {
            std::cout << "!!!!!!!!!!!SALTA  NEGRAS!!!!!!!!" << std::endl;

            return true;
            //     aplicaMovimiento(*miTablero, casilla, salto);
        }

        if(tablero[nuevaCasilla] == 0)
        {
            //PROMOCION A REINA
            if (nuevaCasilla < 36)
            {
                //        miTablero->casillasInt[nuevaCasilla] = 0;
                //        peonEnemigo == true;

                tablero[casilla] = 5;
            }
            std::cout << "!!!!!!MUEVE NORMAL NEGRAS!!!!!!" << std::endl;
            return true;

            //  aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }

        //   nuevaCasilla = casilla+1;
        //    bool peonEnemigo = false;

        if (tablero[casillaCome] < 0)
        {
            std::cout << "NEGRAS COME 1"<< std::endl;
            return true;

            // aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if(alPaso == casilla+1 && tablero[casillaCome] == 0)
        {
            std::cout << "NEGRAS COME AL PASO 1"<< std::endl;
            return true;
            //  aplicaMovimiento(*miTablero, casilla, casillaCome);
        }
        if (tablero[casillaComeSec] < 0)
        {
            std::cout << "NEGRAS COME 2"<< std::endl;
            return true;
            //aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }

        if ((alPaso == casilla-1 && tablero[casillaComeSec] == 0))
        {
            std::cout << "NEGRAS COME AL PASO 2"<< std::endl;
            return true;
            //  aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }

    }else
    {
        std::cout << "!!!!!!!!!!!TURNO BLANCAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla+24;
        nuevaCasilla = casilla+12;
        casillaCome = casilla+11;
        casillaComeSec= casilla+13;

        if(casilla < 48 && tablero[salto] == 0 )
        {
            std::cout << "!BLANCAS SALTAN!!!!!!" << std::endl;
            return true;

            //  aplicaMovimiento(*miTablero, casilla, salto);
        }


        //   std::cout << "!!!!!!!!!!!TURNO BLANCAS!!!!!!!!!!" << std::endl;
        if (tablero[nuevaCasilla] == 0)
        {
            if (nuevaCasilla > 122){
                tablero[casilla] = 5;
            }
            std::cout << "!!!!!!!!!!! BLANCAS AVANZA!!!!!!!!!!" << std::endl;
            return true;

            // aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }
        //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        //std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->tablero[nuevaCasilla] << std::endl;

        if (tablero[casillaCome] < 0)
        {
            std::cout << "BLANCAS COME 1"<< std::endl;

            return true;

            // aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if ((alPaso == casilla-1 && tablero[casillaCome] == 0 ))
        {
            std::cout << "BLANCAS COME AL PASO 1"<< std::endl;
            return true;


            //  aplicaMovimiento(*miTablero, casilla, casillaCome);
        }


        if (tablero[casillaComeSec] < 0 )
        {
            std::cout << "BLANCAS COME 2"<< std::endl;

            return true;

            // aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }


        if ((alPaso == casilla+1 && tablero[casillaComeSec] == 0))
        {
            std::cout << " BLANCAS COME AL PASO 2, casilla: "<< casilla << " CASILLA COME SEC: "<<casillaComeSec << " ALPASO: "<<alPaso<<std::endl;

            return true;

            // aplicaMovimiento(*miTablero, casilla, casillaComeSec);
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

bool Autorizaciones::mueveAlfil(int* miTablero, int casilla)
{
    int nuevaCasilla = casilla-13;

    bool pasa = false;
    bool come;

    while(nuevaCasilla%12 >2 && nuevaCasilla/12 >2)
    {
        pasa = miTablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero[nuevaCasilla] != 0;
            if (come)             return true;


        } else return true;

        nuevaCasilla = nuevaCasilla-13;
    }

    nuevaCasilla = casilla-11;
    pasa = false;
    while(nuevaCasilla%12 < 10 && nuevaCasilla/12 >2)
    {
        pasa = miTablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero[nuevaCasilla] != 0;
            if (come) return true;

        } else return true;

        nuevaCasilla = nuevaCasilla-11;
    }

    nuevaCasilla = casilla+13;
    pasa = false;
    while(nuevaCasilla%12 < 10 && nuevaCasilla/12 < 10)
    {
        pasa = miTablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero[nuevaCasilla] != 0;
            if (come) return true;
        } else return true;

        nuevaCasilla = nuevaCasilla+13;
    }

    nuevaCasilla = casilla+11;
    pasa = false;
    while(nuevaCasilla%12 >2 && nuevaCasilla/12 < 10)
    {
        pasa = miTablero[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero[nuevaCasilla] != 0;
            if (come) return true;
        } else return true;

        nuevaCasilla = nuevaCasilla+11;
    }
}

bool Autorizaciones::mueveCaballo(int* miTablero, int casilla)
{
    int nuevaCasilla;
    nuevaCasilla = casilla-25;
    bool pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        return true;
    }

    nuevaCasilla = casilla-23;
    pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        return true;
    }

    nuevaCasilla = casilla+25;
    pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        return true;
    }

    nuevaCasilla = casilla+23;
    pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;

    if (pasa)
    {
        return true;
    }

    nuevaCasilla = casilla-10;
    pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        return true;
    }

    nuevaCasilla = casilla-14;
    pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        return true;
    }

    nuevaCasilla = casilla+10;
    pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        return true;
    }

    nuevaCasilla = casilla+14;
    pasa = false;
    pasa = miTablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        return true;
    }
}

bool Autorizaciones::mueveRey(int* tablero, int casilla)
{
    std::cout << "MUEVE REY"<< std::endl;

    int nuevaCasilla;
    bool pasa = false;

    if (casilla < 36)
    {
        //ENROQUE CORTO
        bool torre = false;
        nuevaCasilla = casilla-3;

        pasa = false;
        torre = tablero[nuevaCasilla] == 4;
        if (torre && tablero[casilla-2] == 0&& tablero[casilla-1] == 0)
        {
            nuevaCasilla = casilla-2;
            tablero[casilla-3] = 0;
            tablero[casilla-1] = 4;
            std::cout << "APLICA MOVIMIENTO REY -3 (enroque)"<< std::endl;
            return true;
        }
    }

    if (casilla > 122)
    {
        //ENROQUE LARGO
        bool torre = false;
        nuevaCasilla = casilla+4;
        pasa = false;
        torre = tablero[nuevaCasilla] == 4;

        if (torre && tablero[casilla+2] == 0 && tablero[casilla+1] == 0 && tablero[casilla+3] == 0)
        {
            nuevaCasilla = casilla+2;
            tablero[casilla+4] = 0;
            tablero[casilla+1] = 4;
            std::cout << "APLICA MOVIMIENTO REY +4 (enroque)"<< std::endl;
            return true;
        }
    }

    //IZQUIERDA
    pasa = false;
    nuevaCasilla = casilla-1;
    pasa = tablero[nuevaCasilla] <= 0;
    if (pasa){
        std::cout << "APLICA MOVIMIENTO REY -1"<< std::endl;
        return true;
    }

    //DERECHA
    nuevaCasilla = casilla+1;
    pasa = false;
    pasa = tablero[nuevaCasilla] <= 0;

    if (pasa){
        //  miTablero->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY +1"<< std::endl;
        return true;
    }

    //ATRAS
    nuevaCasilla = casilla-12;
    pasa = false;
    pasa = tablero[nuevaCasilla] <= 0;
    if (pasa){
        std::cout << "APLICA MOVIMIENTO REY -12"<< std::endl;
        return true;
    }

    //ADELANTE
    nuevaCasilla = casilla+12;
    pasa = false;
    pasa = tablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        std::cout << "APLICA MOVIMIENTO REY +12"<< std::endl;
        return true;
    }

    //NE
    nuevaCasilla = casilla+13;
    pasa = false;
    pasa = tablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        //    TableroMovido->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY +13"<< std::endl;
        return true;
    }

    //NO
    nuevaCasilla = casilla+11;
    pasa = false;
    pasa = tablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        std::cout << "APLICA MOVIMIENTO REY +11"<< std::endl;
        return true;
    }

    //SO
    nuevaCasilla = casilla-13;
    pasa = false;
    pasa = tablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY -13"<< std::endl;
        return true;
    }

    //SE
    nuevaCasilla = casilla-11;
    pasa = false;
    pasa = tablero[nuevaCasilla] <= 0;
    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY -11"<< std::endl;
        return true;
    }
}




bool Autorizaciones::verificaJaqueMate(int* tablero, bool turnoNegras, int alPaso)
{
    // ModeloTablero nuevoTablero;
    //  std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!" << std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    int rey = 6;
    int reina = 5;
    int torre = 4;
    int alfil = 3;
    int caballo = 2;
    int peon = 1;

    bool resultado = false;

    int ficha = 0;

  //  if (turnoNegras)
 //   {
  //      normalizaTablero(tablero);
 //   }

    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {
            ficha = tablero[(i*12)+y];

            // std::cout << "FOR"<< miTablero->casillasInt[(i*12)+y] << std::endl;


            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (ficha == rey)
            {


                //ENCUENTRA REY BLANCO

                if (mueveRey(tablero, (i*12)+y))
                    return true;
            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (ficha == reina)
            {
                //ENCUENTRA REY BLANCO
                if (mueveReina(tablero, (i*12)+y))
                    return true;
            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (ficha == torre)
            {
                //ENCUENTRA REY BLANCO
                if (mueveTorre(tablero, (i*12)+y))
                    return false;
            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (ficha == alfil)
            {
                //ENCUENTRA REY BLANCO
                if (mueveAlfil(tablero, (i*12)+y))
                    return false;
            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (ficha == caballo)
            {
                //ENCUENTRA REY BLANCO
                if (mueveCaballo(tablero, (i*12)+y))
                    return false;
            }

            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (ficha == peon)
            {
                std::cout << "!!!!!!!!!!!!!!!!!!UN MUEVE PEON!!!!!!!!!!!!!!!!!!! EN CASILLA: "<<(i*12)+y << std::endl;

                //ENCUENTRA REY BLANCO

                if (muevePeon(tablero, (i*12)+y,turnoNegras,alPaso))
                    return false;
                //   std::cout << "!!!!!!!!!!!!!!!!!!ACABA MUEVE PEON!!!!!!!!!!!!!!!!!!!" << std::endl;
            }
        }
    }

    if (turnoNegras)
    {
        normalizaTablero(tablero);
    }

    return true;
}
