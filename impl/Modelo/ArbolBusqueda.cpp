#include "../../headers/Modelo/ArbolBusqueda.h"

ArbolBusqueda::ArbolBusqueda()


{

}





ArbolBusqueda::~ArbolBusqueda()
{


}





short ArbolBusqueda::CalculatePieceActionValue(int pieceType)
{
    switch (pieceType)
    {
        case Peon:
            {
                return 6;
            }
        case Caballo:
            {
                return 3;
            }
        case Alfil:
            {
                return 3;
            }
        case Torre:
            {
                return 2;
            }
        case Reina:
            {
                return 1;
            }
        case Rey:
            {
                return 1;
            }
        default:
            {
                return 0;
            }
    }
}



//void JugadorArtificial::sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada)
//{

//}


bool ArbolBusqueda::construyeArbol(ModeloTablero* tableroPadre)
{


    std::cout << "CONST ARBOL: "<< tableroPadre->nodoInicial<< std::endl;


    std::cout << "ORIGEN ANTES: "<< tableroPadre->jugada[0]<< std::endl;
    std::cout << "DEST ANTES: "<< tableroPadre->jugada[1]<< std::endl;

    int resultado = alphaBeta(tableroPadre,-70000, 70000, 3);


    std::cout << "FIN CONST ARBOL"<< std::endl;


    std::cout << "ORIGEN DESPUES DE ALFABETA!!!!: "<< tableroPadre->jugada[0]<< std::endl;
    std::cout << "DEST DE ALFABETA!!!!: "<< tableroPadre->jugada[1]<< std::endl;



    std::cout << "RESULTADO DE ALFABETA ANTES: "<< resultado<< std::endl;

    // resultado = resultado;

    std::cout << "RESULTADO DE ALFABETA DESPUES: "<< resultado<< std::endl;

    std::cout << "NUMERO NODOS TABLERO INICIAL: "<< tableroPadre->vectorMov.size()<< std::endl;

    if (tableroPadre->jugada[0] == -1)
    {
        std::cout << "NO HAY TABLEROS EN EL VECTOR POR LO QUE ES UN JAQUE MATE O UN AHOGADO, HABRA QUE DIFERENCIAR"<< std::endl;

        return false;

    }else
    {


        tableroPadre->jugadaAutorizada = true;

        /*   ModeloTablero* tp = NULL;
        for (int i = 0; i< tableroPadre->vectorMov.size(); i++)
        {
            tp = tableroPadre->vectorMov.at(i);

            std::cout << "EL ESCORE DE TP: "<< tp->Score<< std::endl;

            if ( tp->Score == resultado)
            {
                std::cout << "TABLERO ELEGIDO"<< std::endl;

                for(int i=2; i<10;i++)
                    std::cout << tp->casillasInt[(i*12)+2]<<"    "<<tp->casillasInt[(i*12)+3]<<"    "<<tp->casillasInt[(i*12)+4]<<"    "<<tp->casillasInt[(i*12)+5]<<"    "<<tp->casillasInt[(i*12)+6]<<"    "<<tp->casillasInt[(i*12)+7]<<"    "<<tp->casillasInt[(i*12)+8]<<"    "<<tp->casillasInt[(i*12)+9]<<std::endl;

                tableroPadre->movimiento = tp->movimiento;

                break;
            }

        }
*/
    }
    std::cout << "retorno"<< std::endl;


    return true;
}


