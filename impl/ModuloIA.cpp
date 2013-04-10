#include "../headers/ModuloIA.h"

ModuloIA::ModuloIA()
{

}

ModuloIA::~ModuloIA()
{

}

ModuloIA* ModuloIA::getCEGUISingletonPtr()
{
    static ModuloIA miFrameListener;
    static ModuloIA* miFrameListenerPtr = &miFrameListener;
    return miFrameListenerPtr;
}


bool ModuloIA::construyeArbol(int* listaCasillas){

    /*
 *
0 = Vacio
9 = Fuera del tablero
1 = (Blancas) Peon
2 =(Blancas) Caballo
3 =(Blancas) Alfil
4 = (Blancas) Torre
5 = (Blancas) Reina
6 = (Blancas) Rey

-1 = (Negras) Peon
-2 =(Negras) Caballo
-3 =(Negras) Alfil
-4 = (Negras) Torre
-5 = (Negras) Reina
-6 = (Negras) Rey
*/


    tableroPadre = new TableroPrueba();

    tableroPadre->turnoN = true;

    std::cout << "CONSTRUYE ARBOL" << std::endl;

    //  tablero->Score = 2;


    //AÑADE LOS BORDES
    for (int i = 0; i<12; i++)
    {

        for (int y = 0; y<12; y++)
        {



            if((i > 9)
                    || (y > 9)
                    || (i < 2)
                    || (y < 2))
            {
                tableroPadre->casillasInt[(i*12)+y] = 99;

            }else tableroPadre->casillasInt[(i*12)+y] = listaCasillas[((i-2)*8)+y-2];


            //  std::cout << tablero->casillasInt[((i-2)*8)+y-2] << std::endl;
        }


    }

    //  std::cout << "BORRA VECTORMOV "<< std::endl;


    // tableroElegido->vectorMov->clear();
    //std::cout << "BORRA TABLEROELEGIDO "<< std::endl;

    // delete [] tableroElegido;
    std::cout << "CONSTRUYE ARBOL2222222222" << std::endl;

    tableroElegido = NULL;
    std::cout << "CONSTRUYE ARBOL33333333333" << std::endl;

    int resultado = alphaBeta(tableroPadre,-50000, 50000, 5);

    std::cout << "RESULTADO DE ALFABETA: "<< resultado<< std::endl;


    std::cout << "NUMERO NODOS TABLERO INICIAL: "<< tableroPadre->vectorMov.size()<< std::endl;

    TableroPrueba* tp = NULL;
    for (int i = 0; i< tableroPadre->vectorMov.size(); i++)
    {


        //  std::vector<TableroPrueba*> vecRef = tablero->vectorMov;


        tp = tableroPadre->vectorMov.at(i);

        std::cout << "EL ESCORE DE TP: "<< tp->Score<< std::endl;




        if ( tp->Score == -resultado)
        {

            tableroElegido = tp;
            std::cout << tableroElegido->fichaMovida<< std::endl;
            break;
        }





    }
    //  delete [] tp;

    // std::cout << "acaba bucle"<< std::endl;

    //  std::cout << "MOVIMIENTOSS: "<<      tableroElegido->movimiento[0] << std::endl;
    //std::cout << "MOVIMIENTOSS: "<<      tableroElegido->movimiento[1] << std::endl;

    // std::cout << "Turno NEGRAS del tablero (0 blancas, bien porque se elige un hijo del inicial): "<<  tableroElegido->turnoN  << std::endl;

    std::cout << "TABLERO ELEGIDO"<< std::endl;


    for(int i=2; i<10;i++){


        std::cout << tableroElegido->casillasInt[(i*12)+2]<<"    "<<tableroElegido->casillasInt[(i*12)+3]<<"    "<<tableroElegido->casillasInt[(i*12)+4]<<"    "<<tableroElegido->casillasInt[(i*12)+5]<<"    "<<tableroElegido->casillasInt[(i*12)+6]<<"    "<<tableroElegido->casillasInt[(i*12)+7]<<"    "<<tableroElegido->casillasInt[(i*12)+8]<<"    "<<tableroElegido->casillasInt[(i*12)+9]<<std::endl;


    }


}

void ModuloIA::insert_helper( TableroPrueba **root, TableroPrueba *newkey,const int profundidad ) {

    if (profundidad != 0){
        if ( (*root) == NULL ) {
            *root = newkey;
            TableroPrueba* tableroTemporal = siguienteMovimiento(newkey);
            // if (hijo) insert_helper( &((*root)->tableroHijo), tableroTemporal, --profundidad );
            // else insert_helper( &((*root)->tableroHermano), tableroTemporal, --profundidad);
        }
    }
}

TableroPrueba* ModuloIA::siguienteMovimiento(TableroPrueba *newkey){



}

