#include "../../headers/Modelo/Movimientos.h"

bool Movimientos::generaMovimientos(ModeloTablero* miTablero)
{
    // ModeloTablero nuevoTablero;
    // std::cout << "!!!!!!!!!!!!!!!!!!GENERA MOVI!!!!!!!!!!!!!!!!!!!   " << miTablero->turnoN << " JAQUE? "<< testJaque<<std::endl;
    
    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS
    
    //HAY QUE ORDENAR LA LISTA
    
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
    
    //   std::cout << "!!!!generaMovimientos "<<std::endl;
    
    for (int y= 1; y<7; y++)
    {
        for (int i = 26; i< 118;i++)
        {
            //  int casilla = (i*12)+y;
            char valorCasilla = miTablero->casillasInt[i];
            // std::cout << "VALOR"<< int(valorCasilla) << std::endl;
            
            if (valorCasilla == y)
            {
                // std::cout << "FOR  DE GENERA MOOVV "<< i<<" FICHA: " << y<<std::endl;
                
                // std::cout << "!!!ENCUENTRA FICHA EN: " <<  i << " CON LA FICHA: "<<int(miTablero->casillasInt[i])<< "DEVERDAD: "<< miTablero->casillasInt[i]<<std::endl;
                // std::cout << "!!!TRADUCIDO: FILA: " <<  ((i/12)-2) + 1 << " Y COLUMNA: " << ((i%12)-2) + 1<< std::endl;
                miTablero->jugada[0] = i;
                bool resultado = mueveFicha(miTablero, tipoFicha(valorCasilla));
                if (fichamovida == false) fichamovida = resultado;
            }
            //     std::cout << "!!!ENCUENTRA FICHA EN: " <<  i << " DE TIPO "<< tipo <<std::endl;
            //    std::cout << "!!!mueve ficha: " <<  i << " DE TIPO " << tipo <<std::endl;
            //    if (testJaque) return false;
            
            // std::cout << "miTablero->casillasInt[(i*8)+y]:" << (i*12)+y<<" "<<miTablero->casillasInt[(i*12)+y]<<std::endl;
        }
        
    }

    //std::sort (miTablero->vectorJugadas.begin(), miTablero->vectorJugadas.end(), myfunction);


    std::cout << "!!!!!!!!!!!!!!JUGADAS BUENAS!: " << miTablero->vectorJugadas.size()<<std::endl;
    std::cout << "!!!!!!!!!!!!!!JUGADAS NEUTRAS!: " << miTablero->vectorJugadasNormales.size()<<std::endl;
    std::cout << "!!!!!!!!!!!!!!JUGADAS MALAS!: " << miTablero->vectorJugadasPeores.size()<<std::endl;



    miTablero->vectorJugadas.reserve( miTablero->vectorJugadasNormales.size() + miTablero->vectorJugadasPeores.size() ); // preallocate memory
    miTablero->vectorJugadas.insert( miTablero->vectorJugadas.end(), miTablero->vectorJugadasNormales.begin(), miTablero->vectorJugadasNormales.end() );
    miTablero->vectorJugadas.insert( miTablero->vectorJugadas.end(), miTablero->vectorJugadasPeores.begin(), miTablero->vectorJugadasPeores.end() );


    // std::cout << "!!!!!!!!!!!!!!JUGADAS FINALES!: " << miTablero->vectorJugadas.size()<<std::endl;






    miTablero->vectorJugadasNormales.clear();

    //  numeroHijos=0;
    miTablero->vectorJugadasPeores.clear();




    //   std::cout << "!!!!FINGENERACION "<<std::endl;

    // std::cout << "!!!!!!!!RETORNO!!!!!!!!   " <<std::endl;
    // std::cout << "!!!!!JAQUE MATE O AHOGADO AL FINAL DE MOVIMIENTOS!!!   " <<std::endl;
    return fichamovida; //JAQUE MATE O AHOGADO

    //  std::cout << "generamov"<< std::endl;
}
/*
bool Movimientos::myfunction (unsigned char* primeraJugada, unsigned char* segundaJugada)
{
    return (segundaJugada[1] < primeraJugada[1]);
}

*/
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
    
    bool movimiento = false;
    generaMovimientos(miTablero);
    
    for (std::vector<unsigned char*>::iterator it = miTablero->vectorJugadas.begin(); it!=miTablero->vectorJugadas.end(); it++)
    {
        
        unsigned char* jugada = *it;
        
        if (!movimiento)
        {
            
            miTablero->jugada[0] = jugada[0];
            miTablero->jugada[1] = jugada[1];
            
            ModeloTablero* tablero = aplicaMovimiento(*miTablero);
            
            if (tablero != NULL)
            {
                //movimiento encontrado
                std::cout << "!!!!!!!!HAY MOVIMIENTO (NO ES JAQUE)!!!!!!!!   " <<std::endl;
                movimiento = true;
                
            }
            delete tablero;
            tablero = NULL;
        }
        delete jugada;
        jugada = NULL;
        
    }
    miTablero->vectorJugadas.clear();
    
    for (int i = 0; i <  miTablero->casillasProtegidas.size(); i++)
    {
        
        // unsigned char* casilla = *it;
        
        delete miTablero->casillasProtegidas.at(i);
        miTablero->casillasProtegidas.at(i) = NULL;
        
    }
    
    miTablero->casillasProtegidas.clear();
    
    if (movimiento)  return false;
    else return true;
    // std::cout << "!!!!!!!!RETORNO!!!!!!!!   " <<std::endl;
    
    // std::cout << "!!!!!JAQUE MATE O AHOGADO AL FINAL DE MOVIMIENTOS!!!   " <<std::endl;
    return true; //JAQUE MATE O AHOGADO
    
    //  std::cout << "generamov"<< std::endl;
}

