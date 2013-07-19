#include "../../headers/Modelo/ArbolBusqueda.h"



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


int ArbolBusqueda::alphaBeta(ModeloTablero* table,int alpha,int beta,const int depthleft )
{
    //std::cout << "!!!!!!!!!!!!!!!!!!INICIO ALFA-BETA NIVEL: "<<depthleft << " ALFA: "<<alpha << " BETA: "<<beta <<std::endl;
    //  std::cout << "!!!!!!!!!!!!!!!!!!NIIVEL: "<< depthleft<< std::endl;


    if( depthleft == 0)
    {
        //   std::cout << "EVALUA LA HEURISTICA "<< std::endl;
        //CALCULA LA HEURISTICA
        int ev = evaluaTablero(table);
        // table->Score = ev;
        // if (ev != 0)std::cout << "EVALUACION DEVUELVE: "<< table->Score<< std::endl
        //   std::cout << "ENCUENTRA UN NODO TERMINAL: "<< table->Score<< std::endl;
        //////////////////////////////se puede hacer delete table aqui???????????????????
        //  std::cout << "!!!!!borra en nodo final"<< std::endl;

        //   delete  table;
        // table = NULL;
        return ev;
    }

    // int rama = 6;
    // bool betaBreak = false;

    // for(int i=0; i<12;i++)
    // {
    //    std::cout << int(table->casillasInt[(i*12)])<<"    "  << int(table->casillasInt[(i*12)+1])<<"    " << int(table->casillasInt[(i*12)+2])<<"    "<<int(table->casillasInt[(i*12)+3])<<"    "<<int(table->casillasInt[(i*12)+4])<<"    "<<int(table->casillasInt[(i*12)+5])<<"    "<<int(table->casillasInt[(i*12)+6])<<"    "<<int(table->casillasInt[(i*12)+7]) <<"    " <<int(table->casillasInt[(i*12)+8])<<"    " << int(table->casillasInt[(i*12)+9])<<"    " << int(table->casillasInt[(i*12)+10])<<"    " << int(table->casillasInt[(i*12)+11])<<"    " << std::endl;
    //  }
    // std::cout << "GENERAMOV " << std::endl;







    //std::cout << "!!!!!!!!!!!!!!!!!!TAMAÑO VECTOR DE TABLEROS HIJO: "<< table->vectorJugadas.size()<< std::endl;

    if (!Movimientos::generaMovimientos(table))
    {
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS (JAQUE MATE O AHOGADO)!!!: " << std::endl;
        return 0;
    }







    //   for (std::vector<unsigned char*>::iterator it = table->vectorJugadas.begin(); it!=table->vectorJugadas.end(); it+2)
    //  {
    //     std::cout << "tabla"<<  it - table->vectorJugadas.begin() << std::endl;

    //    std::cout << "VALOR ITERADOR: "<< int(*it[0])<< std::endl;
    //    std::cout << "VALOR ITERADOR: "<< int(*it[1])<< std::endl;
    //  }

    //  unsigned char jugadaElegida[2];
    int score;
    for (std::vector<unsigned char*>::iterator it = table->vectorJugadas.begin(); it!=table->vectorJugadas.end(); it++)
    {
        // std::cout << "forrrrrrrrrr"<< std::endl;

        // std::cout << "!!!!!!!!!!!!!!!!!!SE AVENTURA EN LA TABLA NUMERO: "<< it - table->vectorJugadas.begin() <<" NIVEL: "<< depthleft<< " ALFA: "<<  alpha<<  " BETA: "<<  beta <<std::endl;

        // std::cout << "null"<< std::endl;

        unsigned char* jugada = *it;

        //  std::cout << "VALOR ITERADOR: "<< int(jugada[0])<< std::endl;
        // std::cout << "VALOR ITERADOR: "<< int(jugada[1])<< std::endl;
        table->jugada[0] = jugada[0];
        table->jugada[1] = jugada[1];
       // std::cout << "aplica"<< std::endl;

        ModeloTablero* tablero = Movimientos::aplicaMovimiento(*table);
       // std::cout << "sale"<< std::endl;

        if (tablero != NULL)
        {
            //    int valorAtaqueAcumulado;

            score = -alphaBeta(tablero, -beta,-alpha, depthleft - 1 );
          //  std::cout << "resultchungo"<< std::endl;
            delete tablero;
            tablero = NULL;
            // std::cout << "!!!!!!!!!!!!!!!!!!SALE DE LA AVENTURA EN LA TABLA  SCORE: "<< score<< " ALFA: "<<  alpha<<  " BETA: "<<  beta << " NIVEL:" << depthleft<< std::endl;
            //  std::cout << "!!!!!!!!!!!!!FOR"<< std::endl;
            // it++;

            if( score >= beta )
            {
              //  std::cout << "!!!!!!!!!!!!!!!!!! fail hard beta-cutoff SCORE: "<< score <<" BETA: " << beta << std::endl;
                //DEJA DE CALCULAR HEURISTICAS
                /////////////TAL VEZ se pueda hacer el delete del elemento de vectormov aqui??????
                //  table->Score = score;

                //problema: se borran los del primer nivel
                //  delete table;
                // table = NULL;
                //delete table->vectorMov.at(i);
                // table->vectorMov.at(i) = NULL;

              //  delete [] jugada;

               //if (table->nodoInicial)
              //  {

               // }
                // Movimientos::deshazMovimiento(table);
                return beta;
                //  fail hard beta-cutoff
            }
            else if( score > alpha )
            {
              //  std::cout << "casillasProtegidas!!si"<< std::endl;
                //std::cout << "!!!!!!!!SCORE " <<score<< " ALPHA: "  <<alpha << std::endl;

                //std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa: "<< score <<" ALFA: " << alpha << std::endl;
                alpha = score;
                // table->Score = score;
                //LE PASA EL MOVIMIENTO A SU PADRE SOLO SI EL PADRE ES EL INICIAL
                //      std::cout << "!!nodo inicial"<< std::endl;
                if (table->nodoInicial)
                {//RELLENA LA JUGADA DEL NODO INICIAL
                   std::cout << "!!!!!!!!!!!!NODO INICIAL " << int(jugada[0])<< " JUGADA: "  << int(jugada[1]) << std::endl;
                    Modelo::getSingletonPtr()->jugadaElegida[0] = jugada[0];
                    Modelo::getSingletonPtr()->jugadaElegida[1] = jugada[1];
                    // table->jugada[0] = static_cast<ModeloTablero*>(table->vectorMov.at(i))->jugada[0];
                    //table->jugada[1] = static_cast<ModeloTablero*>(table->vectorMov.at(i))->jugada[1];
                }
                // jugada = new int[2];
                //  std::cout << "!!!!!!!!!!!!!!!!!! actualiza JUGADA en nodo INCIAL: " << std::endl;
                //      std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa ORIGEN: "<< table->jugada[0]  << std::endl;
                //   std::cout << "!!!!!!!!!!!!!!!!!! actualiza alfa DESTINO: "<< table->jugada[1]   << std::endl;
                // std::cout << "!!!!!!!!!!!!!!!!!! FIN actualiza alfa: "<< std::endl;

                // alpha acts like max in MiniMax
                //  std::cout << "fin"<< std::endl;

            }
            //   std::cout << "deleterrrrr"<< std::endl;

            // Movimientos::deshazMovimiento(table);
            // delete tablero;
            // std::cout << "null"<< std::endl;

            // tablero = NULL;
        }//else std::cout << "MOVIMIENTO INVALIDO"<< std::endl;

        //else  std::cout << "!!BETA BREAAAAK "  << std::endl;

        //problema: se borran los del primer nivel
        // std::cout << "!!FINFOR "  << std::endl;

      //  delete [] jugada;

       // if (table->nodoInicial)
        //{
       //   delete tablero;
        //  tablero = NULL;
       // }

    }

    //for(int i = 0; i < table->vectorMov.size(); i++)
    //  {
    //     if (table->vectorMov.at(i) != NULL)
    //      {
    //         delete table->vectorMov.at(i);
    //         table->vectorMov.at(i) = NULL;
    //        }
    //    }

    //  numeroHijos=0;
    //    table->vectorMov.clear();


    // std::cout << "!!RETURN "  << std::endl;
    //  delete table;
    //  table = NULL;
    //table->vectorMov.clear();
    return alpha;
}

