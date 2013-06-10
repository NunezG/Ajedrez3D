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



int Modelo::agregaJugada(int inicio, int fin)
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

    std::cout << "!!!!!!!!!!!AUTORIZA!!!!!!!!!!!!!!"<< std::endl;

    std::cout << "!!CASILLA SELECCIONADA!!!!!!!!!!" << tableroModelo->jugada[0] << std::endl;
    std::cout << "!!!CASILLA SOBREVOLADA!!!!!!!!" << tableroModelo->jugada[1] << std::endl;


    std::cout << "!!!FICHA EN LA CASILLA SOBREVOLADA!!!!!!!!" << tableroModelo->casillasInt[tableroModelo->jugada[1]] << std::endl;

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
    }else return 0;


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
    {
        std::cout << "NO HAY TABLEROS EN EL VECTOR POR LO QUE ES UN JAQUE MATE O UN AHOGADO, HABRA QUE DIFERENCIAR"<< std::endl;
        return false;

    }
    std::cout << "retorno"<< std::endl;


    return true;
}





int* Modelo::mueveTablero()
{
    tableroModelo->casillasInt[tableroModelo->jugada[1]]= tableroModelo->casillasInt[tableroModelo->jugada[0]];
    tableroModelo->casillasInt[tableroModelo->jugada[0]] = 0;
}