void ModuloIA::insert( TableroPrueba* newKey  )
{
    //insert_helper( &tablero, newKey,4 );
    //  alphaBeta(tablero,100, -100, 1);
}

int ModuloIA::alphaBeta(TableroPrueba* table,int alpha,int beta,const int depthleft )
{

    // std::cout << "!!!!!!!!!!!!!!!!!!ALPHA-BETA turno: "<<table->turnoN << std::endl;
    //  std::cout << "!!!!!!!!!!!!!!!!!!NIIVEL: "<< depthleft<< std::endl;

    int score;
    if( depthleft == 0)
    {
        //   std::cout << "EVALUA LA HEURISTICA "<< std::endl;
        //CALCULA LA HEURISTICA
        table->Score = evaulaTablero(table);
        //   std::cout << "ENCUENTRA UN NODO TERMINAL: "<< table->Score<< std::endl;

        return table->Score;
    }

    //PROBLEMA: ¿Puede haber varios resultados identicos de la evaluacion? ¿entonces coge el primero o el ultimo?
    //OTRO: el tran numero de nodos hijo (siblings?)

    //MIRA A VER SI SE PUEDEN GENERAR LOS MOVIMIENTOS DE UNO EN UNO??

    //  std::cout << "mira el vector"<< std::endl;


    generaMovimientos(table);
    // if (table->vectorMov != NULL) std::cout << "TAMAÑO DEL VECTOR DESPUES de todo(lleno): "<<  table->vectorMov->size()<< std::endl;


    //for (vector<TableroPrueba>::iterator it = vectorMov.begin(); it!=vectorMov.end(); ++it) {
    //  cout << *it << endl;
    //}
    //  std::cout << "!!!!!!!!!!!!!!!!!!TAMAÑO VECTOR DE TABLEROS HIJO: "<< table->vectorMov->size()<< std::endl;

    //TableroPrueba* tab;
    //if (table->vectorMov != NULL){
    for (int i = 0; i < table->vectorMov.size();i++)
    {


        //    std::cout << "!!!!!!!!!!!!!!!!!!SE AVENTURA EN LA TABLA (del vector) NUMERO: "<< i << std::endl;

        score = -alphaBeta(table->vectorMov.at(i), -beta, -alpha, depthleft - 1 );
        if( score >= beta )
        {
            table->Score =  score;

            // table->Score = score;
            //         std::cout << "!!!!!!!!!!!!!!!!!! fail hard beta-cutoff SCORE:"<< score <<" BETA:" << beta << std::endl;
            //DEJA DE CALCULAR HEURISTICAS
            //  table->Score = score;
            return beta;   //  fail hard beta-cutoff

        }
        if( score > alpha )
        {
            //    std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa:"<< score <<" ALFA:" << alpha << std::endl;

            table->Score = score;

            alpha = score; // alpha acts like max in MiniMax
        }
    }
    // }else std::cout << "EL VECTOR ES NULL"<< std::endl;


    // std::cout << "!!!!!!!!!!!!!!!!!FIN ALFABETA"<< std::endl;

    // delete [] tab;
    //


    return alpha;
}

int ModuloIA::evaulaTablero(TableroPrueba* table)
{
    int suma = 0;


    //EMPIEZA CONTANDO LAS FICHAS DEL TABLERO Y HACIENDO UNA SUMA SIMPLE...

    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {


            if (table->casillasInt[(i*12)+y] < 0)
            {


                suma =  suma - valorFicha(tipoF(-table->casillasInt[(i*12)+y]));

            }else if (table->casillasInt[(i*12)+y] > 0){

                suma =  suma + valorFicha(tipoF(table->casillasInt[(i*12)+y]));

            }

        }

    }

    // std::cout << "ESTE TABLERO HA ACUMULADO UN VALOR DE: " << suma<< std::endl;


    return suma;
}




short ModuloIA::valorFicha(const tipoF tipo)
{

    switch (tipo)
    {
    case Pe:
    {
        return 100;
    }
    case Cab:
    {
        return 320;
    }
    case Alf:
    {
        return 325;
    }
    case Tor:
    {
        return 500;
    }
    case Rein:
    {
        return 975;
    }
    case Re:
    {
        return 32767;
    }
    default:
    {
        return 0;
    }
    }
}