bool Movimientos::mueveFicha(ModeloTablero* miTablero, char tipo)
{
    
    // bool fichamovida = false;
    
    switch (tipo)
    {
    case Rey:
        //ENCUENTRA REY
        //  std::cout << "!!!!!!!!!REY!!!!!!!!   " <<std::endl;
        
        return mueveRey(miTablero);
        
        break;
        
    case Reina:
        //std::cout << "!!!!!!!!!REINA!!!!!!!!!   " <<std::endl;
        
        //ENCUENTRA REINA
        
        return mueveReina(miTablero);
        
        //  std::cout << "!!!!!!!!!HA MOVIDO LA REINA!!!!!!!!!!   " <<std::endl;
        
        break;
        
    case Torre:
        // std::cout << "!!!!!!!!!TORRE!!!!!!!!!   " <<std::endl;
        //ENCUENTRA TORRE
        
        return mueveTorre(miTablero);
        
        // std::cout << "!!!!!!!!!HA MOVIDO LA TORRE!!!!!!!!!!   " <<std::endl;
        
        break;
        
    case Alfil:
        //std::cout << "!!!!!!!!!ALFIL!!!!!!!!   " testJaque<<std::endl;
        //ENCUENTRA ALFIL
        
        return mueveAlfil(miTablero);
        
        //   std::cout << "!!!!!!!!!HA MOVIDO EL ALFIL!!!!!!!!!!   " <<std::endl;
        
        break;
        
    case Caballo:
        
        //  std::cout << "!!!!!!!!!CABALLO!!!!!!!!!!   " <<std::endl;
        //ENCUENTRA CABALLO
        return mueveCaballo(miTablero);
        
        // std::cout << "!!!!!!!!!HA MOVIDO EL CABALLO!!!!!!!!!!   " <<std::endl;
        
        break;
        
    case Peon:
        //  std::cout << "!!!!!!!!!!!!!!!!!!PEON!!!!!!!!!!!!!!!!!! "<< std::endl;
        //ENCUENTRA PEON
        
        return muevePeon(miTablero);
        
        //  std::cout << "!!!!!!!!!HA MOVIDO EL PEON!!!!!!!!!!   " <<std::endl;
        
        break;
        
    default:
        break;
    }
}

