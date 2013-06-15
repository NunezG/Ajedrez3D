#include "../../headers/Modelo/Movimientos.h"



bool Movimientos::generaMovimientos(ModeloTablero* miTablero, tipoFicha tipo)
{
    // ModeloTablero nuevoTablero;
    // std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!   " << miTablero->turnoN << " JAQUE? "<< testJaque<<std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS


    //  std::cout << "!!!!!!!!!!!!!!!!!!BORRA VECTOR PREVIO "<<std::endl;

    /*
    int rey = 6;
    int reina = 5;
    int torre = 4;
    int alfil = 3;
    int caballo = 2;
    int peon = 1;
*/

    //CADA VEZ QUE ENCUENTRA UNA FICHA DEVUELVE SUS MOVIMIENTOS Y ANTES DE BUSCAR OTRA SE BORRAN, ASI SE AHORRA MEMORIA

    for (int i = 0; i< 120;i++)
    {

        //   std::cout << "FOR "<< miTablero->casillasInt[(i*12)+y] << std::endl;
        /*
            if (miTablero->casillasInt[(i*12)+y] > 0)
            {
                std::cout << "!!!ENCUENTRA FICHA EN: " <<  (i*12)+y <<std::endl;
            }
*/

        if (miTablero->casillasInt[i] == tipo)
        {
            //     std::cout << "!!!ENCUENTRA FICHA EN: " <<  i << " DE TIPO "<< tipo <<std::endl;
            if (mueveFicha(miTablero, false, i, tipo))
            {
                //    std::cout << "!!!mueve ficha: " <<  i << " DE TIPO " << tipo <<std::endl;

                //    if (testJaque) return false;
            }

        }

        // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
    }


    // std::cout << "!!!!!!!!RETORNO!!!!!!!!   " <<std::endl;
    if (miTablero->vectorMov.size() == 0)
    {
        // std::cout << "!!!!!JAQUE MATE O AHOGADO AL FINAL DE MOVIMIENTOS!!!   " <<std::endl;
        return true; //JAQUE MATE O AHOGADO
    }
    //  std::cout << "generamov"<< std::endl;
}



bool Movimientos::pruebaJaqueMate(ModeloTablero* miTablero)
{
    // ModeloTablero nuevoTablero;
    // std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!   " << miTablero->turnoN << " JAQUE? "<< testJaque<<std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    miTablero->vectorMov.clear();
    /*
    int rey = 6;
    int reina = 5;
    int torre = 4;
    int alfil = 3;
    int caballo = 2;
    int peon = 1;
*/

    for (int i = 0; i< 120;i++)
    {
        //   std::cout << "FOR "<< miTablero->casillasInt[(i*12)+y] << std::endl;
        /*
            if (miTablero->casillasInt[(i*12)+y] > 0)
            {
                std::cout << "!!!ENCUENTRA FICHA EN: " <<  (i*12)+y <<std::endl;
            }
*/
        if (miTablero->casillasInt[i] > 0 && miTablero->casillasInt[i] < 90)
        {
            if (mueveFicha(miTablero, true,i, tipoFicha(miTablero->casillasInt[i])))
            {
                return false;
            }

        }

        // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
    }

    // std::cout << "!!!!!!!!RETORNO!!!!!!!!   " <<std::endl;

    // std::cout << "!!!!!JAQUE MATE O AHOGADO AL FINAL DE MOVIMIENTOS!!!   " <<std::endl;
    return true; //JAQUE MATE O AHOGADO

    //  std::cout << "generamov"<< std::endl;
}

