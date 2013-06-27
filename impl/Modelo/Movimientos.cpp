#include "../../headers/Modelo/Movimientos.h"



bool Movimientos::generaMovimientos(ModeloTablero* miTablero)
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


    bool fichamovida = false;

    //CADA VEZ QUE ENCUENTRA UNA FICHA DEVUELVE SUS MOVIMIENTOS Y ANTES DE BUSCAR OTRA SE BORRAN, ASI SE AHORRA MEMORIA

    for (int i = 26; i< 120;i++)
    {
        std::cout << "FOR  DE GENERA MOOVV"<< i << std::endl;
        //  int casilla = (i*12)+y;
        int valorCasilla = miTablero->casillasInt[i];
        std::cout << "VALOR"<< valorCasilla << std::endl;

        if (valorCasilla > 0)
        {
            std::cout << "!!!ENCUENTRA FICHA EN: " <<  i <<std::endl;
            miTablero->jugada[0] = i;
            fichamovida = mueveFicha(miTablero, false, tipoFicha(valorCasilla));






        }



        //     std::cout << "!!!ENCUENTRA FICHA EN: " <<  i << " DE TIPO "<< tipo <<std::endl;

        //    std::cout << "!!!mueve ficha: " <<  i << " DE TIPO " << tipo <<std::endl;

        //    if (testJaque) return false;




        // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
    }


    // std::cout << "!!!!!!!!RETORNO!!!!!!!!   " <<std::endl;
 // std::cout << "!!!!!JAQUE MATE O AHOGADO AL FINAL DE MOVIMIENTOS!!!   " <<std::endl;
        return fichamovida; //JAQUE MATE O AHOGADO

    //  std::cout << "generamov"<< std::endl;
}