//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?
bool Movimientos::mueveReina(ModeloTablero* miTablero)
{
    // bool reinaMovida = false;

    bool torre = mueveTorre(miTablero);
    bool alfil = mueveAlfil(miTablero);
    
    // if (testJaque)
    //{
    return (torre || alfil);
    // }
    
}

bool Movimientos::muevePeon(ModeloTablero* miTablero)
{
 bool muevePeon = false;
    unsigned char casilla  = miTablero->jugada[0];
    unsigned char nuevaCasilla = casilla+12;
    int casillaCome = casilla+11;
    int casillaComeSec = casilla+13;
    int salto = casilla+24;
    // int filaPeon = 3;
    //int filaPromocion = 9;
    //   std::cout << "!!!!!!!!!!!MIRA EN: "<<nuevaCasilla << std::endl;
    //std::cout << "!!!!!!!!!!!ENCUENTRA: "<<TableroMovido->casillasInt[nuevaCasilla] << std::endl;
    
    //MOVIMIENTO NORMAL
    if(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = nuevaCasilla;
        nuevoMovimiento(miTablero);
        muevePeon = true;
    }
    
    //DOBLE SALTO
    if(casilla/12 == 3 && miTablero->casillasInt[nuevaCasilla] == 0 && miTablero->casillasInt[salto] == 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = salto;
        nuevoMovimiento(miTablero);
        muevePeon = true;

    }
    
    int numProtegidas = 0;
    
    //COME ENEMIGA
    if (miTablero->casillasInt[casillaCome] < 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = casillaCome;
        nuevoMovimiento(miTablero);
        muevePeon = true;

        //miTablero->casillasInt[casilla] = 1;
    }
    else if (miTablero->casillasInt[casillaCome] > 0 && miTablero->casillasInt[casillaCome] != 99)
    {
        //std::cout << "FICHA AMIGA: "<< int(miTablero->jugada[0])<<std::endl;
        unsigned char* protege = new unsigned char[2];
        protege[0] = miTablero->jugada[0];
        protege[1] = miTablero->casillasInt[casillaCome];
        //    miTablero->casillasProtegidas =
        miTablero->casillasProtegidas.push_back(protege);
        numProtegidas++;
        
    }
    
    //COME ENEMIGA 2
    if (miTablero->casillasInt[casillaComeSec] < 0)
    {
        //  std::cout << "NEGRAS COME 2"<< std::endl;
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = casillaComeSec;
        nuevoMovimiento(miTablero);
        muevePeon = true;
        // miTablero->casillasInt[casilla] = 1;
        
    }else if (miTablero->casillasInt[casillaComeSec] > 0 && miTablero->casillasInt[casillaComeSec] != 99)
    {
        unsigned char* protege = new unsigned char[2];
        protege[0] = miTablero->jugada[0];
        protege[1] = miTablero->casillasInt[casillaComeSec];
        //    miTablero->casillasProtegidas =
        miTablero->casillasProtegidas.push_back(protege);
        numProtegidas++;
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
            
            //  miTablero->jugada[0] = casilla;
            miTablero->jugada[1] = casillaCome;
            nuevoMovimiento(miTablero);
            muevePeon = true;

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
            
            //  miTablero->jugada[0] = casilla;
            miTablero->jugada[1] = casillaComeSec;
            nuevoMovimiento(miTablero);
            muevePeon = true;

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }
    }
    
    return muevePeon;

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
    bool izquierda = recorreCasillas(miTablero, -1);
    
    bool derecha =  recorreCasillas(miTablero, +1);
    
    bool abajo =   recorreCasillas(miTablero, -12);
    
    bool arriba =   recorreCasillas(miTablero, +12);

    return (izquierda || derecha || abajo || arriba);
    
}

bool Movimientos::mueveAlfil(ModeloTablero* miTablero)
{    
    bool SO = recorreCasillas(miTablero, -13);
    
    bool SE = recorreCasillas(miTablero, -11);
    
    bool NE  =recorreCasillas(miTablero, +13);
    
    bool NO = recorreCasillas(miTablero, +11);

 return (NE || NO || SE || SO);
}

