#include "../../headers/Modelo/Movimientos.h"



bool Movimientos::generaMovimientos(ModeloTablero* miTablero, bool testJaque)
{
    // ModeloTablero nuevoTablero;
    std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!   " << miTablero->turnoN << " JAQUE? "<< testJaque<<std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS



    miTablero->vectorMov.clear();



    int rey = 6;
    int reina = 5;
    int torre = 4;
    int alfil = 3;
    int caballo = 2;
    int peon = 1;



    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {
            //   std::cout << "FOR "<< miTablero->casillasInt[(i*12)+y] << std::endl;
            /*
            if (miTablero->casillasInt[(i*12)+y] > 0)
            {
                std::cout << "!!!ENCUENTRA FICHA EN: " <<  (i*12)+y <<std::endl;

            }

*/
            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
            if (miTablero->casillasInt[(i*12)+y] == rey)
            {
                std::cout << "!!!!!!!!!REY!!!!!!!!   " <<std::endl;


                //ENCUENTRA REY

                if (mueveRey(miTablero, (i*12)+y, testJaque))
                {

                    std::cout << "!!!!!!!!!HA MOVIDO EL REY!!!!!!!!!!   " <<std::endl;


                    if (testJaque) return false;

                }

            }else

                // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
                if (miTablero->casillasInt[(i*12)+y] == reina)
                {

                    std::cout << "!!!!!!!!!REINA!!!!!!!!!   " <<std::endl;

                    //ENCUENTRA REINA

                    if (mueveReina(miTablero, (i*12)+y, testJaque))
                    {

                        std::cout << "!!!!!!!!!HA MOVIDO LA REINA!!!!!!!!!!   " <<std::endl;


                        if (testJaque) return false;


                    }

                }else

                    // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
                    if (miTablero->casillasInt[(i*12)+y] == torre)
                    {

                        std::cout << "!!!!!!!!!TORRE!!!!!!!!!   " <<std::endl;


                        //ENCUENTRA TORRE

                        if (mueveTorre(miTablero, (i*12)+y, testJaque))
                        {
                            std::cout << "!!!!!!!!!HA MOVIDO LA TORRE!!!!!!!!!!   " <<std::endl;

                            if (testJaque) return false;


                        }

                    }else

                        // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
                        if (miTablero->casillasInt[(i*12)+y] == alfil)
                        {
                            std::cout << "!!!!!!!!!ALFIL!!!!!!!!   " <<std::endl;


                            //ENCUENTRA ALFIL

                            if (mueveAlfil(miTablero, (i*12)+y, testJaque))
                            {

                                std::cout << "!!!!!!!!!HA MOVIDO EL ALFIL!!!!!!!!!!   " <<std::endl;

                                if (testJaque) return false;


                            }

                        }else

                            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
                            if (miTablero->casillasInt[(i*12)+y] == caballo)
                            {


                                std::cout << "!!!!!!!!!CABALLO!!!!!!!!!!   " <<std::endl;

                                //ENCUENTRA CABALLO

                                if (mueveCaballo(miTablero, (i*12)+y, testJaque))
                                {

                                    std::cout << "!!!!!!!!!HA MOVIDO EL CABALLO!!!!!!!!!!   " <<std::endl;

                                    if (testJaque) return false;

                                }

                            }else

                                // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
                                if (miTablero->casillasInt[(i*12)+y] == peon)
                                {
                                    std::cout << "!!!!!!!!!!!!!!!!!!PEON!!!!!!!!!!!!!!!!!! "<< std::endl;


                                    //ENCUENTRA PEON

                                    if (muevePeon(miTablero, (i*12)+y, testJaque))
                                    {
                                        std::cout << "!!!!!!!!!HA MOVIDO EL PEON!!!!!!!!!!   " <<std::endl;

                                        if (testJaque) return false;

                                    }
                                    //   std::cout << "!!!!!!!!!!!!!!!!!!ACABA MUEVE PEON!!!!!!!!!!!!!!!!!!!" << std::endl;


                                }


        }
    }

    std::cout << "!!!!!!!!RETORNO!!!!!!!!   " <<std::endl;

    if (miTablero->vectorMov.size() == 0)
        return true; //JAQUE MATE O AHOGADO


    //  std::cout << "generamov"<< std::endl;



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

    if (miTablero->turnoN)
    {
        std::cout << "!!!!!!!!!!!TURNO NEGRAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla-24;
        nuevaCasilla = casilla-12;
        casillaCome = casilla-11;
        casillaComeSec= casilla-13;
        //  std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        // std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if(casilla > 96 && miTablero->casillasInt[salto] == 0)
        {


            if(aplicaMovimiento(*miTablero, casilla, salto, testJaque))
            {
                std::cout << "!!!!!!!!!!!MUEVE DOS CASILLAS!!!!!!!!" << std::endl;
                if (testJaque) return true;
            }

            //  miTablero->casillasInt[miTablero->alPaso] = 1;

        }

        if(miTablero->casillasInt[nuevaCasilla] == 0)
        {
            //PROMOCION A REINA
            if (nuevaCasilla < 36)
            {
                //        miTablero->casillasInt[nuevaCasilla] = 0;
                //        peonEnemigo == true;
                std::cout << "!!!!!!PROMOCION A REINA DEL PEON!!!!!" << std::endl;


                miTablero->casillasInt[casilla] = 5;
            }
            std::cout << "!!!!!!MUEVE UNA CASILLA!!!!!!" << std::endl;

            if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;

            }
        }

        //   nuevaCasilla = casilla+1;
        //    bool peonEnemigo = false;

        if (miTablero->casillasInt[casillaCome] < 0)
        {
            std::cout << "NEGRAS COME 1"<< std::endl;
            if( aplicaMovimiento(*miTablero, casilla, casillaCome, testJaque))
            {
                if (testJaque) return true;
            }

        }

        if(miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaCome] == 0)
        {
            std::cout << "COME LA FICHA DE LA DERECHA AL PASO"<< std::endl;


            if ((miTablero->alPaso == casillaCome-12
                 && (casilla == casillaCome-13
                     || casilla == casillaCome-11))
                    ||( miTablero->alPaso == casillaCome+12
                        &&(casilla == casillaCome+13
                           || casilla == casillaCome+11 )))
            {
                // fichaAlPaso = miTablero->casillasInt[miTablero->alPaso]; //ficha enemiga, supuestamente negativa
                std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (posicion) : " <<miTablero->alPaso<< std::endl;
                // std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (siempre tiene que ser 1): " <<fichaAlPaso<< std::endl;

                miTablero->casillasInt[miTablero->alPaso] = 0;
                //casillas[1] = 0;
            }



            if(aplicaMovimiento(*miTablero, casilla, casillaCome, testJaque))
            {
                if (testJaque) return true;
            }

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }
        if (miTablero->casillasInt[casillaComeSec] < 0)
        {
            std::cout << "NEGRAS COME 2"<< std::endl;


            if (aplicaMovimiento(*miTablero, casilla, casillaComeSec, testJaque))
            {
                if (testJaque) return true;
            }
        }

        if ((miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaComeSec] == 0))
        {
            std::cout << "COME LA FICHA DE LA IZQUIERDA AL PASO"<< std::endl;


            if ((miTablero->alPaso == casillaComeSec-12
                 && (casilla == casillaComeSec-13
                     || casilla == casillaComeSec-11))
                    ||( miTablero->alPaso == casillaComeSec+12
                        &&(casilla == casillaComeSec+13
                           || casilla == casillaComeSec+11 )))
            {
                // fichaAlPaso = miTablero->casillasInt[miTablero->alPaso]; //ficha enemiga, supuestamente negativa
                std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (posicion) : " <<miTablero->alPaso<< std::endl;
                //std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (siempre tiene que ser 1): " <<fichaAlPaso<< std::endl;

                miTablero->casillasInt[miTablero->alPaso] = 0;
                //casillas[1] = 0;
            }



            std::cout << "NEGRAS COME AL PASO 2"<< std::endl;
            if (aplicaMovimiento(*miTablero, casilla, casillaComeSec, testJaque))
            {
                if (testJaque) return true;
            }

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }

    }else
    {
        std::cout << "!!!!!!!!!!!TURNO BLANCAS EN PEON!!!!!!!!!!" << std::endl;
        salto = casilla+24;
        nuevaCasilla = casilla+12;
        casillaCome = casilla+11;
        casillaComeSec= casilla+13;



        if(casilla < 48 && miTablero->casillasInt[salto] == 0 )
        {
            std::cout << "!BLANCAS SALTAN!!!!!!" << std::endl;

            if (aplicaMovimiento(*miTablero, casilla, salto, testJaque))
            {
                if (testJaque) return true;
            }
        }


        //   std::cout << "!!!!!!!!!!!TURNO BLANCAS!!!!!!!!!!" << std::endl;
        if (miTablero->casillasInt[nuevaCasilla] == 0)
        {
            if (nuevaCasilla > 122){
                miTablero->casillasInt[casilla] = 5;
            }
            std::cout << "!!!!!!!!!!! BLANCAS AVANZA!!!!!!!!!!" << std::endl;

            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;
            }
        }
        //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
        //std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

        if (miTablero->casillasInt[casillaCome] < 0)
        {
            std::cout << "BLANCAS COME 1"<< std::endl;


            if (aplicaMovimiento(*miTablero, casilla, casillaCome, testJaque))
            {
                if (testJaque) return true;
            }
        }

        if ((miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaCome] == 0 ))
        {
            std::cout << "BLANCAS COME AL PASO 1"<< std::endl;


            if(aplicaMovimiento(*miTablero, casilla, casillaCome, testJaque))
            {
                if (testJaque) return true;
            }
        }


        if (miTablero->casillasInt[casillaComeSec] < 0 )
        {
            std::cout << "BLANCAS COME 2"<< std::endl;


            if( aplicaMovimiento(*miTablero, casilla, casillaComeSec, testJaque))
            {
                if (testJaque) return true;
            }
        }


        if ((miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaComeSec] == 0))
        {
            std::cout << " BLANCAS COME AL PASO 2, casilla: "<< casilla << " CASILLA COME SEC: "<<casillaComeSec << " ALPASO: "<<miTablero->alPaso<<std::endl;


            if(aplicaMovimiento(*miTablero, casilla, casillaComeSec, testJaque))
            {
                if (testJaque) return true;
            }
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

bool Movimientos::mueveAlfil(ModeloTablero* miTablero, int casilla, bool testJaque)
{
    int nuevaCasilla = casilla-13;

    bool pasa = false;
    bool come;

    while(nuevaCasilla%12 >2 && nuevaCasilla/12 >2)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;

            }
            if (come) break;

        } else break;

        nuevaCasilla = nuevaCasilla-13;
    }

    nuevaCasilla = casilla-11;
    pasa = false;
    while(nuevaCasilla%12 < 10 && nuevaCasilla/12 >2)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;

            }
            if (come) break;

        } else break;

        nuevaCasilla = nuevaCasilla-11;
    }

    nuevaCasilla = casilla+13;
    pasa = false;
    while(nuevaCasilla%12 < 10 && nuevaCasilla/12 < 10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;

            }
            if (come) break;
        } else break;

        nuevaCasilla = nuevaCasilla+13;
    }

    nuevaCasilla = casilla+11;
    pasa = false;
    while(nuevaCasilla%12 >2 && nuevaCasilla/12 < 10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            come = miTablero->casillasInt[nuevaCasilla] != 0;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;

            }
            if (come) break;
        } else break;

        nuevaCasilla = nuevaCasilla+11;
    }

    if (testJaque) return false;

}

