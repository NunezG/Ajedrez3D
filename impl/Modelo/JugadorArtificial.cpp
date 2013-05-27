#include "../../headers/Modelo/JugadorArtificial.h"

JugadorArtificial::JugadorArtificial() :
    Jugador()
  , dificultad(0)

{

}
JugadorArtificial::~JugadorArtificial()
{


}


int* JugadorArtificial::mueveFicha(ModeloTablero* tablero)
{
    std::cout << "ARTIF MUEVE FICHA " << std::endl;

    // Modelo* modelo = Modelo::getSingletonPtr();

    //ModuloIA* modulo = ModuloIA::getCEGUISingletonPtr();

    //   ModeloTablero* tableroPadre = new ModeloTablero();

    std::cout << "TUDRNO DE MITABLERO:" << tablero->turnoN<< std::endl;

    //  tableroPadre->turnoN = tablero->turnoN;

    std::cout << "CONSTRUYE ARBOL CO ALPASO:" << tablero->alPaso<< std::endl;
    //VERIFICA ALPASO SI ES EN BASE 8 o 12


    /*  int fila = (tablero->alPaso/8)+2;
    int col= (tablero->alPaso%8)+2;

  //  tableroPadre->casillasInt = new int[144];
    tableroPadre->alPaso = ((fila*12)+col);
    */
    std::cout << "TRADUCIDO:" << tablero->alPaso<< std::endl;

    ////////////////////////////////////////////////////////////////////////////////////7
    //  tableroPadre->casillasInt = tablero->casillasInt;

    //  tablero->Score = 2;
    /*
    for (int i = 0; i<144; i++)
    {
        tableroPadre->casillasInt[i] = listaCasillas[i];
    }
   */
    bool result = construyeArbol(tablero);

    std::cout  << "IFFF " << std::endl;

    if (result == true && tableroElegido != NULL)
    {
        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        //    std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[0]<< std::endl;
        //    std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[1]<< std::endl;

        //   mueveIA(tableroElegido->movimiento[0],tableroElegido->movimiento[1]);


        //ACTIVA LA IA

        /*   int filaOrigen = (tableroElegido->movimiento[0]/12)-2;
        int colOrigen = (tableroElegido->movimiento[0]%12)-2;


        int filaDestino = (tableroElegido->movimiento[1]/12)-2;
        int colDestino = (tableroElegido->movimiento[1]%12)-2;

*/
        //aplicaSeleccion(tablero, filaOrigen, colOrigen, filaDestino, colDestino);

        //  tablero->casillasInt == Movimientos::mueveTablero(tablero->casillasInt, filaOrigen, colOrigen, filaDestino, colDestino);



        //   tableroElegido = NULL;

    }else
    {



        std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;

    }

    //  std::cout  << "DELETE TABLEROPADRE EN COTROL: "<<  std::endl;

    // delete tableroPadre;

    //  std::cout  << "NULEA MODULO EN COTROL: "<<  std::endl;
    //  tableroPadre = NULL;

    //modulo = NULL;

    //   std::cout   << "BORRA TABLERO " << std::endl;


    //  delete modulo->tableroElegido;


    //   std::cout  << "NULLEA TABLERO " << std::endl;


    //  modulo->tableroElegido = NULL;

    //modulo->ejecutaMovimiento(mod);

    //INICIA LA IA PARA CALCULAR LA FICHA A MOVER

    //PRIMERO HAZLO CON EL TABLERO Y LUEGO TE OCUPAS DE LAS FICHAS
    //EMPEZAMOS POR TODOS LOS MOVIMIENTOS DE TODOS LOS PEONES
    //ModuloIA modulo;

    // modelo->escena->tablero->movimientosPeon();



    // tableroInicial.casillas = ...

    //Recorre todas las fichas (negras) del tablero y crea un tablero para cada movimiento de cada ficha (estos seran lso hermanos)

    //Recorre todas las fichas (blancas) de cada tablero creado y crea un tablero para cada movimiento de cada ficha


    //    tableroInicial


    std::cout  << "ALFABETA HA DEVUELTO EL MOVIMIENTO 1: "<< tableroElegido->movimiento[0] <<   " Y 2 "<< tableroElegido->movimiento[1]<< std::endl;


    tablero->movimiento = tableroElegido->movimiento;

    return tableroElegido->movimiento;

}



//añade Tablero como parametro y asi se puede integrar al modelo??
void JugadorArtificial::calculaMovimiento()
{

}

bool JugadorArtificial::esHumano()
{
    return false;
}




//void JugadorArtificial::sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada)
//{

//}





