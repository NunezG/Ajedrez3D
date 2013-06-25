#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo()
    //jugadaAutorizada(false)
  // ,nombreBlancas("Jugador 1")
  //, nombreNegras("Jugador 2")
  //,  jugadores(NULL)
{   
    //mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");
    tableroModelo = new ModeloTablero();
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
    }
    else return 0;
}

bool Modelo::construyeArbol()
{
    std::cout << "CONST ARBOL: "<< tableroModelo->nodoInicial<< std::endl;
    std::cout << "ORIGEN ANTES: "<< tableroModelo->jugada[0]<< std::endl;
    std::cout << "DEST ANTES: "<< tableroModelo->jugada[1]<< std::endl;

    int resultado = ArbolBusqueda::alphaBeta(tableroModelo,-70000, 70000, 5);

    std::cout << "FIN CONST ARBOL"<< std::endl;
    std::cout << "ORIGEN DESPUES DE ALFABETA!!!!: "<< tableroModelo->jugada[0]<< std::endl;
    std::cout << "DEST DE ALFABETA!!!!: "<< tableroModelo->jugada[1]<< std::endl;
    std::cout << "RESULTADO DE ALFABETA ANTES: "<< resultado<< std::endl;

    // resultado = resultado;

    std::cout << "RESULTADO DE ALFABETA DESPUES: "<< resultado<< std::endl;
    std::cout << "NUMERO NODOS TABLERO INICIAL: "<< tableroModelo->vectorMov.size()<< std::endl;

    if (tableroModelo->jugada[0] == -1)
    {//SIN RESULTADO
        std::cout << "NO HAY TABLEROS EN EL VECTOR POR LO QUE ES UN JAQUE MATE O UN AHOGADO, HABRA QUE DIFERENCIAR"<< std::endl;
        return false;
    }
    return true;
}

int Modelo::mueveTablero()
{

    tableroModelo->cambiaTurno();



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