bool Movimientos::mueveFicha(ModeloTablero* miTablero, bool testJaque, int casilla, tipoFicha tipo)
{
    bool fichamovida = false;

    switch (tipo)
    {

    case Rey:
        //ENCUENTRA REY
        //  std::cout << "!!!!!!!!!REY!!!!!!!!   " <<std::endl;

        fichamovida = mueveRey(miTablero, casilla, testJaque);

        break;

    case Reina:
        //std::cout << "!!!!!!!!!REINA!!!!!!!!!   " <<std::endl;

        //ENCUENTRA REINA

        fichamovida = mueveReina(miTablero, casilla, testJaque);

        //  std::cout << "!!!!!!!!!HA MOVIDO LA REINA!!!!!!!!!!   " <<std::endl;

        break;

    case Torre:
        // std::cout << "!!!!!!!!!TORRE!!!!!!!!!   " <<std::endl;
        //ENCUENTRA TORRE

        fichamovida = mueveTorre(miTablero, casilla, testJaque);

        // std::cout << "!!!!!!!!!HA MOVIDO LA TORRE!!!!!!!!!!   " <<std::endl;

        break;

    case Alfil:
        //std::cout << "!!!!!!!!!ALFIL!!!!!!!!   " <<std::endl;
        //ENCUENTRA ALFIL

        fichamovida = mueveAlfil(miTablero, casilla, testJaque);

        //   std::cout << "!!!!!!!!!HA MOVIDO EL ALFIL!!!!!!!!!!   " <<std::endl;

        break;

    case Caballo:

        //  std::cout << "!!!!!!!!!CABALLO!!!!!!!!!!   " <<std::endl;
        //ENCUENTRA CABALLO
        fichamovida = mueveCaballo(miTablero, casilla, testJaque);

        // std::cout << "!!!!!!!!!HA MOVIDO EL CABALLO!!!!!!!!!!   " <<std::endl;

        break;

    case Peon:
        //  std::cout << "!!!!!!!!!!!!!!!!!!PEON!!!!!!!!!!!!!!!!!! "<< std::endl;
        //ENCUENTRA PEON

        fichamovida = muevePeon(miTablero, casilla, testJaque);

        //  std::cout << "!!!!!!!!!HA MOVIDO EL PEON!!!!!!!!!!   " <<std::endl;

        break;

    default:
        break;
    }


    return fichamovida;

}


//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?
bool Movimientos::mueveReina(ModeloTablero* miTablero, int casilla, bool testJaque)
{
    bool torre = mueveTorre(miTablero, casilla, testJaque);
    bool alfil = mueveAlfil(miTablero, casilla, testJaque);

    if (testJaque)
    {
        if (torre) return true;
        else if (alfil) return true;
        else return false;

    }

}

