#include "../../headers/Modelo/Autorizaciones.h"


int Autorizaciones::autorizaPeon (ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0] ;

    std::cout << "!!!!!!!!!!!AUTORIZA PEON!!!!!!!!!!!!!!" << std::endl;

    if (Dif < 0)
    {
        std::cout << "!!!!DIFERENCIA NEGATIVA!!!!!!!" << std::endl;

        std::cout << "!!!!TURNO AL CAMBIAR!!!!! "<<miTablero->turnoN << std::endl;


        //Invierte el signo  de la diferencia de los peones negros
        Dif = -Dif;
    }

    // int filaSobreTraducida = 24 + (filaNueva * 12);

    //std::cout << "!!!!!!!!DIFERENCIA: " <<   diferencia.Fila<<" col!!!!!!!!: " <<diferencia.Columna << std::endl;
    //std::cout << "!!!!!!!!FILa sobrevolada: " <<   nodoSobrevolado.Fila  << std::endl;
    //std::cout << "!!!!!!!!COL sobrevolada: " <<   nodoSobrevolado.Columna<< std::endl;
    //std::cout << "!!!!!!!!FILa seleccionada: " <<   seleccionado.Fila<<" traducida!!!!!!!!" <<filaSobreTraducida << std::endl;
    //std::cout << "!!!!!!!!COL seleccionada: " <<   seleccionado.Columna<<" traducida!!!!!!!!" <<seleccionado.Columna+2 << std::endl;

    if (Dif == 12 ||
            (Dif== 24
             && miTablero->jugada[0]/12 == 3))
    {
        std::cout << "!!!!ALTA 2 CASILLAS (ESCAQUES) o PASA UNA CASILLA!!!!!!!" << std::endl;

        //SALTA 2 CASILLAS (ESCAQUES) o PASA UNA CASILLA
        if (miTablero->casillasInt[miTablero->jugada[1]] != 0)
            return 0;
        else
        {
                return pruebaCamino(miTablero, 12);
        }
    }

    else if(( Dif == 11 || Dif == 13))
    {
        Dif = miTablero->jugada[1] - miTablero->jugada[0];
        //COME
        if (miTablero->casillasInt[miTablero->jugada[1]] < 0)
        {
            return pruebaCamino(miTablero, Dif);
        }
        else if(miTablero->alPaso >= 0)
        {
            //AL PASO

            //CASILLA EN LA COLUMNA DE LA SOBREVOLADA Y EN LA FILA DEL PEON ATACANTE
            int  posCasilla  = miTablero->jugada[0]/12 + miTablero->jugada[1]%12;

            if (miTablero->alPaso ==  posCasilla)
            {

                return pruebaCamino(miTablero, Dif);


            }

        }
    }
    return 0;
}

int Autorizaciones::autorizaAlfil(ModeloTablero* miTablero)
{

    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    std::cout << "!!!AUTORIZA ALFIL!" << Dif << std::endl;

    //diferencia multiplo de 11
    if (Dif % 11 == 0)
    {
        std::cout << "!!!A1111!" << std::endl;


        if(Dif > 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR IZQUIERDA)
            return pruebaCamino(miTablero, 11);


        else if(Dif < 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO DERECHA)
            return pruebaCamino(miTablero, -11);


    }
    //multiplo de 13
    else if (Dif % 13 == 0)
    {
        std::cout << "!!!A2222!" << std::endl;

        if(Dif  > 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ARRIBA DERECHA)
            return pruebaCamino(miTablero, 13);

        else if (Dif < 0) //Columnas DESCENDENTES Y Filas DESCENDENTES (ABAJO IZQUIERDA)
            return pruebaCamino(miTablero, -13);



    }else return 0;
}

int Autorizaciones::autorizaReina(ModeloTablero* miTablero)
{
    int result = autorizaAlfil(miTablero);
    if (result > 0)
        return result;
    else return autorizaTorre(miTablero);
}