bool Movimientos::recorreCasillas(ModeloTablero* miTablero, unsigned char salto)
{
    unsigned char nuevaCasilla = miTablero->jugada[0]+salto;
    // pasa = true;

    bool mueveFicha = false;

    while(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        //  std::cout << "AGREGA CASILLA "<< int(nuevaCasilla)<< std::endl;
        miTablero->jugada[1] = nuevaCasilla;
        nuevoMovimiento(miTablero);
        mueveFicha = true;
        nuevaCasilla = nuevaCasilla+salto;
    }
    
    if (miTablero->casillasInt[nuevaCasilla] != 99)
    {
        if(miTablero->casillasInt[nuevaCasilla] < 0)
        {     //encuentra ficha  enemiga
            miTablero->jugada[1] = nuevaCasilla;
            nuevoMovimiento(miTablero);
            mueveFicha = true;
        }
        else if(miTablero->casillasInt[nuevaCasilla] > 0)
        {

            //NO PONER NEGATIVO?? HACER EN LISTA O VECTOR PARA QUE HAYA TAMAÑO??
            //encuentra ficha  amiga
            miTablero->jugada[1] = nuevaCasilla;

            unsigned char* protege = new unsigned char[2];
            protege[0] = miTablero->jugada[0];
            protege[1] = miTablero->casillasInt[nuevaCasilla];
            //    miTablero->casillasProtegidas =
            miTablero->casillasProtegidas.push_back(protege);
        }
    }
    // miTablero->numCasillasProtegidas++;
    return mueveFicha;
}

bool Movimientos::mueveCaballo(ModeloTablero* miTablero)
{
    unsigned char casilla  = miTablero->jugada[0];
    
    bool mueveCaballo = false;

    char movimientos[8] = {-25, 25, -23, 23, -14, 14, -10, 10};
    
    for (int i = 0; i < 8; i++)
    {
        if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
        {
            if (miTablero->casillasInt[casilla+movimientos[i]] <= 0)
            {
                miTablero->jugada[1] = casilla+movimientos[i];
                nuevoMovimiento(miTablero);
                mueveCaballo = true;
            }else if (miTablero->casillasInt[casilla+movimientos[i]] > 0)
            {
                unsigned char* protege = new unsigned char[2];
                protege[0] = miTablero->jugada[0];
                protege[1] = miTablero->casillasInt[casilla+movimientos[i]];
                //    miTablero->casillasProtegidas =
                miTablero->casillasProtegidas.push_back(protege);

            }
        }
    }
    
   return mueveCaballo;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero)
{  
    unsigned char casilla  = miTablero->jugada[0];
    
    // int Dif = destino - casilla;
    // std::cout << "MUEVE REY"<< miTablero->turnoN<< std::endl;
    // unsigned char nuevaCasilla;blero->casillasProtegidas[miTablero->casill
    //   bool pasa = false;
    //  char filaRey = 2;

    bool mueveRey = false;

    //ENROQUE
    if (casilla/12 == 2)
    {
        unsigned char destino  = casilla + 2;
        
        if(destino/12 == 2 && miTablero->casillasInt[destino-1] == 0 && miTablero->casillasInt[destino] == 0 && (miTablero->casillasInt[destino+1] == Torre
                                                                                                                 || (miTablero->casillasInt[destino+2] == Torre
                                                                                                                     && miTablero->casillasInt[destino+1] == 0)))
        {
            miTablero->jugada[1] = destino;
            nuevoMovimiento(miTablero);
            mueveRey = true;
        }

        destino  = casilla - 2;
        if(destino/12 == 2 && miTablero->casillasInt[destino+1] == 0 && miTablero->casillasInt[destino] == 0 && (miTablero->casillasInt[destino-1] == Torre
                                                                                                                 || (miTablero->casillasInt[destino-2] == Torre
                                                                                                                     && miTablero->casillasInt[destino-1] == 0)))
        {
            miTablero->jugada[1] = destino;
            nuevoMovimiento(miTablero);
            mueveRey = true;

        }

    }
    
    char movimientos[8] = {-1, 1, -12, 12, -13, 13, -11, 11};
    
    for (int i = 0; i < 8; i++)
    {
        if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
        {
            if (miTablero->casillasInt[casilla+movimientos[i]] <= 0)
            {
                miTablero->jugada[1] = casilla+movimientos[i];
                nuevoMovimiento(miTablero);
                mueveRey = true;
            }else if (miTablero->casillasInt[casilla+movimientos[i]] > 0)
            {
                unsigned char* protege = new unsigned char[2];
                protege[0] = miTablero->jugada[0];
                protege[1] = miTablero->casillasInt[casilla+movimientos[i]];
                //    miTablero->casillasProtegidas =
                miTablero->casillasProtegidas.push_back(protege);

                //miTablero->casillasProtegidas[miTablero->casillasInt[miTablero->jugada[0]]][miTablero->casillasInt[casilla+movimientos[i]]] = miTablero->casillasInt[casilla+movimientos[i]];

            }
        }
    }
    return mueveRey;
}

