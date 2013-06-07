#include "../../headers/ModeloVista/Jugador.h"

Jugador::Jugador(EscenaAjedrez* miEscena, Modelo* modelo) :
    jugadorNegras(false),
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

bool Jugador::activaMovimiento()
{
    std::cout << "ACTIVAMOV"<< std::endl;
    modelo->jugadaAutorizada = true;
   // aplicaCambio();
}

bool Jugador::casillaSobrevolada(const std::string nombreCasilla)
{
    //  std::cout << "auto1: " << nombreCasilla<< std::endl;

    Casilla* casillaSobrevolada = static_cast<Casilla*>(escena->tablero->getHijo(nombreCasilla));

    //   std::cout << "auto222" << std::endl;

    Casilla* casillaSobreAnterior = escena->tablero->getNodoCasillaSobrevolada();

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
        escena->tablero->setNodoCasillaSobrevolada(casillaSobrevolada);

        return true;
    }

    return false;
}

void Jugador::esperaJugador()
{

    //  std::cout << "espera"<<std::endl;
    // std::cout << "jugadores.size()"<< modelo->jugadores.size()<<std::endl;

    //  std::cout  << "mueveficha " << std::endl;
    mueveFicha();
    std::cout  << "miramov " << std::endl;
    //HAY RESULTADO
    if(modelo->jugadaAutorizada)
    {

        std::cout  << "HA AUTORIZADO UN MOVIMIENTO EN EL BUCLE!!! " << std::endl;

        //  tableroModelo->movimiento[0] = -99;
        // std::cout  << "BORRA tablromov" << std::endl;
    }
    // tablero->setNodoCasillaSeleccionada();
    // tablero->setNodoCasillaSobrevolada();
    //  tablero->actualizaTablero();


    //   modelo->mueveJugador(tablero->getTurnoNegras());

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

    std::cout << "cambiatur 6"<< modelo->tableroModelo->turnoN<<std::endl;
    // tablero->cambiaTurno();
    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);

    //CAMBIA DE TURNO
    ModeloTablero* turnoSiguiente = new ModeloTablero(*modelo->tableroModelo);
    bool Jaque = false;

    //   if (turnoNegras)tablero = Calculos::normalizaTablero(tablero);
    std::cout << "cambiatur 7 "<< turnoSiguiente->turnoN<<std::endl;

    if (turnoSiguiente->evaluaJaque())
    {//JAQUE AL REY
        std::cout << "!!!!HA EVALUADO JAQUE PARA EL ENEMIGO AL MOVER FICHA" << std::endl;
        Jaque = true;
    }
    std::cout << "!!!!!!pasa! " << std::endl;

    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Movimientos::pruebaJaqueMate(turnoSiguiente))
    {
        delete turnoSiguiente;
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

    }else
    {
        delete turnoSiguiente;
        if (Jaque)
        {//Jaque asecas
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

    std::cout << "FIN cambiatur 4 "<< std::endl;
}

void Jugador::promocionaPeon()
{
    Casilla* casilla = escena->tablero->getNodoCasillaSobrevolada();

    if(!casilla->sinHijos())
    {
        //PROMOCIONA PEON
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

        if(ficha->tipo_Ficha == 1
                && ((!escena->tablero->getTurnoNegras()
                     && escena->tablero->getNodoCasillaSobrevolada()->getPosicion().Fila == 7)
                    || (escena->tablero->getTurnoNegras()
                        && escena->tablero->getNodoCasillaSobrevolada()->getPosicion().Fila == 0 )))
        {
            casilla->eliminaHijo(0);

            // ficha = tablero->promocionaPeon(ficha);
            //  Ogre::Entity *entidadFicha;

            std::stringstream saux;

            saux.str("");
            saux << "ReinaPR_" << escena->tablero->peonesPromocionados;

            FichaReina* nodoNuevo =new FichaReina(*ficha, saux.str());

            if (!escena->tablero->getTurnoNegras())
            {
                nodoNuevo->creaModelo3D(escena->mSceneMgr,"Reina",BLANCAS);
            }
            else
            {
                nodoNuevo->creaModelo3D(escena->mSceneMgr,"Reina",NEGRAS);
                nodoNuevo->cambiaMaterial("MaterialFichaNegra");
            }

            delete ficha;

            escena->tablero->peonesPromocionados++;

            casilla->agregaHijo(nodoNuevo);
        }
    }
    //return static_cast<FichaReina*>(nodoNuevo);
}