int Autorizaciones::autorizaRey(ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    int destino= miTablero->jugada[1];

    if (Dif== 1 || Dif== -1 ||Dif== 11 || Dif== -11 || Dif== 12 || Dif== -12|| Dif== 13 || Dif== -13)
        return pruebaCamino(miTablero, Dif);
    else{
        //ENROQUE
        if ( Dif/12 == 0 && destino/12 == 2)
        {
            if(Dif == 2
                    && miTablero->casillasInt[destino+1] == Torre)
                return pruebaCamino(miTablero, 1);

            else if(Dif == -2 && miTablero->casillasInt[destino-2] == Torre
                    && miTablero->casillasInt[destino-1] == Vacio)   //izquierda (enroque largo)
                return pruebaCamino(miTablero, -1);

        }

        return 0;
    }
}

int Autorizaciones::autorizaTorre(ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    std::cout << "!!!AUTORIZA TORRE!" << Dif << std::endl;

    //MULTIPLO DE 12, ARRIBA O ABAJO
    if (Dif%12 == 0)
    {
        std::cout << "!!!misma collll"  << std::endl;

        if (Dif < 0) //MOVIMIENTO ABAJO
            return pruebaCamino(miTablero, -12);

        else if (Dif > 0 )  //MOVIMIENTO ARRIBA
            return pruebaCamino(miTablero, 12);

    }

    //misma fila
    else if (miTablero->jugada[1]/12 == miTablero->jugada[0]/12)
    {
        std::cout << "!!!misma filaaaa!"  << std::endl;


        if (Dif > 0)
            //MOVIMIENTO DERECHA
            return pruebaCamino(miTablero, +1);

        else if (Dif < 0) //MOVIMIENTO IZQUIERDA
            return pruebaCamino(miTablero, -1);
    }
    return 0;
}




int Autorizaciones::autorizaCaballo(ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0];


    if (Dif < 0) Dif = -Dif;
    //  int filaDif = Dif/12;
    //  int colDif = Dif%12;


    // std::cout << "!!caballo!"  << filaDif << " "<<colDif << std::endl;
    std::cout << "!!DIF!"  << Dif  << std::endl;


    if (Dif == 23 || Dif == 25 || Dif == 10 || Dif == 14)
    {



        return pruebaCamino(miTablero, miTablero->jugada[1] - miTablero->jugada[0]);

    }
    else {
        std::cout << "!!faaaaaaaial!" <<std::endl;

        return 0;}
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

int Autorizaciones::pruebaCamino(ModeloTablero* miTablero, int salto)
{
    //   int Dif = casillaFinal - casillaInicial;

    int resultado = 0;
    // int ocupado = false;
    int nuevaCasilla = miTablero->jugada[0];
    bool pasa = true;

    while(pasa)
    {
        nuevaCasilla = nuevaCasilla+salto;
       // std::cout << "!!!!PRUEBA CAMINO!!!: " << nuevaCasilla  <<std::endl;

        pasa = miTablero->casillasInt[nuevaCasilla] == 0;


        if (nuevaCasilla == miTablero->jugada[1])
        {
            int fichavieja = miTablero->casillasInt[miTablero->jugada[0]];
            int fichaNueva = miTablero->casillasInt[nuevaCasilla];

            miTablero->casillasInt[nuevaCasilla] = fichavieja;
            miTablero->casillasInt[miTablero->jugada[0]] = 0;

           // std::cout << "!!!mira si es jaque!" << std::endl;


            if (miTablero->evaluaJaque())
            {
                std::cout << "!!!!!HA EVALUADO UN JAQUE DESPUES DE MOVER (AL PROBAR CAMINO) !!!" << std::endl;
                resultado = 2;
            }
            else
                resultado= 1;

            miTablero->casillasInt[nuevaCasilla] = fichaNueva;
            miTablero->casillasInt[miTablero->jugada[0]] = fichavieja;


          //  std::cout << "!!!retorna resultado: "<<resultado << std::endl;

            return resultado;
        }

        //  if(miTablero->casillasInt[nuevaCasilla] != 0)
        // {
        //   std::cout << "!!!!OCUPADO: " << salto  <<std::endl;
        //  return false;

        //}
    }

    return resultado;
}
