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

    //for(int i=0; i<12;i++)
    //  {
    //    std::cout << int(miTablero->casillasInt[(i*12)])<<"    "  << int(miTablero->casillasInt[(i*12)+1])<<"    " << int(miTablero->casillasInt[(i*12)+2])<<"    "<<int(miTablero->casillasInt[(i*12)+3])<<"    "<<int(miTablero->casillasInt[(i*12)+4])<<"    "<<int(miTablero->casillasInt[(i*12)+5])<<"    "<<int(miTablero->casillasInt[(i*12)+6])<<"    "<<int(miTablero->casillasInt[(i*12)+7]) <<"    " <<int(miTablero->casillasInt[(i*12)+8])<<"    " << int(miTablero->casillasInt[(i*12)+9])<<"    " << int(miTablero->casillasInt[(i*12)+10])<<"    " << int(miTablero->casillasInt[(i*12)+11])<<"    " << std::endl;
    // }
    //  std::cout << "TABLERO EN MOVVII" << std::endl;



    bool fichamovida = false;

    //CADA VEZ QUE ENCUENTRA UNA FICHA DEVUELVE SUS MOVIMIENTOS Y ANTES DE BUSCAR OTRA SE BORRAN, ASI SE AHORRA MEMORIA

    for (int i = 26; i< 118;i++)
    {
        //std::cout << "FOR  DE GENERA MOOVV "<< i << std::endl;
        //  int casilla = (i*12)+y;
        char valorCasilla = miTablero->casillasInt[i];
        // std::cout << "VALOR"<< int(valorCasilla) << std::endl;

        if (valorCasilla != 99 && miTablero->casillasInt[i] > 0)
        {
            // std::cout << "!!!ENCUENTRA FICHA EN: " <<  i << " CON LA FICHA: "<<int(miTablero->casillasInt[i])<< "DEVERDAD: "<< miTablero->casillasInt[i]<<std::endl;
            // std::cout << "!!!TRADUCIDO: FILA: " <<  ((i/12)-2) + 1 << " Y COLUMNA: " << ((i%12)-2) + 1<< std::endl;
            miTablero->jugada[0] = i;
            fichamovida = mueveFicha(miTablero, tipoFicha(valorCasilla));
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
    std::cout << "!!!!!!PRUEBA JAQUE! " << std::endl;

    generaMovimientos(miTablero);
    for (std::vector<unsigned char*>::iterator it = miTablero->vectorJugadas.begin(); it!=miTablero->vectorJugadas.end(); it++)
    {

        unsigned char* jugada = *it;

        miTablero->jugada[0] = jugada[0];
        miTablero->jugada[1] = jugada[1];

        ModeloTablero* tablero = aplicaMovimiento(*miTablero);

        if (tablero != NULL)
        {
            //movimiento encontrado
            std::cout << "!!!!!!!!HAY MOVIMIENTO (NO ES JAQUE)!!!!!!!!   " <<std::endl;

            delete tablero;
            return false;

        }

    }


    // std::cout << "!!!!!!!!RETORNO!!!!!!!!   " <<std::endl;

    // std::cout << "!!!!!JAQUE MATE O AHOGADO AL FINAL DE MOVIMIENTOS!!!   " <<std::endl;
    return true; //JAQUE MATE O AHOGADO

    //  std::cout << "generamov"<< std::endl;
}

bool Movimientos::mueveFicha(ModeloTablero* miTablero, char tipo)
{

    bool fichamovida = false;

    switch (tipo)
    {
    case Rey:
        //ENCUENTRA REY
        //  std::cout << "!!!!!!!!!REY!!!!!!!!   " <<std::endl;

        fichamovida = mueveRey(miTablero);

        break;

    case Reina:
        //std::cout << "!!!!!!!!!REINA!!!!!!!!!   " <<std::endl;

        //ENCUENTRA REINA

        fichamovida = mueveReina(miTablero);

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

        fichamovida = mueveAlfil(miTablero);

        //   std::cout << "!!!!!!!!!HA MOVIDO EL ALFIL!!!!!!!!!!   " <<std::endl;

        break;

    case Caballo:

        //  std::cout << "!!!!!!!!!CABALLO!!!!!!!!!!   " <<std::endl;
        //ENCUENTRA CABALLO
        fichamovida = mueveCaballo(miTablero);

        // std::cout << "!!!!!!!!!HA MOVIDO EL CABALLO!!!!!!!!!!   " <<std::endl;

        break;

    case Peon:
        //  std::cout << "!!!!!!!!!!!!!!!!!!PEON!!!!!!!!!!!!!!!!!! "<< std::endl;
        //ENCUENTRA PEON

        fichamovida = muevePeon(miTablero);

        //  std::cout << "!!!!!!!!!HA MOVIDO EL PEON!!!!!!!!!!   " <<std::endl;

        break;

    default:
        break;
    }
}

//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?
bool Movimientos::mueveReina(ModeloTablero* miTablero)
{
    bool torre = mueveTorre(miTablero);
    bool alfil = mueveAlfil(miTablero);

    // if (testJaque)
    //{
    // if (torre) return true;
    //  else if (alfil) return true;
    //  else return false;

    // }

}

bool Movimientos::muevePeon(ModeloTablero* miTablero)
{
    unsigned char casilla  = miTablero->jugada[0];
    unsigned char nuevaCasilla = casilla+12;
    int casillaCome = casilla+11;
    int casillaComeSec = casilla+13;
    int salto = casilla+24;
    int filaPeon = 3;
    //int filaPromocion = 9;
    //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
    //std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;

    //MOVIMIENTO NORMAL
    if(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = nuevaCasilla;
        nuevoMovimiento(miTablero);
    }

    //DOBLE SALTO
    if(casilla/12 == filaPeon && miTablero->casillasInt[salto] == 0)
    {
        miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = salto;
        nuevoMovimiento(miTablero);
    }

    //COME ENEMIGA
    if (miTablero->casillasInt[casillaCome] < 0)
    {
        miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = casillaCome;
        nuevoMovimiento(miTablero);
        //miTablero->casillasInt[casilla] = 1;
    }

    //COME ENEMIGA 2
    if (miTablero->casillasInt[casillaComeSec] < 0)
    {
        //  std::cout << "NEGRAS COME 2"<< std::endl;
        miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = casillaComeSec;
        nuevoMovimiento(miTablero);
        // miTablero->casillasInt[casilla] = 1;

    }
    //COME AL PASO PEON ENEMIGO (DERECHA)
    if(miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaCome] == 0)
    {
        if (miTablero->alPaso == casillaCome-12
                && casilla == casillaCome-11)
        {
            //    std::cout << "COME LA FICHA DE LA DERECHA AL PASO"<< std::endl;
            // fichaAlPaso = miTablero->casillasInt[miTablero->alPaso]; //ficha enemiga, supuestamente negativa
            //  std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (posicion) : " <<miTablero->alPaso<< std::endl;
            // std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (siempre tiene que ser 1): " <<fichaAlPaso<< std::endl;

            miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;

            miTablero->jugada[0] = casilla;
            miTablero->jugada[1] = casillaCome;
            nuevoMovimiento(miTablero);

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }
    }

    //COME AL PASO PEON ENEMIGO (IZQUIERDA)
    if(miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaComeSec] == 0)
    {
        if (miTablero->alPaso == casillaComeSec-12
                && casilla == casillaComeSec-13)
        {
            //    std::cout << "COME LA FICHA DE LA DERECHA AL PASO"<< std::endl;
            // fichaAlPaso = miTablero->casillasInt[miTablero->alPaso]; //ficha enemiga, supuestamente negativa
            //  std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (posicion) : " <<miTablero->alPaso<< std::endl;
            // std::cout << "!!!!!!!!!COME LA FICHA QUE ESTA AL PASO (siempre tiene que ser 1): " <<fichaAlPaso<< std::endl;

            miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;

            miTablero->jugada[0] = casilla;
            miTablero->jugada[1] = casillaComeSec;
            nuevoMovimiento(miTablero);

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }
    }

    // if (testJaque) return false;
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

