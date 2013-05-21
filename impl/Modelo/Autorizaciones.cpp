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