bool JugadorArtificial::construyeArbol(ModeloTablero* tableroPadre)
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
    std::cout << "CONSTRUYE ARBOL PARA TURNO (ESNEGRA?):"<< tableroPadre->turnoN<< std::endl;

    tableroElegido = NULL;

    int resultado = alphaBeta(tableroPadre,-50000, 50000, 3);

    std::cout << "RESULTADO DE ALFABETA ANTES: "<< resultado<< std::endl;

    resultado = -resultado;

    std::cout << "RESULTADO DE ALFABETA DESPUES: "<< resultado<< std::endl;


    std::cout << "NUMERO NODOS TABLERO INICIAL: "<< tableroPadre->vectorMov.size()<< std::endl;

    if (tableroPadre->vectorMov.size() == 0)
    {
        std::cout << "NO HAY TABLEROS EN EL VECTOR POR LO QUE ES UN JAQUE MATE O UN AHOGADO, HABRA QUE DIFERENCIAR"<< std::endl;

        return false;

    }else
    {
        ModeloTablero* tp = NULL;
        for (int i = 0; i< tableroPadre->vectorMov.size(); i++)
        {

            //  std::vector<ModeloTablero*> vecRef = tablero->vectorMov;

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


int JugadorArtificial::alphaBeta(ModeloTablero* table,int alpha,int beta,const int depthleft )
{

    std::cout << "!!!!!!!!!!!!!!!!!!INICIO ALFA-BETA NIVEL: "<<depthleft << " ALFA: "<<alpha << " BETA: "<<beta <<std::endl;
    //  std::cout << "!!!!!!!!!!!!!!!!!!NIIVEL: "<< depthleft<< std::endl;

    int score;
    if( depthleft == 0)
    {
        //   std::cout << "EVALUA LA HEURISTICA "<< std::endl;
        //CALCULA LA HEURISTICA
        int ev = evaluaTablero(table->casillasInt, table->turnoN);

        table->Score = ev;
        std::cout << "EVALUACION DEVUELVE: "<< table->Score<<" NIVEL"<< depthleft<< std::endl;


        //   std::cout << "ENCUENTRA UN NODO TERMINAL: "<< table->Score<< std::endl;

        return table->Score;
    }

    //PROBLEMA: ¿Puede haber varios resultados identicos de la evaluacion? ¿entonces coge el primero o el ultimo?
    //OTRO: el tran numero de nodos hijo (siblings?)

    //MIRA A VER SI SE PUEDEN GENERAR LOS MOVIMIENTOS DE UNO EN UNO??

    //  std::cout << "mira el vector"<< std::endl;


    Movimientos::generaMovimientos(table, false);
    // if (table->vectorMov != NULL) std::cout << "TAMAÑO DEL VECTOR DESPUES de todo(lleno): "<<  table->vectorMov->size()<< std::endl;


    //for (vector<ModeloTablero>::iterator it = vectorMov.begin(); it!=vectorMov.end(); ++it) {
    //  cout << *it << endl;
    //}
    //  std::cout << "!!!!!!!!!!!!!!!!!!TAMAÑO VECTOR DE TABLEROS HIJO: "<< table->vectorMov->size()<< std::endl;

    //ModeloTablero* tab;
    //if (table->vectorMov != NULL){
    if (table->vectorMov.size() == 0)
    {
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS (JAQUE MATE O AHOGADO)!!!: " << std::endl;

        return 0;

    }

    for (int i = 0; i < table->vectorMov.size();i++)
    {


        std::cout << "!!!!!!!!!!!!!!!!!!SE AVENTURA EN LA TABLA NUMERO: "<< i <<" NIVEL: "<< depthleft<< " ALFA: "<<  alpha<<  " BETA: "<<  beta <<std::endl;

        score = -alphaBeta(table->vectorMov.at(i), -beta,-alpha, depthleft - 1 );
        std::cout << "!!!!!!!!!!!!!!!!!!SALE DE LA AVENTURA EN LA TABLA NUMERO: "<< i <<" NIVEL: "<< depthleft<< " ALFA: "<<  alpha<<  " BETA: "<<  beta << std::endl;

        std::cout << "!!!!!!!!!!!!!!!!!SCORE: "<< score<< std::endl;

        if( score >= beta )
        {
            //  table->Score =  score;

            // table->Score = score;
            std::cout << "!!!!!!!!!!!!!!!!!! fail hard beta-cutoff SCORE: "<< score <<" BETA: " << beta << std::endl;
            //DEJA DE CALCULAR HEURISTICAS
            //  table->Score = score;
            table->Score = score;
            return score;   //  fail hard beta-cutoff

        }
        if( score > alpha )
        {
            std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa: "<< score <<" ALFA: " << alpha << std::endl;

            table->Score = score;
            alpha = score; // alpha acts like max in MiniMax
        } else std::cout << "!!!!!!!!!!!!!SCORE NO ES MAYOR QUE BETA NI ALFA:" << " ALFA: "<<  alpha<<  " BETA: "<<  beta <<std::endl;

    }
    // }else std::cout << "EL VECTOR ES NULL"<< std::endl;


    // std::cout << "!!!!!!!!!!!!!!!!!FIN ALFABETA"<< std::endl;

    // delete [] tab;
    //

    return alpha;
}

int JugadorArtificial::evaluaTablero(const int casillasInt[144], bool turnoN)
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
            //Busca las fichas del mismo color del turno
            if (casillasInt[(i*12)+y] < 0)
            {
                //if(casillasInt[(i*12)+y] == -6){
                //   BlackCheck = false;

                //   }

                suma =  suma - valorFicha(tipoFicha(-casillasInt[(i*12)+y]));

            }else if (casillasInt[(i*12)+y] > 0){

                suma =  suma + valorFicha(tipoFicha(casillasInt[(i*12)+y]));

            }

        }

    }
    //if(!turnoN)
    //{
    //SI EL NODO TERMINAL ES TURNO BLANCAS SE INVIERTE LA SUMA, ASI LA SUMA POSITIVA ES LA DE LAS NEGRAS
    //  std::cout << "turno  blancas suma: " << suma<< std::endl;

    //   suma = -suma;

    //}

    if(suma!=0)std::cout << "ESTE TABLERO TIENE VALOR DISTINTO DE 0 Y HA ACUMULADO UN VALOR DE: " << suma<< " y turnoN:"<<turnoN   <<std::endl;


    return suma;
}




short JugadorArtificial::valorFicha(const tipoFicha tipo)
{

    switch (tipo)
    {
    case Peon:
    {
        return 100;
    }
    case Caballo:
    {
        return 320;
    }
    case Alfil:
    {
        return 325;
    }
    case Torre:
    {
        return 500;
    }
    case Reina:
    {
        return 9750;
    }
    case Rey:
    {
        return 32767;
    }
    default:
    {
        return 0;
    }
    }
}


