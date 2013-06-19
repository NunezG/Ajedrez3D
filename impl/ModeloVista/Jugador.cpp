#include "../../headers/ModeloVista/Jugador.h"

Jugador::Jugador(EscenaAjedrez* miEscena, Modelo* modelo) :
    //jugadorNegras(false),
    nombre(""),
    // miTablero(0)
    //tableroModelo(modeloTablero)
    escena(miEscena)
  //, tablero(miEscena->tablero)
  , modelo(modelo)
  //esperaEleccion(false)
{
    // tablero = escena->tablero;

}

Jugador::~Jugador()
{
}


bool Jugador::casillaSobrevolada(const std::string nombreCasilla)
{
    //  std::cout << "auto1: " << nombreCasilla<< std::endl;
    Casilla* casillaSobrevolada = static_cast<Casilla*>(escena->getTablero()->getHijo(nombreCasilla));
    Casilla* casillaSobreAnterior = escena->getTablero()->getNodoCasillaSobrevolada();
    //   std::cout << "CasillaSobrevolada: "<<   casillaSobrevolada->getNombre()  << std::endl;

    //devulve true si ha cambiado de casilla
    if (!casillaSobreAnterior || casillaSobrevolada->getNombre() != casillaSobreAnterior-> getNombre())
    {
        if (casillaSobreAnterior)
        {
            //     std::cout << "CasillaSobrevolada ANTERIOR: "<<   casillaSobreAnterior->getNombre()  << std::endl;
            escena->apagaVentanaEmergente();

            casillaSobreAnterior->apagaCasilla();
            //tablero->setNodoCasillaSobrevolada(-1);
        }

        //   std::cout << "CAMBIA LA CASILLA SOBREVOLADA: " << std::endl;
        escena->getTablero()->setNodoCasillaSobrevolada(casillaSobrevolada);

        return true;
    }
    return false;
}


std::string Jugador::getNombre()
{
    return nombre;
}

void Jugador::setNombre( std::string unNombre)
{
    nombre = unNombre;
}