void ModuloIA::generaMovimientos(TableroPrueba* miTablero){
    // TableroPrueba nuevoTablero;
    //  std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!" << std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    int rey = 6;
    int reina = 5;
    int torre = 4;
    int alfil = 3;
    int caballo = 2;
    int peon = 1;

    if (miTablero->turnoN){
        rey = -6;
        reina = -5;
        torre = -4;
        alfil = -3;
        caballo = -2;
        peon = -1;
    }


    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {


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
                //   std::cout << "!!!!!!!!!!!!!!!!!!UN MUEVE PEON!!!!!!!!!!!!!!!!!!!" << std::endl;


                //ENCUENTRA REY BLANCO

                muevePeon(miTablero, (i*12)+y);
                //   std::cout << "!!!!!!!!!!!!!!!!!!ACABA MUEVE PEON!!!!!!!!!!!!!!!!!!!" << std::endl;


            }


        }
    }


    //  std::cout << "!!!!!!!!!!!!!!!!!!ACABA MOVI!!!!!!!!!!!!!!!!!!!" << std::endl;



}

//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?



bool ModuloIA::mueveTorre(TableroPrueba* miTablero,const int casilla)
{
    //mueve a todas las casillas posibles

    //mira si esta ocupada

    int nuevaCasilla = casilla-1;
    bool come = false;
    bool pasa = false;

    while(nuevaCasilla%12 >2)
    {
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

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
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

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
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

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
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;
        } else break;
        nuevaCasilla = nuevaCasilla+12;
    }
}


bool ModuloIA::mueveReina(TableroPrueba* miTablero, int casilla)
{
    mueveTorre(miTablero, casilla);
    mueveAlfil(miTablero, casilla);
}

void ModuloIA::muevePeon(TableroPrueba* miTablero, int casilla)
{
    int nuevaCasilla;
    int casillaCome;
    int casillaComeSec;

    if (miTablero->turnoN)
    {
        //  std::cout << "!!!!!!!!!!!TURNO NEGRAS!!!!!!!!!!" << std::endl;

        nuevaCasilla = casilla-12;
        casillaCome = casilla-11;
        casillaComeSec= casilla-13;
        //  std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        // std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if(miTablero->casillasInt[nuevaCasilla] == 0)
        {
            if (nuevaCasilla > 122){
                //        miTablero->casillasInt[nuevaCasilla] = 0;
                //        peonEnemigo == true;

                miTablero->casillasInt[casilla] = -5;
            }

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }

        //   nuevaCasilla = casilla+1;
        //    bool peonEnemigo = false;

        if (/*peonEnemigo ||*/ miTablero->casillasInt[casillaCome] > 0)
        {

            if (casillaCome > 122){
                //        miTablero->casillasInt[nuevaCasilla] = 0;
                //        peonEnemigo == true;

                miTablero->casillasInt[casilla] = -5;
            }

            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if (miTablero->casillasInt[casillaComeSec] > 0)
        {

            if (casillaComeSec > 122){
                //        miTablero->casillasInt[nuevaCasilla] = 0;
                //        peonEnemigo == true;

                miTablero->casillasInt[casilla] = -5;
            }
            aplicaMovimiento(*miTablero, casilla, casillaComeSec);
        }
    }else
    {
        nuevaCasilla = casilla+12;
        casillaCome = casilla+11;
        casillaComeSec= casilla+13;

        //   std::cout << "!!!!!!!!!!!TURNO BLANCAS!!!!!!!!!!" << std::endl;
        if (miTablero->casillasInt[nuevaCasilla] == 0)
        {
            if (nuevaCasilla < 36){
                miTablero->casillasInt[casilla] = 5;
            }
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
        }
        //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        //   std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if (miTablero->casillasInt[casillaCome] < 0)
        {

            if (casillaCome < 36){
                miTablero->casillasInt[casilla] = 5;
            }
            aplicaMovimiento(*miTablero, casilla, casillaCome);
        }

        if (miTablero->casillasInt[casillaComeSec] < 0)
        {
            if (casillaComeSec < 36){
                miTablero->casillasInt[casilla] = 5;
            }
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

bool ModuloIA::mueveAlfil(TableroPrueba* miTablero, int casilla)
{
    int nuevaCasilla = casilla-13;

    bool pasa = false;
    bool come;

    while(nuevaCasilla%12 >2 && nuevaCasilla/12 >2)
    {
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

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
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

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
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

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
        if (miTablero->turnoN)
        {
            pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
        }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);
            if (come) break;
        } else break;

        nuevaCasilla = nuevaCasilla+11;
    }
}

bool ModuloIA::mueveCaballo(TableroPrueba* miTablero, int casilla)
{
    //HAY QUE HACERLO A PARTIR DE UNA POSICION

    int nuevaCasilla;

    nuevaCasilla = casilla-25;


    bool pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }

    nuevaCasilla = casilla-23;



    pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }




    nuevaCasilla = casilla+25;


    pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla+23;


    pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla-10;


    pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla-14;


    pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla+10;


    pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }



    nuevaCasilla = casilla+14;


    pasa = false;

    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

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