bool Movimientos::mueveCaballo(ModeloTablero* miTablero, int casilla, bool testJaque)
{
    int nuevaCasilla;
    nuevaCasilla = casilla-25;
    bool pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {

        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla-23;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+25;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+23;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa)
    {
        std::cout << "pasacvaballo"<< std::endl;

        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla-10;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {


            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla-14;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {

            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+10;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {

            if (testJaque) return true;
        }
    }

    nuevaCasilla = casilla+14;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        if(aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {

            if (testJaque) return true;
        }
    }

    if (testJaque) return false;
    // else return true;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero, int casilla, bool testJaque)
{
    //  std::cout << "MUEVE REY"<< miTablero->turnoN<< std::endl;

    int nuevaCasilla;
    bool pasa = false;

    if (casilla < 36)
    {
        //ENROQUE CORTO
        bool torre = false;
        nuevaCasilla = casilla-3;

        pasa = false;
        torre = miTablero->casillasInt[nuevaCasilla] == 4;
        if (torre && miTablero->casillasInt[casilla-2] == 0&& miTablero->casillasInt[casilla-1] == 0)
        {
            nuevaCasilla = casilla-2;
            miTablero->casillasInt[casilla-3] = 0;
            miTablero->casillasInt[casilla-1] = 4;
            std::cout << "APLICA MOVIMIENTO REY -3 (enroque)"<< std::endl;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                std::cout << "REY MOVIDO"<< std::endl;

                if (testJaque) return true;
            }
        }
    }

    if (casilla > 122)
    {
        //ENROQUE LARGO
        bool torre = false;
        nuevaCasilla = casilla+4;
        pasa = false;
        torre = miTablero->casillasInt[nuevaCasilla] == 4;

        if (torre && miTablero->casillasInt[casilla+2] == 0 && miTablero->casillasInt[casilla+1] == 0 && miTablero->casillasInt[casilla+3] == 0)
        {
            nuevaCasilla = casilla+2;
            miTablero->casillasInt[casilla+4] = 0;
            miTablero->casillasInt[casilla+1] = 4;
            std::cout << "APLICA MOVIMIENTO REY +4 (enroque)"<< std::endl;
            if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                std::cout << "REY MOVIDO"<< std::endl;

                if (testJaque) return true;
            }
        }
    }

    //IZQUIERDA
    pasa = false;
    nuevaCasilla = casilla-1;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa){
        std::cout << "APLICA MOVIMIENTO REY -1"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }

    }

    //DERECHA
    nuevaCasilla = casilla+1;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

    if (pasa){
        //  miTablero->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY +1"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //ATRAS
    nuevaCasilla = casilla-12;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa){
        std::cout << "APLICA MOVIMIENTO REY -12"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //ADELANTE
    nuevaCasilla = casilla+12;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        std::cout << "APLICA MOVIMIENTO REY +12"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //NE
    nuevaCasilla = casilla+13;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        //    TableroMovido->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY +13"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //NO
    nuevaCasilla = casilla+11;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        std::cout << "APLICA MOVIMIENTO REY +11"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //SO
    nuevaCasilla = casilla-13;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY -13"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    //SE
    nuevaCasilla = casilla-11;
    pasa = false;
    pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
    if (pasa)
    {
        //   TableroMovido->fichaMovida = "REY!!!!";
        std::cout << "APLICA MOVIMIENTO REY -11"<< std::endl;
        if (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
        {
            std::cout << "REY MOVIDO"<< std::endl;

            if (testJaque) return true;
        }
    }

    if (testJaque) return false;

}







bool Movimientos::mueveTorre(ModeloTablero* miTablero,const int casilla, bool testJaque)
{
    //mueve a todas las casillas posibles
    //mira si esta ocupada
    int nuevaCasilla = casilla-1;
    bool ocupado = false;
    bool pasa = false;

    while(nuevaCasilla%12 >2)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;

        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;
            }
            else if (ocupado) break;
        }else break;
        nuevaCasilla = nuevaCasilla-1;
    }

    nuevaCasilla = casilla+1;
    pasa = false;
    while(nuevaCasilla%12 <10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;
            }
            else if (ocupado) break;
        }else break;
        nuevaCasilla = nuevaCasilla+1;
    }

    nuevaCasilla = casilla-12;
    pasa = false;
    while(nuevaCasilla/12 > 2)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;
            }
            else if (ocupado) break;
        }else break;

        nuevaCasilla = nuevaCasilla-12;
    }

    nuevaCasilla = casilla+12;
    pasa = false;
    while(nuevaCasilla/12 < 10)
    {
        pasa = miTablero->casillasInt[nuevaCasilla] <= 0;
        if (pasa)
        {
            ocupado = miTablero->casillasInt[nuevaCasilla] != 0;
            if  (aplicaMovimiento(*miTablero, casilla, nuevaCasilla, testJaque))
            {
                if (testJaque) return true;
            }
            else if (ocupado) break;
        }else break;
        nuevaCasilla = nuevaCasilla+12;
    }

    if (testJaque) return false;

}