bool Movimientos::mueveAlfil(ModeloTablero* miTablero)
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
     //  std::cout << "AGREGA CASILLA "<< int(nuevaCasilla)<< std::endl;

        miTablero->jugada[1] = nuevaCasilla;
        nuevoMovimiento(miTablero);
        if(miTablero->casillasInt[nuevaCasilla] != 0)
        {
            break;
        }
        nuevaCasilla = nuevaCasilla+salto;

    }
    return true;
}

bool Movimientos::mueveCaballo(ModeloTablero* miTablero)
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


    // else return true;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero)
{
    unsigned char casilla  = miTablero->jugada[0] ;

    // std::cout << "MUEVE REY"<< miTablero->turnoN<< std::endl;
    // unsigned char nuevaCasilla;
    //   bool pasa = false;
    char filaRey = 2;

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

}

ModeloTablero* Movimientos::nuevoMovimiento(ModeloTablero *miTablero)
{
    if (miTablero->casillasInt[miTablero->jugada[1]] <= 0)
    {
        // std::cout << "AGREGADO "<< int(miTablero->jugada[0])<<" /  "<<int(miTablero->jugada[1])<< std::endl;

        unsigned char* jugada = new unsigned char[2];
        jugada[0] = miTablero->jugada[0];
        jugada[1] = miTablero->jugada[1];
        miTablero->vectorJugadas.push_back(jugada);
    }
}