bool Movimientos::muevePeon(ModeloTablero* miTablero, int casilla, bool testJaque)
{
    int nuevaCasilla;
    int casillaCome;
    int casillaComeSec;
    int salto;
    int filaPeon;
    int filaPromocion;



    if (miTablero->turnoN)
    {
        // std::cout << "!!!!!!!!!!!TURNO NEGRAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla-24;
        nuevaCasilla = casilla-12;
        casillaCome = casilla-11;
        casillaComeSec= casilla-13;
        filaPeon = 8;
        filaPromocion = 2;
        //  std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        // std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;



        //   nuevaCasilla = casilla+1;
        //    bool peonEnemigo = false;


    }else
    {
        // std::cout << "!!!!!!!!!!!TURNO BLANCAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla+24;
        nuevaCasilla = casilla+12;
        casillaCome = casilla+11;
        casillaComeSec= casilla+13;
        filaPeon = 3;
        filaPromocion = 9;

        //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        //std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

    }

    //MOVIMIENTO NORMAL
    if(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        //PROMOCION A REINA
        if (nuevaCasilla/12 == filaPromocion)
        {
            std::cout << "!!!!!!PROMOCION A REINA DEL PEON!!!!!" << std::endl;
            miTablero->casillasInt[casilla] = 5;
        }

        // std::cout << "!!!!!!MUEVE UNA CASILLA!!!!!!" << std::endl;
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            if (testJaque) return true;

        }
        miTablero->casillasInt[casilla] = 1;
    }



    //DOBLE SALTO
    if(casilla/12 == filaPeon && miTablero->casillasInt[salto] == 0)
    {
        if(aplicaMovimiento(*miTablero, casilla, salto))
        {
            // std::cout << "!!!!!!!!!!!MUEVE DOS CASILLAS!!!!!!!!" << std::endl;
            if (testJaque) return true;
        }
        //  miTablero->casillasInt[miTablero->alPaso] = 1;

    }

    //COME ENEMIGA
    if (miTablero->casillasInt[casillaCome] < 0)
    {

        //PROMOCION A REINA
        if (nuevaCasilla/12 == filaPromocion)
        {
            std::cout << "!!!!!!PROMOCION A REINA DEL PEON!!!!!" << std::endl;
            miTablero->casillasInt[casilla] = 5;
        }


        //   std::cout << "NEGRAS COME 1"<< std::endl;
        if( aplicaMovimiento(*miTablero, casilla, casillaCome))
        {
            if (testJaque) return true;
        }

        miTablero->casillasInt[casilla] = 1;


    }

    //COME ENEMIGA 2
    if (miTablero->casillasInt[casillaComeSec] < 0)
    {

        //PROMOCION A REINA
        if (nuevaCasilla/12 == filaPromocion)
        {
            std::cout << "!!!!!!PROMOCION A REINA DEL PEON!!!!!" << std::endl;
            miTablero->casillasInt[casilla] = 5;
        }

        //  std::cout << "NEGRAS COME 2"<< std::endl;


        if (aplicaMovimiento(*miTablero, casilla, casillaComeSec))
        {
            if (testJaque) return true;
        }

        miTablero->casillasInt[casilla] = 1;

    }


    //COME AL PASO PEON ENEMIGO
    if(miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaCome] == 0)
    {
        if ((miTablero->alPaso == casillaCome-12
             && (casilla == casillaCome-13
                 || casilla == casillaCome-11))
                ||( miTablero->alPaso == casillaCome+12
                    &&(casilla == casillaCome+13
                       || casilla == casillaCome+11 )))
        {
            //    std::cout << "COME LA FICHA DE LA DERECHA AL PASO"<< std::endl;
            // fichaAlPaso = miTablero->casillasInt[miTablero->alPaso]; //ficha enemiga, supuestamente negativa
            //  std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (posicion) : " <<miTablero->alPaso<< std::endl;
            // std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (siempre tiene que ser 1): " <<fichaAlPaso<< std::endl;

            miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;

            if(aplicaMovimiento(*miTablero, casilla, casillaCome))
            {
                if (testJaque) return true;
            }

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }



    }

    //COME AL PASO 2 PEON ENEMIGO
    if ((miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaComeSec] == 0))
    {


        if ((miTablero->alPaso == casillaComeSec-12
             && (casilla == casillaComeSec-13
                 || casilla == casillaComeSec-11))
                ||( miTablero->alPaso == casillaComeSec+12
                    &&(casilla == casillaComeSec+13
                       || casilla == casillaComeSec+11 )))
        {
            //      std::cout << "NEGRA COME LA FICHA DE LA IZQUIERDA AL PASO"<< std::endl;
            // fichaAlPaso = miTablero->casillasInt[miTablero->alPaso]; //ficha enemiga, supuestamente negativa
            //    std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (posicion) : " <<miTablero->alPaso<< std::endl;
            //std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (siempre tiene que ser 1): " <<fichaAlPaso<< std::endl;

            miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;


            //   std::cout << "NEGRAS COME AL PASO 2"<< std::endl;
            if (aplicaMovimiento(*miTablero, casilla, casillaComeSec))
            {
                if (testJaque) return true;
            }

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }



    }




    if (testJaque) return false;

    // std::cout << "!!!!FIN!!!!!!!!!!!!!!!: "  <<std::endl;

    //  for (int i = 0;  i< miTablero->vectorMov.size(); i++)
    //    {
    //     ModeloTablero puntTab = miTablero->vectorMov.at(i);
    //      std::cout << "!!!MUEVE DE: " <<    puntTab.movimiento[0]  << std::endl;
    //      std::cout << "!!!A: " <<    puntTab.movimiento[1]  << std::endl;

    //  }
}



bool Movimientos::mueveTorre(ModeloTablero* miTablero,const int casilla, bool testJaque)
{
    //mueve a todas las casillas posibles
    //mira si esta ocupada
    int nuevaCasilla = casilla-1;
    bool ocupado;
    bool pasa = true;

    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;
            }
            if (ocupado) break;
        }else break;
        nuevaCasilla = nuevaCasilla-1;
    }

    nuevaCasilla = casilla+1;
    pasa = true;
    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;
            }
            if (ocupado) break;
        }else break;
        nuevaCasilla = nuevaCasilla+1;
    }

    nuevaCasilla = casilla-12;
    pasa = true;
    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;
            }
            if (ocupado) break;
        }else break;

        nuevaCasilla = nuevaCasilla-12;
    }

    nuevaCasilla = casilla+12;
    pasa = true;
    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;
            }
            if (ocupado) break;
        }else break;
        nuevaCasilla = nuevaCasilla+12;
    }

    if (testJaque) return false;

}



bool Movimientos::mueveAlfil(ModeloTablero* miTablero, int casilla, bool testJaque)
{
    int nuevaCasilla = casilla-13;

    bool pasa = true;
    bool ocupado;

    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;

            }
            if (ocupado) break;

        } else break;

        nuevaCasilla = nuevaCasilla-13;
    }

    nuevaCasilla = casilla-11;
    pasa = true;
    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;

            }
            if (ocupado) break;

        } else break;

        nuevaCasilla = nuevaCasilla-11;
    }

    nuevaCasilla = casilla+13;
    pasa = true;
    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;

            }
            if (ocupado) break;
        } else break;

        nuevaCasilla = nuevaCasilla+13;
    }

    nuevaCasilla = casilla+11;
    pasa = true;
    while(pasa)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                if (testJaque) return true;

            }
            if (ocupado) break;
        } else break;

        nuevaCasilla = nuevaCasilla+11;
    }

    if (testJaque) return false;

}