bool Movimientos::aplicaMovimiento(ModeloTablero &miTablero, int casOrigen, int casDestino, bool testJaque)
{
    int* casillas = miTablero.casillasInt;
    ModeloTablero* TableroMovido = NULL;

    int fichaOrigen = casillas[casOrigen];
    int fichaDestino = casillas[casDestino];

    /*
        std::cout << "casOrigen "<<casOrigen <<std::endl;
        std::cout << "casDestino "<<casDestino <<std::endl;

        std::cout << "fichaOrigen "<<fichaOrigen <<std::endl;
        std::cout << "fichaDestino "<<fichaDestino <<std::endl;

*/

    //   std::cout << "!!!!!!!!!FICHA ORIGEN!!!!!!:" << fichaOrigen << std::endl;

    //     std::cout << "!!!!!!!!!FICHA DESTINO!!!!!!:" << miTablero.casillasInt[casDestino] << std::endl;

    casillas[casOrigen] = 0;
    casillas[casDestino] = fichaOrigen;

    if (evaluaJaque(casillas, miTablero.turnoN))
    {
          std::cout << "!!!!!HA EVALUADO UN JAQUE (DESPUES DE MOVER) POR LO QUE NO AÑADE AL VECTOR!!!" << std::endl;

          casillas[casOrigen] = fichaOrigen;
          casillas[casDestino] = fichaDestino;
         return false;
    }else
    {

        if(!testJaque)
        {


            TableroMovido = new ModeloTablero(miTablero);

            // TableroMovido->alPaso = -1;

            TableroMovido->movimiento[0] = casOrigen;
            TableroMovido->movimiento[1] = casDestino;

             std::cout << "!!!!!!!!fichaOrigen!!!!: " <<fichaOrigen <<std::endl;


            if (fichaOrigen == 1 && (casDestino - casOrigen  == 24 || casOrigen - casDestino == 24))
            {
                TableroMovido->alPaso = casDestino;
                std::cout << "!!!!!!!!!DOBLE SALTO EN IA!!!!!!:" <<TableroMovido->alPaso <<std::endl;
            }

            //   TableroMovido->turnoN = !miTablero.turnoN;

            miTablero.vectorMov.push_back(TableroMovido);


        }else{

            //no hace nada
        }

        casillas[casOrigen] = fichaOrigen;
        casillas[casDestino] = fichaDestino;
        return true;

        // miTablero.numeroHijos++;
    }

    //REVIERTE EL MOVIMIENTO

   return false;

}


/////////////////////////////////////////////////////////////////////////////////////////
//MOVIMIENTOS DE HUMANO QUE HABRA QUE CAMBIAR