ModeloTablero* Movimientos::aplicaMovimiento(ModeloTablero &miTablero)
{
    // std::cout << "aplicamovivi " <<std::endl;

    ModeloTablero* TableroMovido = NULL;
    //   std::cout << "!!!!!!!!!FICHA ORIGEN!!!!!!:" << fichaOrigen << std::endl;
    //     std::cout << "!!!!!!!!!FICHA DESTINO!!!!!!:" << miTablero.casillasInt[casDestino] << std::endl;
    // TableroMovido->alPaso = -1;
    int casOrigen = miTablero.jugada[0];
    int casDestino = miTablero.jugada[1];

    // std::cout << "!!!casOrigen: FILA: " <<  ((casOrigen/12)-2) + 1 << " Y COLUMNA: " << ((casOrigen%12)-2) + 1<< std::endl;
    // std::cout << "!!!casDestino: FILA: " miTablero<<  ((casDestino/12)-2) + 1 << " Y COLUMNA: " << ((casDestino%12)-2) + 1<< std::endl;
    // std::cout << "aplicamovivi 1" <<std::endl;

    //COME AL PASO
   // if (miTablero.casillasInt[casOrigen] == 1 && miTablero.alPaso == casDestino-12)
   // {
   //     miTablero.casillasInt[miTablero.alPaso] = 0;
  //  }

 // int fichavieja = miTablero.casillasInt[casOrigen];
  //  int fichaNueva = miTablero.casillasInt[casDestino];
    // std::cout << "aplicamovivi 2" <<std::endl;

    //APLICA EL MOVIMIENTO
  //  miTablero.casillasInt[casDestino] = fichavieja;
   // miTablero.casillasInt[casOrigen] = 0;
    // std::cout << "aplicamovivi 3" <<std::endl;
    //    std::cout << "casOrigen "<<casOrigen <<std::endl;
    //  std::cout << "casDestino "<<casDestino <<std::endl;
    //std::cout << "fichaOrigen "<<fichaOrigen <<std::endl;
    // std::cout << "fichaDestino "<<fichaDestino <<std::endl;
    //  TableroMovido->turnoN = !TableroMovido->turnoN;

    //  std::cout << "!!!!APLICAMOVIMIENTTTTT!!" << std::endl;


        std::cout << "aplicamoviviqqqq " <<std::endl;
        TableroMovido = new ModeloTablero(miTablero, casOrigen, casDestino);
        std::cout << "aplicamoviviqqqqsdsdsdscsdsd " <<std::endl;
        //  TableroMovido->jugada[0] = casOrigen;
        // TableroMovido->jugada[1] = casDestino;


       if (TableroMovido->turnoN == miTablero.turnoN)
       {
            //std::cout << "!!!!!HA EVALUADO UN JAQUE EN EL ARBOL (DESPUES DE MOVER) !!!" << std::endl;
            delete TableroMovido;
            // miTablero.casillasInt[casDestino] = fichaNueva;
            //miTablero.casillasInt[casOrigen] = fichavieja;
            return NULL;


       }

        //miTablero.casillasInt[casDestino] = fichaNueva;
        //  std::cout << "aplicamoviviqqseeerereqq " <<std::endl;
        //miTablero.casillasInt[casOrigen] = fichavieja;
        // std::cout << "aplicamovivisfsfse " <<std::endl;


        //   TableroMovido->turnoN = !miTablero.turnoN;
        // miTablero.vectorMov.push_back(TableroMovido);
        //   std::cout << "!!!!TABLERO AÑADIDO!" << std::endl;
        //return TableroMovido;


    //DESHACE EL MOVIMIENTO
   // if (miTablero.alPaso != -1 && miTablero.casillasInt[miTablero.alPaso] == 0)
   // {
     //   miTablero.casillasInt[miTablero.alPaso] == 1;

   // }
 //   miTablero.casillasInt[casDestino] = fichaNueva;
 //   miTablero.casillasInt[casOrigen] = fichavieja;

    return TableroMovido;
    // miTablero.numeroHijos++;
    //REVIERTE EL MOVIMIENTO
    // return false;
}