int Movimientos::pruebaCamino(ModeloTablero* miTablero, int salto)
{
    //   int Dif = casillaFinal - casillaInicial;

    int resultado = 0;
    // int ocupado = false;
    int nuevaCasilla = miTablero->jugada[0];
    bool pasa = true;

    while(pasa)
    {
        nuevaCasilla = nuevaCasilla+salto;
        std::cout << "!!!!PRUEBA CAMINO!!!: " << nuevaCasilla  <<std::endl;

        pasa = miTablero->casillasInt[nuevaCasilla] == 0;


        if (nuevaCasilla == miTablero->jugada[1])
        {
            int fichavieja = miTablero->casillasInt[miTablero->jugada[0]];
            int fichaNueva = miTablero->casillasInt[nuevaCasilla];

            miTablero->casillasInt[nuevaCasilla] = fichavieja;
            miTablero->casillasInt[miTablero->jugada[0]] = 0;

            std::cout << "!!!mira si es jaque!" << std::endl;


            if (miTablero->evaluaJaque())
            {
                std::cout << "!!!!!HA EVALUADO UN JAQUE (DESPUES DE MOVER) !!!" << std::endl;
                resultado = 2;
            }
            else
                resultado= 1;

            miTablero->casillasInt[nuevaCasilla] = fichaNueva;
            miTablero->casillasInt[miTablero->jugada[0]] = fichavieja;


            std::cout << "!!!retorna resultado: "<<resultado << std::endl;

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

bool Movimientos::mueveCaballo(ModeloTablero* miTablero, int casilla, bool testJaque)
{
    int nuevaCasilla;
    nuevaCasilla = casilla-25;
    bool pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {

        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla-23;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+25;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+23;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {
        //   std::cout << "pasacvaballo"<< std::endl;

        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla-10;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla-14;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {

            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+10;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {

            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+14;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {

            if (testJaque) return true;
        }
    }

    if (testJaque) return false;
    // else return true;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero, int casilla, bool testJaque)
{
     // std::cout << "MUEVE REY"<< miTablero->turnoN<< std::endl;
    int nuevaCasilla;
    //   bool pasa = false;
    int filaRey;

    if (miTablero->turnoN) filaRey = 9;
    else filaRey = 2;

    if (casilla/12 == filaRey)
    {
        //  std::cout << "REY EN FILA: "<< filaRey<< "Y TURNO: "<< miTablero->turnoN<<std::endl;
        //ENROQUE CORTO (DERECHA)
        nuevaCasilla = casilla + 3;
        if (miTablero->casillasInt[nuevaCasilla] == 4 && miTablero->casillasInt[casilla+2] == 0 && miTablero->casillasInt[casilla+1] == 0)
        {
            miTablero->casillasInt[nuevaCasilla] = 0;
            miTablero->casillasInt[casilla+1] = 4;

            nuevaCasilla = casilla+2;

            //  std::cout << "APLICA MOVIMIENTO REY +3 (enroque corto): "<< miTablero->turnoN << std::endl;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                // std::cout << "APLICADO"<< std::endl;
                if (testJaque) return true;
            }
            //  std::cout << "REVIERTE 1"<< std::endl;

            miTablero->casillasInt[casilla+3] = 4;
            miTablero->casillasInt[casilla+1] = 0;
        }

        //ENROQUE LARGO (IZQUIERDA)
        nuevaCasilla = casilla-4;

        if (miTablero->casillasInt[nuevaCasilla] == 4 && miTablero->casillasInt[casilla-1] == 0 && miTablero->casillasInt[casilla-2] == 0 && miTablero->casillasInt[casilla-3] == 0)
        {
            miTablero->casillasInt[nuevaCasilla] = 0;
            miTablero->casillasInt[casilla-1] = 4;

            nuevaCasilla = casilla-2;

            // std::cout << "APLICA MOVIMIENTO REY -4 (enroque largo): "<< miTablero->turnoN <<std::endl;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
            {
                //  std::cout << "APLICADO"<< std::endl;

                if (testJaque) return true;
            }
            //  std::cout << "REVIERTE 2"<< std::endl;

            miTablero->casillasInt[casilla-4] = 4;
            miTablero->casillasInt[casilla-1] = 0;
        }
    }

    //IZQUIERDA
    nuevaCasilla = casilla-1;
    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        //  std::cout << "APLICA MOVIMIENTO REY -1"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            // std::cout << "REY MOVIDO"<< std::endl;
            if (testJaque) return true;
        }
    }

    //DERECHA
    nuevaCasilla = casilla+1;
    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        //  miTablero->fichaMovida = "REY!!!!";
        //   std::cout << "APLICA MOVIMIENTO REY +1"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            // std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //ATRAS
    nuevaCasilla = casilla-12;
    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        // std::cout << "APLICA MOVIMIENTO REY -12"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            // std::cout << "REY MOVIDO"<< std::endl;
            if (testJaque) return true;
        }
    }

    //ADELANTE
    nuevaCasilla = casilla+12;
    //  pasa = false;
    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        //  std::cout << "APLICA MOVIMIENTO REY +12"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            //std::cout << "REY MOVIDO"<< std::endl;
            if (testJaque) return true;
        }
    }

    //NE
    nuevaCasilla = casilla+13;
    // pasa = false;
    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        //    TableroMovido->fichaMovida = "REY!!!!";
        //  std::cout << "APLICA MOVIMIENTO REY +13"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            //std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //NO
    nuevaCasilla = casilla+11;
    // pasa = false;

    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        //  std::cout << "APLICA MOVIMIENTO REY +11"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            //std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //SO
    nuevaCasilla = casilla-13;
    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";
        //   std::cout << "APLICA MOVIMIENTO REY -13"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            // std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //SE
    nuevaCasilla = casilla-11;
    if (miTablero->casillasInt[nuevaCasilla] <= 0)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";
        //   std::cout << "APLICA MOVIMIENTO REY -11"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla))
        {
            // std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    if (testJaque) return false;
}

bool Movimientos::aplicaMovimiento(ModeloTablero &miTablero, int casOrigen, int casDestino)
{
    ModeloTablero* TableroMovido = NULL;
    //   std::cout << "!!!!!!!!!FICHA ORIGEN!!!!!!:" << fichaOrigen << std::endl;
    //     std::cout << "!!!!!!!!!FICHA DESTINO!!!!!!:" << miTablero.casillasInt[casDestino] << std::endl;
    // TableroMovido->alPaso = -1;

    int fichavieja = miTablero.casillasInt[casOrigen];
    int fichaNueva = miTablero.casillasInt[casDestino];

    miTablero.casillasInt[casDestino] = fichavieja;
    miTablero.casillasInt[casOrigen] = 0;

    //    std::cout << "casOrigen "<<casOrigen <<std::endl;
    //  std::cout << "casDestino "<<casDestino <<std::endl;
    //std::cout << "fichaOrigen "<<fichaOrigen <<std::endl;
    // std::cout << "fichaDestino "<<fichaDestino <<std::endl;
  //  TableroMovido->turnoN = !TableroMovido->turnoN;

  //  std::cout << "!!!!APLICAMOVIMIENTTTTT!!" << std::endl;

    if (miTablero.evaluaJaque())
    {
      //  std::cout << "!!!!!HA EVALUADO UN JAQUE EN EL ARBOL (DESPUES DE MOVER) !!!" << std::endl;
       // delete TableroMovido;

        miTablero.casillasInt[casDestino] = fichaNueva;
        miTablero.casillasInt[casOrigen] = fichavieja;

        return false;
    }
    else
    {
        TableroMovido = new ModeloTablero(miTablero);

        TableroMovido->jugada[0] = casOrigen;
        TableroMovido->jugada[1] = casDestino;

        miTablero.casillasInt[casDestino] = fichaNueva;
        miTablero.casillasInt[casOrigen] = fichavieja;

        if (miTablero.casillasInt[casOrigen] == 1 && (casDestino - casOrigen  == 24 || casOrigen - casDestino == 24))
        {
            TableroMovido->alPaso = casDestino;
            //std::cout << "!!!!!!!!!DOBLE SALTO EN IA!!!!!!:" <<TableroMovido->alPaso <<std::endl;
        }
        //   TableroMovido->turnoN = !miTablero.turnoN;

       miTablero.vectorMov.push_back(TableroMovido);
    //   std::cout << "!!!!TABLERO AÑADIDO!" << std::endl;

        return true;
    }

    miTablero.casillasInt[casDestino] = fichaNueva;
    miTablero.casillasInt[casOrigen] = fichavieja;

    return false;

    // miTablero.numeroHijos++;
    //REVIERTE EL MOVIMIENTO
    // return false;
}
