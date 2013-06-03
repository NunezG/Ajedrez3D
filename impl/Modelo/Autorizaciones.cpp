#include "../../headers/Modelo/Autorizaciones.h"

bool Autorizaciones::autoriza(ModeloTablero* tablero,  tipoFicha tipo)
{
    int Dif = tablero->jugada[1] - tablero->jugada[0] ;
    //      filaNueva - filaSel;
    //int colDif = colNueva - colSel;


    std::cout << "!!!!!!!!!!!AUTORIZA!!!!!!!!!!!!!!"<< std::endl;

    std::cout << "!!CASILLA SELECCIONADA!!!!!!!!!!" << tablero->jugada[0] << std::endl;
    std::cout << "!!!CASILLA SOBREVOLADA!!!!!!!!" << tablero->jugada[1] << std::endl;



    //int fichaSobrevolada = tablero->casillasInt[24 + (filaNueva*12)+colNueva+2];
    //  std::cout << "!!!!!!!!!!!fichaSOBREVOLADA!!!!!!!!!!!!!!" << 24 + (filaNueva*12)+colNueva+2 << std::endl;

    // std::cout << "!!!!!!!!!!!ficha!!!!!!!!!!!!!!" << fichaSobrevolada << std::endl;

    //MIRA SI ES COMESTIBLE (FICHA ENEMIGA)

    if(tablero->casillasInt[tablero->jugada[1]] <= 0)
    {
        switch (tipo)
        {
        case Rey: //REY SELECCIONADO

            return autorizaRey(tablero);
            break;

        case Reina: //REINA SELECCIONADO

            return autorizaReina(tablero);
            break;

        case Alfil: //ALFIL SELECCIONADO

            return autorizaAlfil(tablero);
            break;

        case Torre: //TORRE SELECCIONADA

            return autorizaTorre(tablero);
            break;

        case Caballo: //CABALLO SELECCIONADO

            return autorizaCaballo(Dif);
            break;

        case Peon: //PEON SELECCIONADO

            return autorizaPeon(tablero);
            break;

        default:
            return false;
            break;
        }
    }else return false;
    // if (turnoNegas)normalizaTablero(tablero);
}

bool Autorizaciones::autorizaPeon (ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0] ;

    std::cout << "!!!!!!!!!!!AUTORIZA PEON!!!!!!!!!!!!!!" << std::endl;

    if (Dif < 0)
    {
        //Invierte el signo  de la diferencia de los peones negros
        Dif = -Dif;
    }

    // int filaSobreTraducida = 24 + (filaNueva * 12);

    //std::cout << "!!!!!!!!DIFERENCIA: " <<   diferencia.Fila<<" col!!!!!!!!: " <<diferencia.Columna << std::endl;
    //std::cout << "!!!!!!!!FILa sobrevolada: " <<   nodoSobrevolado.Fila  << std::endl;
    //std::cout << "!!!!!!!!COL sobrevolada: " <<   nodoSobrevolado.Columna<< std::endl;
    //std::cout << "!!!!!!!!FILa seleccionada: " <<   seleccionado.Fila<<" traducida!!!!!!!!" <<filaSobreTraducida << std::endl;
    //std::cout << "!!!!!!!!COL seleccionada: " <<   seleccionado.Columna<<" traducida!!!!!!!!" <<seleccionado.Columna+2 << std::endl;

    if (Dif== 24
            && ((miTablero->jugada[0]/12 == 3 && !miTablero->turnoN) || (miTablero->jugada[0]/12 == 8 && miTablero->turnoN)))
    {
        //SALTA 2 CASILLAS (ESCAQUES)
        if (miTablero->turnoN)
            return pruebaCamino(miTablero, -12);
        else
            return pruebaCamino(miTablero, 12);
    }
    else if (Dif == 12)
    {
        //PASA UNA CASILLA
        if (miTablero->casillasInt[miTablero->jugada[1]] != 0)
            return false;
        else
            return true;
    }
    else if(( Dif == 11 || Dif == 13))
    {
        //COME
        if (miTablero->casillasInt[miTablero->jugada[1]] < 0)
            return true;
        else if(miTablero->alPaso >= 0)
        {
            //AL PASO

            int  posCasilla  = miTablero->jugada[0]/12 + miTablero->jugada[1]%12;

            if (miTablero->alPaso ==  posCasilla)
                return true;
        }
    }
    return false;
}

