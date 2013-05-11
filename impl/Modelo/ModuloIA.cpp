#include "../../headers/Modelo/ModuloIA.h"

ModuloIA::ModuloIA():
    BlackCheck(false),
    BlackMate(false),
    WhiteCheck(false),
    WhiteMate(false),
    StaleMate(false)
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


bool ModuloIA::construyeArbol(TableroPrueba* tableroPadre)
{

    /*
 *
0 = Vacio
99 = Fuera del tablero
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

    //  std::cout << "BORRA VECTORMOV "<< std::endl;


    // tableroElegido->vectorMov->clear();
    //std::cout << "BORRA TABLEROELEGIDO "<< std::endl;

    // delete [] tableroElegido;
    std::cout << "CONSTRUYE ARBOL2222222222" << std::endl;

    tableroElegido = NULL;
    std::cout << "CONSTRUYE ARBOL33333333333" << std::endl;

    int resultado = alphaBeta(tableroPadre,-50000, 50000, 3);

    std::cout << "RESULTADO DE ALFABETA ANTES: "<< resultado<< std::endl;

    if (tableroPadre->turnoN) resultado = -resultado;

    std::cout << "RESULTADO DE ALFABETA DESPUES: "<< resultado<< std::endl;


    std::cout << "NUMERO NODOS TABLERO INICIAL: "<< tableroPadre->vectorMov.size()<< std::endl;

    if (tableroPadre->vectorMov.size() == 0)
    {
        std::cout << "NO HAY TABLEROS EN EL VECTOR POR LO QUE ES UN JAQUE MATE O UN AHOGADO, HABRA QUE DIFERENCIAR"<< std::endl;

        return false;

    }else
    {
        TableroPrueba* tp = NULL;
        for (int i = 0; i< tableroPadre->vectorMov.size(); i++)
        {

            //  std::vector<TableroPrueba*> vecRef = tablero->vectorMov;

            tp = tableroPadre->vectorMov.at(i);

            std::cout << "EL ESCORE DE TP: "<< tp->Score<< std::endl;

            if ( tp->Score == resultado)
            {
                std::cout << "ELEGIDO "<< std::endl;

                tableroElegido = tp;
                //std::cout << tableroElegido->fichaMovida<< std::endl;
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
    std::cout << "retorno"<< std::endl;


    return true;
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
        int ev = evaulaTablero(table->casillasInt, table->turnoN);

        table->Score = ev;
        // std::cout << "EVALUACION DEVUELVE: "<< table->Score<< std::endl;


        //   std::cout << "ENCUENTRA UN NODO TERMINAL: "<< table->Score<< std::endl;

        return table->Score;
    }

    //PROBLEMA: ¿Puede haber varios resultados identicos de la evaluacion? ¿entonces coge el primero o el ultimo?
    //OTRO: el tran numero de nodos hijo (siblings?)

    //MIRA A VER SI SE PUEDEN GENERAR LOS MOVIMIENTOS DE UNO EN UNO??

    //  std::cout << "mira el vector"<< std::endl;


    Autorizaciones::generaMovimientos(table);
    // if (table->vectorMov != NULL) std::cout << "TAMAÑO DEL VECTOR DESPUES de todo(lleno): "<<  table->vectorMov->size()<< std::endl;


    //for (vector<TableroPrueba>::iterator it = vectorMov.begin(); it!=vectorMov.end(); ++it) {
    //  cout << *it << endl;
    //}
    //  std::cout << "!!!!!!!!!!!!!!!!!!TAMAÑO VECTOR DE TABLEROS HIJO: "<< table->vectorMov->size()<< std::endl;

    //TableroPrueba* tab;
    //if (table->vectorMov != NULL){
    if (table->vectorMov.size() == 0)
    {
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS (JAQUE MATE O AHOGADO)!!!: " << std::endl;

        return 0;

    }

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

int ModuloIA::evaulaTablero(const int casillasInt[144], bool turnoN)
{
    int suma = 0;
    //   BlackCheck = false;

    //EMPIEZA CONTANDO LAS FICHAS DEL TABLERO Y HACIENDO UNA SUMA SIMPLE...


    //EVALUA JAQUE PARA NEGRAS

    //  BlackCheck = evaluaJaque(casillasInt, turnoN);


    //   if(BlackCheck)
    //   {
    //      return 0;
    //   std::cout << "EVALUA UN JAQUE COMO TERMINAL: "<< std::endl;

    //  }

    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {
            if (casillasInt[(i*12)+y] < 0)
            {
                //if(casillasInt[(i*12)+y] == -6){
                //   BlackCheck = false;

                //   }

                suma =  suma - valorFicha(tipoF(-casillasInt[(i*12)+y]));

            }else if (casillasInt[(i*12)+y] > 0){

                suma =  suma + valorFicha(tipoF(casillasInt[(i*12)+y]));

            }

        }

    }
 //   if(turnoN){
   //    std::cout << "turno  negras suma: " << suma<< std::endl;

     //  suma = -suma;

    //}

    if(suma!=0)std::cout << "ESTE TABLERO TIENE VALOR DISTINTO DE 0 Y HA ACUMULADO UN VALOR DE: " << suma<< " y turnoN:"<<turnoN   <<std::endl;


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
        return 9750;
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

