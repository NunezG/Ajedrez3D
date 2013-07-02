#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo()
    //jugadaAutorizada(false)
  // ,nombreBlancas("Jugador 1")
  //, nombreNegras("Jugador 2")
  //,  jugadores(NULL)
{   
    //mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");
    tableroModelo = new ModeloTablero();
    jugadaElegida[0] = 0;
    jugadaElegida[1] = 0;
}

Modelo::~Modelo()
{
}

Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}

void Modelo::agregaJugada(int inicio, int fin)
{
    tableroModelo->jugada[0] = inicio;
    tableroModelo->jugada[1] = fin;
}

//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int Modelo::autorizaCasilla(tipoFicha tipo)
{   
   // int Dif = tableroModelo->jugada[1] - tableroModelo->jugada[0] ;
    //      filaNueva - filaSel;
    //int colDif = colNueva - colSel;
    //std::cout << "!!!!!!!!!!!AUTORIZA!!!!!!!!!!!!!!"<< std::endl;
   // std::cout << "!!CASILLA SELECCIONADA!!!!!!!!!!" << tableroModelo->jugada[0] << std::endl;
    //std::cout << "!!!CASILLA SOBREVOLADA!!!!!!!!" << tableroModelo->jugada[1] << std::endl;
    //std::cout << "!!!FICHA EN LA CASILLA SOBREVOLADA!!!!!!!!" << tableroModelo->casillasInt[tableroModelo->jugada[1]] << std::endl;

    if (tableroModelo->turnoN)
    {
        tableroModelo->jugada[0] = 143-tableroModelo->jugada[0];
        tableroModelo->jugada[1] = 143-tableroModelo->jugada[1];

    }

    //MIRA SI ES COMESTIBLE (FICHA ENEMIGA)

    if(tableroModelo->casillasInt[tableroModelo->jugada[1]] <= 0)
    {

        switch (tipo)
        {
        case Rey: //REY SELECCIONADO

            return Autorizaciones::autorizaRey(tableroModelo);
            break;

        case Reina: //REINA SELECCIONADO

            return Autorizaciones::autorizaReina(tableroModelo);
            break;

        case Alfil: //ALFIL SELECCIONADO

            return Autorizaciones::autorizaAlfil(tableroModelo);
            break;

        case Torre: //TORRE SELECCIONADA

            return Autorizaciones::autorizaTorre(tableroModelo);
            break;

        case Caballo: //CABALLO SELECCIONADO

            return Autorizaciones::autorizaCaballo(tableroModelo);
            break;

        case Peon: //PEON SELECCIONADO

            return Autorizaciones::autorizaPeon(tableroModelo);
            break;

        default:
            return 0;
            break;
        }
       // if (tableroModelo->evaluaJaque())
      //  {  //JAQUE AL REY


      //  }
    }
    else return 0;
}

int Modelo::mueveTablero()
{
    std::cout << "jugadaElegida[0]  " << int(jugadaElegida[0]) <<std::endl;
    std::cout << "jugadaElegida[1]  " << int(jugadaElegida[1]) <<std::endl;

    tableroModelo->jugada[0] = jugadaElegida[0];
    tableroModelo->jugada[1] = jugadaElegida[1];

    tableroModelo->cambiaTurno();

    //tableroModelo->jugada[0] = 143-jugadaElegida[0];
    //tableroModelo->jugada[1] = 143-jugadaElegida[1];

    for(int i=0; i<12;i++)
    {
        std::cout << int(tableroModelo->casillasInt [(i*12)])<<"    "  << int(tableroModelo->casillasInt [(i*12)+1])<<"    " << int(tableroModelo->casillasInt [(i*12)+2])<<"    "<<int(tableroModelo->casillasInt [(i*12)+3])<<"    "<<int(tableroModelo->casillasInt [(i*12)+4])<<"    "<<int(tableroModelo->casillasInt [(i*12)+5])<<"    "<<int(tableroModelo->casillasInt [(i*12)+6])<<"    "<<int(tableroModelo->casillasInt [(i*12)+7]) <<"    " <<int(tableroModelo->casillasInt [(i*12)+8])<<"    " << int(tableroModelo->casillasInt [(i*12)+9])<<"    " << int(tableroModelo->casillasInt [(i*12)+10])<<"    " << int(tableroModelo->casillasInt [(i*12)+11])<<"    " << std::endl;
    }
    std::cout << "traducido AL CAMBIAR DE TURNO" << std::endl;

    std::cout << "!!!!!!pasa111! " << std::endl;

    // tablero->cambiaTurno();
    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);
  //  ModeloTablero* turnoSiguiente = new ModeloTablero(*modelo->tableroModelo);
    bool Jaque = false;

    //   if (turnoNegras)tablero = Calculos::normalizaTablero(tablero);
    Jaque = tableroModelo->evaluaJaque();  //JAQUE AL REY

    std::cout << "!!!!!!pasa! " << std::endl;

    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Movimientos::pruebaJaqueMate(tableroModelo))
    {
      //  delete turnoSiguiente;
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS PARA EL TURNO SIGUIENTE(JAQUE MATE O AHOGADO)!!!: " << std::endl;

        //SE EVALUA EL JAQUE Y SI EL REY NO ESTA EN JAQUE ES QUE ES AHOGADO
        //EVALUA JAQUE
        if (Jaque)
        {            //JAQUE MATE
            return 3;
            std::cout << "!!!!!!!!!DEVUELVE JAQUE MATE! " << std::endl;
        }
        else
        { //NO HAY JAQUE, AHOGADO, RESULTADO EN TABLAS
            std::cout << "!!!!!!!!!DEVUELVE REY AHOGADO! " << std::endl;
            return 4;
        }
    }
    else
    {
      //  delete turnoSiguiente;
        if (Jaque)
        {//Jaque asecas
            std::cout << "!!!!!!!!!DEVUELVE JAQUE! " << std::endl;
            return 2;
        }
        //Mueve
            return 1;
    }
    //FINDE PARTIDA
    return 0;
}