int ArbolBusqueda::evaluaTablero(ModeloTablero* tablero)
{
    int suma = 0;
    //   BlackCheck = false;


    //EMPIEZA CONTANDO LAS FICHAS DEL TABLERO Y HACIENDO UNA SUMA SIMPLE...

    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {
            //Busca las fichas del mismo color del turno
            if (tablero->casillasInt[(i*12)+y] < 0)
            {
                //if(casillasInt[(i*12)+y] == -6){
                //   BlackCheck = false;
                //   }

                suma =  suma - valorFicha(tipoFicha(-tablero->casillasInt[(i*12)+y]));

            }else if (tablero->casillasInt[(i*12)+y] > 0)
            {
                suma =  suma + valorFicha(tipoFicha(tablero->casillasInt[(i*12)+y]));
            }
            //MVV (Most valuable victim)/LVA (Least valuable attacker)

        }
    }


   // if (tablero->valorAtaque > 0)
   // {// si es mayor que 0 es que el valor del atacante es mayor
      //  std::cout << "LA FICHA ES MAYOR "  <<   std::endl;

    //    suma = suma - (tablero->valorAtaque * 200);

   // }else if (tablero->valorAtaque < 0)
   // {
       // std::cout << "LA FICHA ES MENOR " <<   std::endl;
       // suma = suma + (tablero->valorAtaque * 200);
    //}


    //NO TIENE SENTIDO AÑADIR ALGO TAN COSTOSO A CADA MOVIMIENTO SI SOLO SE VA A EVALUAR AL FINAL, PRUEBA CON MUEVEFICHA O SI NO USALO PARA ORDENAR MAS LA LISTA

    if (tablero->valorDefensivo != 0)
    {

        //EL VALOR DEFENSIVO DEPENDE DE LAS QUE PROTEGIA EN EL TABLERO PADRE Y SE SUPONE QUE SE PIERDE SI SE MUEVE


        std::cout << "VALOR DEFENSIVO: "  << tablero->valorDefensivo  <<std::endl;
        suma = suma - (tablero->valorDefensivo);

    }


    // for (int i = 26; i< 118;i++)
    //  {
    //  miTablero->vectorJugadas


    //     miTablero->vectorJugadas.at()

    //  }



    //if(!turnoN)
    //{
    //SI EL NODO TERMINAL ES TURNO BLANCAS SE INVIERTE LA SUMA, ASI LA SUMA POSITIVA ES LA DE LAS NEGRAS
    //  std::cout << "turno  blancas suma: " << suma<< std::endl;

    //suma = -suma;

    //}

  //  std::cout << "tablero->valorDefensivo " << tablero->valorDefensivo   <<std::endl;

   //if(suma!=0)std::cout << "ESTE TABLERO TIENE VALOR DISTINTO DE 0 Y HA ACUMULADO UN VALOR DE: " << suma   <<std::endl;
  // else std::cout << "ESTE TABLERO TIENE VALOR 0 "    <<std::endl;


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