int Jugador::aplicaSeleccion()
{
    modelo->mueveTablero();  
    modelo->tableroModelo->turnoN = !modelo->tableroModelo->turnoN;

    //NORMALIZA EL TABLERO PARA EL CAMBIO DE TURNO
    for(int i=0; i<144;i++)
    {
        //NORMALIZA EL TABLERO, CAMBIA EL SIGNO DE LAS FICHAS
        if (modelo->tableroModelo->casillasInt[i] != 0 && modelo->tableroModelo->casillasInt[i] != 99)
        {
            modelo->tableroModelo->casillasInt[i] = -modelo->tableroModelo->casillasInt[i];
        }
    }
    modelo->tableroModelo->jugada[0] = -1;
    modelo->tableroModelo->jugada[1] = -1;

    // tablero->cambiaTurno();
    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);
  //  ModeloTablero* turnoSiguiente = new ModeloTablero(*modelo->tableroModelo);
    bool Jaque = false;

    //   if (turnoNegras)tablero = Calculos::normalizaTablero(tablero);
    if (modelo->tableroModelo->evaluaJaque())
    {//JAQUE AL REY
        std::cout << "!!!!HA EVALUADO JAQUE PARA EL ENEMIGO AL MOVER FICHA" << std::endl;
        Jaque = true;
    }

    std::cout << "!!!!!!pasa! " << std::endl;

    //ATUALIZA EL TABLERO DE LA VISTA
    Tablero* tablero = escena->getTablero();

    if (tablero->getNodoCasillaSobrevolada() != NULL)
        tablero->getNodoCasillaSobrevolada()->apagaCasilla();

    escena->apagaVentanaEmergente();
    tablero->fichaSeleccionada = false;

    int filaSel;
    int colSel;
    int filaNueva;
    int colNueva;

    std::cout << "tableroModelo->jugada[0] " << modelo->tableroModelo->jugada[0]<< std::endl;
    std::cout << "tableroModelo->jugada[1] " << modelo->tableroModelo->jugada[1]<< std::endl;

    filaSel = (modelo->tableroModelo->jugada[0]/12)-2;
    colSel = (modelo->tableroModelo->jugada[0]%12)-2;
    filaNueva = (modelo->tableroModelo->jugada[1]/12)-2;
    colNueva = (modelo->tableroModelo->jugada[1]%12)-2;


    if (tablero->getNodoCasillaSeleccionada() == NULL)
    {    //JUGADOR ARTIFICIAL

        // std::cout << "tableroModelo->jugada[0] en escenaajedrez al aplicar: "<< tableroModelo->jugada[0] << " tableroModelo->jugada[0]/12: "<< tableroModelo->jugada[0]/12 << " tableroModelo->jugada[0]%12 " << tableroModelo->jugada[0]%12 << std::endl;
        // std::cout << "tableroModelo->jugada[1]en escenaajedrez al aplicar: "<< tableroModelo->jugada[1] << " tableroModelo->jugada[1]/12: "<< tableroModelo->jugada[1]/12 << " tableroModelo->jugada[1]%12 " << tableroModelo->jugada[1]%12 << std::endl;
        std::cout << "SELECT 1 FILA: "<< (filaSel*8)+colSel <<std::endl;

        tablero->setNodoCasillaSeleccionada((filaSel * 8) + colSel);

        std::cout << "nombre: "<< tablero->getNodoCasillaSeleccionada()->getNombre()<<std::endl;

        tablero->setNodoCasillaSobrevolada((filaNueva * 8) + colNueva);
    }

    tablero->actualizaTablero();








    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Movimientos::pruebaJaqueMate(modelo->tableroModelo))
    {
      //  delete turnoSiguiente;
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS PARA EL TURNO SIGUIENTE(JAQUE MATE O AHOGADO)!!!: " << std::endl;

        //SE EVALUA EL JAQUE Y SI EL REY NO ESTA EN JAQUE ES QUE ES AHOGADO
        //EVALUA JAQUE
        if (Jaque)
        {
            std::cout << "!!!!!!!!!DEVUELVE JAQUE MATE! " << std::endl;
            //JAQUE MATE
            return 2;
        }
        else
        { //NO HAY JAQUE, AHOGADO, RESULTADO EN TABLAS
            std::cout << "!!!!!!!!!DEVUELVE REY AHOGADO! " << std::endl;
            return 3;
        }
    }
    else
    {


      //  delete turnoSiguiente;
        if (Jaque)
        {//Jaque asecas
            std::cout << "!!!!!!!!!DEVUELVE JAQUE! " << std::endl;

            return 4;
        }
        else
        {
            std::cout << "!!!!!!!!!!!!!!!!!!NO HAY JAQUE Y MUEVE BIEN!!!: " << std::endl;
            //Mueve sin jaque
            return 1;
        }
    }
    return 0;
}

void Jugador::promocionaPeon()
{
    Tablero* tablero = escena->getTablero();

    Casilla* casilla = tablero->getNodoCasillaSobrevolada();

    if(!casilla->sinHijos())
    {
        //MIRA SI PROMOCIONA PEON
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

        if(ficha->tipo_Ficha == 1
                && ((!tablero->getTurnoNegras()
                     && tablero->getNodoCasillaSobrevolada()->getPosicion().Fila == 7)
                    || (tablero->getTurnoNegras()
                        && tablero->getNodoCasillaSobrevolada()->getPosicion().Fila == 0 )))
        {
            casilla->eliminaHijo(0);

            // ficha = tablero->promocionaPeon(ficha);
            //  Ogre::Entity *entidadFicha;

            std::stringstream saux;

            saux.str("");
            saux << "ReinaPR_" << tablero->peonesPromocionados;

            FichaReina* nodoNuevo =new FichaReina(*ficha, saux.str());

            if (!tablero->getTurnoNegras())
            {
                nodoNuevo->creaModelo3D(escena->mSceneMgr,"Reina",BLANCAS);
            }
            else
            {
                nodoNuevo->creaModelo3D(escena->mSceneMgr,"Reina",NEGRAS);
                nodoNuevo->cambiaMaterial("MaterialFichaNegra");
            }

            delete ficha;

            tablero->peonesPromocionados++;

            casilla->agregaHijo(nodoNuevo);
        }
    }
    //return static_cast<FichaReina*>(nodoNuevo);
}