int ArbolBusqueda::alphaBeta(ModeloTablero* table,int alpha,int beta,const int depthleft )
{

    // std::cout << "!!!!!!!!!!!!!!!!!!INICIO ALFA-BETA NIVEL: "<<depthleft << " ALFA: "<<alpha << " BETA: "<<beta <<std::endl;
    //  std::cout << "!!!!!!!!!!!!!!!!!!NIIVEL: "<< depthleft<< std::endl;

    if( depthleft == 0)
    {
        //   std::cout << "EVALUA LA HEURISTICA "<< std::endl;
        //CALCULA LA HEURISTICA
        int ev = evaluaTablero(table->casillasInt, table->turnoN);

        // table->Score = ev;

        // if (ev != 0)std::cout << "EVALUACION DEVUELVE: "<< table->Score<< std::endl;


        //   std::cout << "ENCUENTRA UN NODO TERMINAL: "<< table->Score<< std::endl;

        //////////////////////////////se puede hacer delete table aqui???????????????????
        //  std::cout << "!!!!!borra en nodo final"<< std::endl;

        //   delete  table;
        // table = NULL;
        //std::cout << "!!!!!fin"<< std::endl;

        return ev;
    }

    int rama = 6;
    int score;
    bool betaBreak = false;

    while (rama > 0 && !betaBreak)
    {

        Movimientos::generaMovimientos(table,tipoFicha(rama));


        //  std::cout << "!!!!!!!!!!!!!!!!!!TAMAÑO VECTOR DE TABLEROS HIJO: "<< table->vectorMov->size()<< std::endl;

        if (rama == 7 && table->vectorMov.size() == 0)
        {
            // std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS (JAQUE MATE O AHOGADO)!!!: " << std::endl;
            return 0;
        }
        for (int i = 0; i < table->vectorMov.size();i++)
        {
            // std::cout << "!!!!!!!!!!!!!!!!!!SE AVENTURA EN LA TABLA NUMERO: "<< i <<" NIVEL: "<< depthleft<< " ALFA: "<<  alpha<<  " BETA: "<<  beta <<std::endl;

            if (!betaBreak)
            {
                score = -alphaBeta(table->vectorMov.at(i), -beta,-alpha, depthleft - 1 );
                //  std::cout << "!!!!!!!!!!!!!!!!!!SALE DE LA AVENTURA EN LA TABLA NUMERO: "<< i <<" NIVEL: "<< depthleft<< " ALFA: "<<  alpha<<  " BETA: "<<  beta << std::endl;

                //  std::cout << "!!!!!!!!!!!!!FOR"<< std::endl;


                if( score >= beta )
                {
                    // std::cout << "!!!!!!!!!!!!!!!!!! fail hard beta-cutoff SCORE: "<< score <<" BETA: " << beta << std::endl;
                    //DEJA DE CALCULAR HEURISTICAS
                    /////////////TAL VEZ se pueda hacer el delete del elemento de vectormov aqui??????
                    //  table->Score = score;

                    //problema: se borran los del primer nivel
                    //  delete table;
                    // table = NULL;


                    delete table->vectorMov.at(i);
                    table->vectorMov.at(i) = NULL;

                    betaBreak = true;
                    //  fail hard beta-cutoff
                }
                else if( score > alpha )
                {
                    //   std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa: "<< score <<" ALFA: " << alpha << std::endl;
                    // table->Score = score;
                    //LE PASA EL MOVIMIENTO A SU PADRE SOLO SI EL PADRE ES EL INICIAL


                    //      std::cout << "!!nodo inicial"<< std::endl;


                    if (table->nodoInicial)
                    {

                        table->jugada[0] = static_cast<ModeloTablero*>(table->vectorMov.at(i))->jugada[0];
                        table->jugada[1] = static_cast<ModeloTablero*>(table->vectorMov.at(i))->jugada[1];

                    }



                    // jugada = new int[2];


                    //  std::cout << "!!!!!!!!!!!!!!!!!! actualiza JUGADA en nodo INCIAL: " << std::endl;

                    //      std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa ORIGEN: "<< table->jugada[0]  << std::endl;

                    //   std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa DESTINO: "<< table->jugada[1]   << std::endl;


                    // std::cout << "!!!!!!!!!!!!!!!!!! FIN actualiza alfa: "<< std::endl;

                    alpha = score; // alpha acts like max in MiniMax
                }
            } //else  std::cout << "!!BETA BREAAAAK "  << std::endl;


            //problema: se borran los del primer nivel

            // std::cout << "!!FINFOR "  << std::endl;


            delete table->vectorMov.at(i);
            table->vectorMov.at(i) = NULL;

        }
        rama--;


        for(int i = 0; i < table->vectorMov.size(); i++)
        {
            if (table->vectorMov.at(i) != NULL)
            {


                delete table->vectorMov.at(i);

                table->vectorMov.at(i) = NULL;
            }
        }

        //  numeroHijos=0;
        table->vectorMov.clear();
    }
    //  std::cout << "!!RETURN "  << std::endl;


    //  delete table;
    //  table = NULL;

    //table->vectorMov.clear();
    if (!betaBreak)
    return alpha;
    else return score;
}

int ArbolBusqueda::evaluaTablero(const int casillasInt[144], bool turnoN)
{
    int suma = 0;
    //   BlackCheck = false;

    //EMPIEZA CONTANDO LAS FICHAS DEL TABLERO Y HACIENDO UNA SUMA SIMPLE...

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

      //suma = -suma;

    //}

    //if(suma!=0)std::cout << "ESTE TABLERO TIENE VALOR DISTINTO DE 0 Y HA ACUMULADO UN VALOR DE: " << suma<< " y turnoN:"<<turnoN   <<std::endl;


    return suma;
}




short ArbolBusqueda::valorFicha(const tipoFicha tipo)
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
        return 750;
    }
    case Rey:
    {
        return 3000;
    }
    default:
    {
        return 0;
    }
    }
}