void  Movimientos::nuevoMovimiento(ModeloTablero *miTablero)
{

    // miTablero->vectorJugadas.sort();

    if (miTablero->casillasInt[miTablero->jugada[0]] == 99 || miTablero->casillasInt[miTablero->jugada[1]] == 99  ){
        std::cout << "VA A AGREGAR UN MOVIMIENTO CON ALGUNA CASILLA EN 99, OBVIAMENTE NO DEBERIA, ORIGEN: "<<int(miTablero->jugada[0])<<"  DESTINO: "<< int(miTablero->jugada[1])<<std::endl;


        std::cout << "VA "<< int(miTablero->casillasInt[miTablero->jugada[0]])  <<" / "<< int(miTablero->casillasInt[miTablero->jugada[0]]) <<std::endl;
    }
    unsigned char* jugada = new unsigned char[2];
    jugada[0] = miTablero->jugada[0];
    jugada[1] = miTablero->jugada[1];

    int valorAtaque = miTablero->casillasInt[miTablero->jugada[0]] + miTablero->casillasInt[miTablero->jugada[1]];

    //cuanto menor sea el valor, mejor
    if (miTablero->casillasInt[jugada[1]] != 0 && valorAtaque != 0)
    {
        // std::cout << "!!!!!!!!!!!!!valorAtaque!: " << valorAtaque<<std::endl;
        // if (valorAtaque > 5)  std::cout << "!!!!!!!HAY UN PROBLEMA!: "<<int(miTablero->casillasInt[jugada[0]]) << " / "<<int(miTablero->casillasInt[jugada[1]])<< " / "<< int(jugada[0]) << " / "<< int(jugada[1]) <<std::endl;

        if (valorAtaque < 0){

            miTablero->vectorJugadas.push_back(jugada);
            std::cout << "!!!!!!JUGAA BUENA!: "<<int(miTablero->casillasInt[jugada[0]]) << " / "<<int(miTablero->casillasInt[jugada[1]])<< " / "<< int(jugada[0]) << " / "<< int(jugada[1]) <<std::endl;


        }

        else if (valorAtaque > 0) {
            miTablero->vectorJugadasPeores.push_back(jugada);
            std::cout << "!!!!!!JUGAA MALA!: "<<int(miTablero->casillasInt[jugada[0]]) << " / "<<int(miTablero->casillasInt[jugada[1]])<< " / "<< int(jugada[0]) << " / "<< int(jugada[1]) <<std::endl;

        }
    }else miTablero->vectorJugadasNormales.push_back(jugada);
    
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
    
    // std::cout << "!!!!APLICAMOVIMIE11111!" << std::endl;
    
    
    //  std::cout << "aplicamoviviqqqq " <<std::endl;
    TableroMovido = new ModeloTablero(miTablero, casOrigen, casDestino);
    // std::cout << "aplicamoviviqqqqsdsdsdscsdsd " <<std::endl;
    //  TableroMovido->jugada[0] = casOrigen;
    // TableroMovido->jugada[1] = casDestino;
    
    // std::cout << "!!!!APLICAMOVIMIENTTTTT!!" << std::endl;
    
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
    
    //std::cout << "!!!!return TableroMovido;!!" << std::endl;
    
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