bool Movimientos::pruebaJaqueMate(ModeloTablero* miTablero)
{
    // ModeloTablero nuevoTablero;
    // std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!   " << miTablero->turnoN << " JAQUE? "<< testJaque<<std::endl;

    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

  //  miTablero->vectorMov.clear();
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


            miTablero->jugada[0] = i;

            if (mueveFicha(miTablero, true, tipoFicha(miTablero->casillasInt[i])))
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

bool Movimientos::mueveFicha(ModeloTablero* miTablero, bool testJaque, char tipo)
{

    bool fichamovida = false;

    switch (tipo)
    {

    case Rey:
        //ENCUENTRA REY
        //  std::cout << "!!!!!!!!!REY!!!!!!!!   " <<std::endl;

        fichamovida = mueveRey(miTablero, testJaque);

        break;

    case Reina:
        //std::cout << "!!!!!!!!!REINA!!!!!!!!!   " <<std::endl;

        //ENCUENTRA REINA

        fichamovida = mueveReina(miTablero, testJaque);

        //  std::cout << "!!!!!!!!!HA MOVIDO LA REINA!!!!!!!!!!   " <<std::endl;

        break;

    case Torre:
        // std::cout << "!!!!!!!!!TORRE!!!!!!!!!   " <<std::endl;
        //ENCUENTRA TORRE

        fichamovida = mueveTorre(miTablero);

        // std::cout << "!!!!!!!!!HA MOVIDO LA TORRE!!!!!!!!!!   " <<std::endl;

        break;

    case Alfil:
        //std::cout << "!!!!!!!!!ALFIL!!!!!!!!   " testJaque<<std::endl;
        //ENCUENTRA ALFIL

        fichamovida = mueveAlfil(miTablero, testJaque);

        //   std::cout << "!!!!!!!!!HA MOVIDO EL ALFIL!!!!!!!!!!   " <<std::endl;

        break;

    case Caballo:

        //  std::cout << "!!!!!!!!!CABALLO!!!!!!!!!!   " <<std::endl;
        //ENCUENTRA CABALLO
        fichamovida = mueveCaballo(miTablero, testJaque);

        // std::cout << "!!!!!!!!!HA MOVIDO EL CABALLO!!!!!!!!!!   " <<std::endl;

        break;

    case Peon:
        //  std::cout << "!!!!!!!!!!!!!!!!!!PEON!!!!!!!!!!!!!!!!!! "<< std::endl;
        //ENCUENTRA PEON

        fichamovida = muevePeon(miTablero, testJaque);

        //  std::cout << "!!!!!!!!!HA MOVIDO EL PEON!!!!!!!!!!   " <<std::endl;

        break;

    default:
        break;
    }








}


//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?
bool Movimientos::mueveReina(ModeloTablero* miTablero, bool testJaque)
{
    bool torre = mueveTorre(miTablero);
    bool alfil = mueveAlfil(miTablero, testJaque);

    if (testJaque)
    {
        if (torre) return true;
        else if (alfil) return true;
        else return false;

    }

}

bool Movimientos::muevePeon(ModeloTablero* miTablero, bool testJaque)
{
    unsigned char nuevaCasilla;
    int casillaCome;
    int casillaComeSec;
    int salto;
    int filaPeon;
    int filaPromocion;

    unsigned char casilla  = miTablero->jugada[0] ;


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
        unsigned char*  jugada = new unsigned char[2];
        jugada[0] = casilla;
        jugada[1] = nuevaCasilla;
        miTablero->vectorJugadas.push_back(jugada);

        //PROMOCION A REINA
        if (nuevaCasilla/12 == filaPromocion)
        {
            std::cout << "!!!!!!PROMOCION A REINA DEL PEON!!!!!" << std::endl;
            miTablero->casillasInt[casilla] = 5;
        }


        miTablero->casillasInt[casilla] = 1;
    }



    //DOBLE SALTO
    if(casilla/12 == filaPeon && miTablero->casillasInt[salto] == 0)
    {
        unsigned char*  jugada = new unsigned char[2];
        jugada[0] = casilla;
        jugada[1] = nuevaCasilla;
        miTablero->vectorJugadas.push_back(jugada);


    }

    //COME ENEMIGA
    if (miTablero->casillasInt[casillaCome] < 0)
    {

        //PROMOCION A REINA
        if (nuevaCasilla/12 == filaPromocion)
        {
            std::cout << "!!!!!!PROMOCION A REINA DEL PEON!!!!!" << std::endl;
            miTablero->casillasInt[casilla] = char(5);
        }
        unsigned char*  jugada = new unsigned char[2];
        jugada[0] = casilla;
        jugada[1] = nuevaCasilla;
        miTablero->vectorJugadas.push_back(jugada);

        miTablero->casillasInt[casilla] = char(1);


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

        unsigned char*  jugada = new unsigned char[2];
        jugada[0] = casilla;
        jugada[1] = nuevaCasilla;
        miTablero->vectorJugadas.push_back(jugada);

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

            unsigned char*  jugada = new unsigned char[2];
            jugada[0] = casilla;
            jugada[1] = nuevaCasilla;
            miTablero->vectorJugadas.push_back(jugada);

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


            unsigned char*  jugada = new unsigned char[2];
            jugada[0] = casilla;
            jugada[1] = nuevaCasilla;
            miTablero->vectorJugadas.push_back(jugada);

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

bool Movimientos::mueveTorre(ModeloTablero* miTablero)
{
    //mueve a todas las casillas posibles
    //mira si esta ocupada
    recorreCasillas(miTablero, -1);

    recorreCasillas(miTablero, +1);

    recorreCasillas(miTablero, -12);

    recorreCasillas(miTablero, +12);
}

bool Movimientos::mueveAlfil(ModeloTablero* miTablero, bool testJaque)
{
    recorreCasillas(miTablero, -13);

    recorreCasillas(miTablero, -11);

    recorreCasillas(miTablero, +13);

    recorreCasillas(miTablero, +11);
}

bool Movimientos::recorreCasillas(ModeloTablero* miTablero, unsigned char salto)

{
    unsigned char nuevaCasilla = miTablero->jugada[0]+salto;
   // pasa = true;
    while(miTablero->casillasInt[nuevaCasilla] <= 0)
    {

        nuevaCasilla = nuevaCasilla+salto;

        unsigned char*  jugada = new unsigned char[2];
        jugada[0] = miTablero->jugada[0];
        jugada[1] = nuevaCasilla;
        miTablero->vectorJugadas.push_back(jugada);
        if(miTablero->casillasInt[nuevaCasilla] != 0)
        {
            break;
        }
    }
    return true;
}

bool Movimientos::mueveCaballo(ModeloTablero* miTablero, bool testJaque)
{
    unsigned char casilla  = miTablero->jugada[0] ;

    miTablero->jugada[1] = casilla-25;
    nuevoMovimiento(miTablero);


    miTablero->jugada[1] = casilla-23;
    nuevoMovimiento(miTablero);


    miTablero->jugada[1] = casilla+25;
    nuevoMovimiento(miTablero);


    miTablero->jugada[1] = casilla+23;
    nuevoMovimiento(miTablero);


    miTablero->jugada[1] = casilla-10;
    nuevoMovimiento(miTablero);


    miTablero->jugada[1] = casilla-14;
    nuevoMovimiento(miTablero);


    miTablero->jugada[1] = casilla+10;
    nuevoMovimiento(miTablero);


    miTablero->jugada[1] = casilla+14;
    nuevoMovimiento(miTablero);


    if (testJaque) return false;
    // else return true;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero, bool testJaque)
{
    unsigned char casilla  = miTablero->jugada[0] ;

    // std::cout << "MUEVE REY"<< miTablero->turnoN<< std::endl;
   // unsigned char nuevaCasilla;
    //   bool pasa = false;
    char filaRey;

    if (miTablero->turnoN) filaRey = 9;
    else filaRey = 2;

    if (casilla/12 == filaRey)
    {
        //  std::cout << "REY EN FILA: "<< filaRey<< "Y TURNO: "<< miTablero->turnoN<<std::endl;
        //ENROQUE CORTO (DERECHA)
        miTablero->jugada[1]  = casilla + 3;
        if (miTablero->casillasInt[miTablero->jugada[1] ] == 4 && miTablero->casillasInt[casilla+2] == 0 && miTablero->casillasInt[casilla+1] == 0)
        {
            miTablero->casillasInt[miTablero->jugada[1] ] = 0;
            miTablero->casillasInt[casilla+1] = 4;

            miTablero->jugada[1]  = casilla+2;

            nuevoMovimiento(miTablero);


            miTablero->casillasInt[casilla+3] = 4;
            miTablero->casillasInt[casilla+1] = 0;
        }

        //ENROQUE LARGO (IZQUIERDA)
        miTablero->jugada[1]  = casilla-4;

        if (miTablero->casillasInt[miTablero->jugada[1]] == 4 && miTablero->casillasInt[casilla-1] == 0 && miTablero->casillasInt[casilla-2] == 0 && miTablero->casillasInt[casilla-3] == 0)
        {
            miTablero->casillasInt[miTablero->jugada[1]] = 0;
            miTablero->casillasInt[casilla-1] = 4;

            miTablero->jugada[1]  = casilla-2;

              nuevoMovimiento(miTablero);

            miTablero->casillasInt[casilla-4] = 4;
            miTablero->casillasInt[casilla-1] = 0;
        }
    }

    //IZQUIERDA
    miTablero->jugada[1] = casilla-1;
    nuevoMovimiento(miTablero);

    //DERECHA
    miTablero->jugada[1] = casilla+1;
    nuevoMovimiento(miTablero);


    //ATRAS
    miTablero->jugada[1] = casilla-12;
    nuevoMovimiento(miTablero);


    //ADELANTE
    miTablero->jugada[1] = casilla+12;
    nuevoMovimiento(miTablero);


    //NE
    miTablero->jugada[1] = casilla+13;
    nuevoMovimiento(miTablero);

    //NO
    miTablero->jugada[1] = casilla+11;
    nuevoMovimiento(miTablero);

    //SO
    miTablero->jugada[1] = casilla-13;
    nuevoMovimiento(miTablero);


    //SE
    miTablero->jugada[1] = casilla-11;
    nuevoMovimiento(miTablero);

    if (testJaque) return false;
}

ModeloTablero* Movimientos::nuevoMovimiento(ModeloTablero *miTablero)

{
if (miTablero->casillasInt[miTablero->jugada[1]] <= 0)
{
    unsigned char* jugada = new unsigned char[2];
    jugada[0] = miTablero->jugada[0];
    jugada[1] = miTablero->jugada[1];
    miTablero->vectorJugadas.push_back(jugada);
}
}

ModeloTablero* Movimientos::aplicaMovimiento(ModeloTablero &miTablero)
{
    ModeloTablero* TableroMovido = NULL;
    //   std::cout << "!!!!!!!!!FICHA ORIGEN!!!!!!:" << fichaOrigen << std::endl;
    //     std::cout << "!!!!!!!!!FICHA DESTINO!!!!!!:" << miTablero.casillasInt[casDestino] << std::endl;
    // TableroMovido->alPaso = -1;
    int casOrigen = miTablero.jugada[0];
    int casDestino = miTablero.jugada[1];

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

        return NULL;
    }
    else
    {
        TableroMovido = new ModeloTablero(miTablero, casOrigen, casDestino);

        //  TableroMovido->jugada[0] = casOrigen;
        // TableroMovido->jugada[1] = casDestino;



        miTablero.casillasInt[casDestino] = fichaNueva;
        miTablero.casillasInt[casOrigen] = fichavieja;

        if (miTablero.casillasInt[casOrigen] == 1 && (casDestino - casOrigen  == 24 || casOrigen - casDestino == 24))
        {
            TableroMovido->alPaso = casDestino;
            //std::cout << "!!!!!!!!!DOBLE SALTO EN IA!!!!!!:" <<TableroMovido->alPaso <<std::endl;
        }
        //   TableroMovido->turnoN = !miTablero.turnoN;

       // miTablero.vectorMov.push_back(TableroMovido);
        //   std::cout << "!!!!TABLERO AÑADIDO!" << std::endl;

        return TableroMovido;
    }

    miTablero.casillasInt[casDestino] = fichaNueva;
    miTablero.casillasInt[casOrigen] = fichavieja;

    return NULL;

    // miTablero.numeroHijos++;
    //REVIERTE EL MOVIMIENTO
    // return false;
}




