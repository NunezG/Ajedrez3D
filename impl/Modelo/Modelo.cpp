#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo():
    jugadaAutorizada(false)

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

int Modelo::autoriza(tipoFicha tipo)
{
    int Dif = tableroModelo->jugada[1] - tableroModelo->jugada[0] ;
    //      filaNueva - filaSel;
    //int colDif = colNueva - colSel;

    std::cout << "!!!!!!!!!!!AUTORIZA!!!!!!!!!!!!!!"<< std::endl;

    std::cout << "!!CASILLA SELECCIONADA!!!!!!!!!!" << tableroModelo->jugada[0] << std::endl;
    std::cout << "!!!CASILLA SOBREVOLADA!!!!!!!!" << tableroModelo->jugada[1] << std::endl;


    std::cout << "!!!FICHA EN LA CASILLA SOBREVOLADA!!!!!!!!" << tableroModelo->casillasInt[tableroModelo->jugada[1]] << std::endl;


    //int fichaSobrevolada = tablero->casillasInt[24 + (filaNueva*12)+colNueva+2];
    //  std::cout << "!!!!!!!!!!!fichaSOBREVOLADA!!!!!!!!!!!!!!" << 24 + (filaNueva*12)+colNueva+2 << std::endl;

    // std::cout << "!!!!!!!!!!!ficha!!!!!!!!!!!!!!" << fichaSobrevolada << std::endl;

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
    // if (turnoNegas)normalizaTablero(tablero);
}

int Modelo::agregaJugada(int inicio, int fin)
{



    tableroModelo->jugada[0] = inicio;
    tableroModelo->jugada[1] = fin;


}


//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int Modelo::autorizaCasilla(tipoFicha tipo)
{   
    //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
    int autorizado= 0;

    // tablero->casillasInt = tablero->traduceTablero();
    return autoriza(tipo);

    //  if (turnoNegras)tablero = Autorizaciones::normalizaTablero(tablero);
   // std::cout << "autorizado en autorizacasilla: "<<autorizado << std::endl;

    //if(autorizado)
   // {
        //EVALUA EL JAQUE CON LA FICHA YA MOVIDA

        //si esta ocupado y no es comestible

      //  ModeloTablero* tableroMovido = new ModeloTablero(*tableroModelo);

        //if(tableroModelo->turnoN) Autorizaciones::normalizaTablero(tableroModelo->casillasInt);
        // else return 0;

        std::cout << "evalua jaque" << std::endl;

        //Autorizaciones::normalizaTablero(tablero);
        // if (turnoNegras)tableroInt = Autorizaciones::normalizaTablero(tableroInt);

        std::cout << "evalua " << std::endl;

     //   int fichaInicial =  tableroModelo->casillasInt[tableroModelo->jugada[0]];
      //  int fichaFinal = tableroModelo->casillasInt[tableroModelo->jugada[1]];

        //PRIMERO SE EFECTUA EL MOVIMIENTO PROPUESTO
/*
        tableroModelo->turnoN = tableroModelo->turnoN;

        tableroModelo->casillasInt[tableroModelo->jugada[1]]= fichaInicial;
        tableroModelo->casillasInt[tableroModelo->jugada[0]] = 0;

        //EVALUA JAQUE
        if (!tableroModelo->evaluaJaque())
        {
            // tablero->getNodoCasillaSobrevolada()->seleccionada = true;
            //ILUMINA LA CASILLA

            delete tableroModelo;
            std::cout << "ES COMESTIBLE" << std::endl;
            return 1;
        }else
        {
            std::cout << "JAQUE AL REY" << std::endl;

             delete tableroModelo;
            return 3;
        }
        */

      //  return 1;
  //  }
    std::cout << "sale de autorizado" << std::endl;
}

bool Modelo::construyeArbol()
{
    std::cout << "CONST ARBOL: "<< tableroModelo->nodoInicial<< std::endl;
    std::cout << "ORIGEN ANTES: "<< tableroModelo->jugada[0]<< std::endl;
    std::cout << "DEST ANTES: "<< tableroModelo->jugada[1]<< std::endl;

    int resultado = ArbolBusqueda::alphaBeta(tableroModelo,-70000, 70000, 3);

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

    }else
    {
        //jugadaAutorizada = true;

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





int* Modelo::mueveTablero()
{

    //  int* tableroTraducido = tablero;

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );

    // int posFinal = 24+(filaNueva*12) + colNueva+2;

    //   int posInicial = 24+(filaSel*12) + colSel+2;


    tableroModelo->casillasInt[tableroModelo->jugada[1]]= tableroModelo->casillasInt[tableroModelo->jugada[0]];
    tableroModelo->casillasInt[tableroModelo->jugada[0]] = 0;

    //  return tableroTraducido;
}