bool ModuloIA::mueveRey(TableroPrueba* miTablero, int casilla)
{
    int nuevaCasilla;

    nuevaCasilla = casilla-1;


    bool pasa = false;




    if (miTablero->turnoN)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa){


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);


    }

    if (casilla < 36)
    {
        //ENROQUE CORTO
        bool torre = false;
        nuevaCasilla = casilla-3;

        pasa = false;
        if (miTablero->turnoN)
        {
            torre = miTablero->casillasInt[nuevaCasilla] == -4 ;
        }else  torre = miTablero->casillasInt[nuevaCasilla] == 4;

        if (torre && miTablero->casillasInt[casilla-2] == 0&& miTablero->casillasInt[casilla-1] == 0)
        {

            nuevaCasilla = casilla-2;

            miTablero->casillasInt[casilla-3] = 0;

            if (miTablero->turnoN)
                miTablero->casillasInt[casilla-1] = -4;
            else
                miTablero->casillasInt[casilla-1] = 4;

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);

        }
    }

    if (casilla > 122)
    {
        //ENROQUE LARGO
        bool torre = false;
        nuevaCasilla = casilla+4;

        pasa = false;
        if (miTablero->turnoN)
        {
            torre = miTablero->casillasInt[nuevaCasilla] == -4 ;
        }else  torre = miTablero->casillasInt[nuevaCasilla] == 4;

        if (torre && miTablero->casillasInt[casilla+2] == 0 && miTablero->casillasInt[casilla+1] == 0 && miTablero->casillasInt[casilla+3] == 0)
        {

            nuevaCasilla = casilla+2;

            miTablero->casillasInt[casilla+4] = 0;

            if (miTablero->turnoN)
                miTablero->casillasInt[casilla+1] = -4;
            else
                miTablero->casillasInt[casilla+1] = 4;

            aplicaMovimiento(*miTablero, casilla, nuevaCasilla);

        }



    }



    nuevaCasilla = casilla+1;
    pasa = false;


    if (miTablero->turnoN){
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa){
        //  miTablero->fichaMovida = "REY!!!!";

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);



    }


    nuevaCasilla = casilla-12;

    pasa = false;

    if (miTablero->turnoN){
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa){


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);

    }


    nuevaCasilla = casilla+12;

    pasa = false;


    if (miTablero->turnoN){
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        //  TableroMovido->fichaMovida = "REY!!!!";

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);




    }


    nuevaCasilla = casilla+13;

    pasa = false;

    if (miTablero->turnoN){
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0  ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {

        //    TableroMovido->fichaMovida = "REY!!!!";

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);





    }

    nuevaCasilla = casilla+11;

    pasa = false;
    if (miTablero->turnoN){
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {


        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);




    }



    nuevaCasilla = casilla-13;
    pasa = false;


    if (miTablero->turnoN){
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0 ;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);



    }



    nuevaCasilla = casilla-11;
    pasa = false;


    if (miTablero->turnoN){
        pasa = miTablero->casillasInt[nuevaCasilla] >= 0;
    }else  pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";

        aplicaMovimiento(*miTablero, casilla, nuevaCasilla);




    }



}


void ModuloIA::aplicaMovimiento(TableroPrueba &miTablero, int casOrigen, int casDestino){



    if(miTablero.casillasInt[casDestino] != 99)
    {



        TableroPrueba* TableroMovido = new TableroPrueba(miTablero);




        int fichaOrigen = miTablero.casillasInt[casOrigen];

        //   std::cout << "!!!!!!!!!FICHA ORIGEN!!!!!!:" << fichaOrigen << std::endl;


        //     std::cout << "!!!!!!!!!FICHA DESTINO!!!!!!:" << miTablero.casillasInt[casDestino] << std::endl;


        TableroMovido->casillasInt[casOrigen] = 0;

        TableroMovido->casillasInt[casDestino] = fichaOrigen;


        TableroMovido->movimiento[0] = casOrigen;
        TableroMovido->movimiento[1] = casDestino;


        // TableroMovido->turnoN = !TableroMovido->turnoN;

        //   std::cout << "!!!!!!LE METE AL VECTOR" << std::endl;

        miTablero.vectorMov.push_back(TableroMovido);

        miTablero.numeroHijos++;



    }



}



TableroPrueba::TableroPrueba() :
    numeroHijos(0),
    Score(0),
    fichaMovida(""),
    vectorMov(0)
{
}

TableroPrueba::TableroPrueba( const TableroPrueba& original ):
    numeroHijos(0),
    Score(0),
    fichaMovida(""),
    vectorMov(0),
    turnoN(!original.turnoN)
{


    for(int i=0; i<144;i++){


        casillasInt[i] = original.casillasInt[i];



    }


}

TableroPrueba::~TableroPrueba()
{



    for(int i = 0; i < numeroHijos; i++)
    {

        delete vectorMov.at(i);

        vectorMov.at(i) = NULL;
    }

    numeroHijos=0;

    vectorMov.clear();


}