bool Autorizaciones::autorizaAlfil(ModeloTablero* miTablero)
{

    int Dif = miTablero->jugada[1] - miTablero->jugada[0];


    if ( Dif%12  + Dif/12 == 0)
    {
        if(Dif%12 < 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR IZQUIERDA)
            return pruebaCamino(miTablero, 11);


        else if(Dif%12 > 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO DERECHA)
            return pruebaCamino(miTablero, -11);


    }
    else if( Dif%12  - Dif/12 == 0)
    {
        if(Dif%12  > 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ARRIBA DERECHA)
            return pruebaCamino(miTablero, 13);

        else if (Dif%12 > 0) //Columnas DESCENDENTES Y Filas DESCENDENTES (ABAJO IZQUIERDA)
            return pruebaCamino(miTablero, -13);



    }else return false;
}
bool Autorizaciones::autorizaReina(ModeloTablero* miTablero)
{
    if (autorizaAlfil(miTablero))
        return true;
    else return autorizaTorre(miTablero);
}

bool Autorizaciones::autorizaRey(ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    //  int filaDif = Dif/12;

int destino= miTablero->jugada[1];


    if (Dif== 1 || Dif== -1 || Dif== 12 || Dif== -12)
        return true;
    else{
        //ENROQUE
        if ( Dif/12 == 0 && ((!miTablero->turnoN && miTablero->jugada[1]/12 == 0) ||
                             (miTablero->turnoN &&  miTablero->jugada[1]/12 == 7)))
        {
            //    int posCasilla = filaNueva * 12; //ES SIEMPRE LA PRIMERA COLUMNA

            //derecha (enroque corto)

            if (miTablero->casillasInt[destino-1] == Vacio)
            {
                if(Dif == 2
                        && miTablero->casillasInt[destino] == Torre)
                    return true;

                else if(Dif == -2 && miTablero->casillasInt[miTablero->jugada[1]+1] == Torre
                        && miTablero->casillasInt[destino] == Vacio)   //izquierda (enroque largo)
                    return true;

            }
        }
        return false;
    }
}

bool Autorizaciones::autorizaTorre(ModeloTablero* miTablero)
{

    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    if (Dif%12 == 0 && Dif/12 < 0) //MOVIMIENTO ABAJO
        return pruebaCamino(miTablero, -12);

    else if (Dif%12==0
             && Dif/12 > 0 )  //MOVIMIENTO ARRIBA
        return pruebaCamino(miTablero, 12);

    else if (Dif/12==0
             && Dif%12 > 0 )  //MOVIMIENTO IZQUIERDA
        return pruebaCamino(miTablero, -1);

    else if (Dif/12==0
             && Dif%12 < 0 ) //MOVIMIENTO DERECHA
        return pruebaCamino(miTablero, 1);

    else return false;
}

bool Autorizaciones::autorizaCaballo(int Dif)
{
    int filaDif = Dif/12;
    int colDif = Dif%12;

    if (filaDif < 0) filaDif = -filaDif;

    if ((filaDif == 2 && colDif == 1)
            || (filaDif == 1 && colDif == 2))
        return true;
    else return false;
}



/*
bool Autorizaciones::verificaCamino(ModeloTablero* tablero)
{
    std::cout << "!!!!!!!!!!!VERIFICA!!!!!!!!!!!!!!CAMINO: " << camino<<std::endl;

    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    int Destino;

    if (Dif/)

        //int colDestino = colNueva;//-(nuevo.z/10);
        //  int filaDestino = filaNueva; //-(nuevo.x/10);

        while (tablero->casillasInt[Destino] != 99)
        {
            if (camino == 1) Destino = Destino+12;  // ARRIBA
            else if (camino == 2) Destino = Destino-12; // ABAJO
            else if (camino == 3) Destino = Destino+1; // DERECHA
            else if (camino == 4) Destino = Destino-1; // IZQUIERDA
            else if (camino == 5)
            { //MOVIMIENTO DIAGONAL ARRIBA DERECHA
                Destino = Destino+13;
            }
            else if (camino == 6)
            { //MOVIMIENTO DIAGONAL ARRIBA IZQUIERDA
                Destino = Destino+11;
            }
            else if (camino == 7) //MOVIMIENTO DIAGONAL ABAJO IZQUIERDA
            {
                Destino = Destino-13;
            }
            else if (camino == 8) //MOVIMIENTO DIAGONAL ABAJO DERECHA
            {
                Destino = Destino-11;
            }


            std::cout << "!!!!!!!!!!!VERIF!!!!!!!!!!!!!!" <<24+(filaDestino*12) + colDestino+2 <<std::endl;
            std::cout << "!!!!!!!!!!!CASILLA!!!!!!!!!!!!!!" <<casillas[24+(filaDestino*12) + colDestino+2]<<std::endl;

            if (casillas[Destino] != 0)
                return false;
        }
    return true;
}
*/
