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
    Casilla* casillaSobreAnterior = escena->getTablero()->getCasillaSobrevolada();
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
        escena->getTablero()->setCasillaSobrevolada(casillaSobrevolada);

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
    //ATUALIZA EL TABLERO DE LA VISTA
    Tablero* tablero = escena->getTablero();


    escena->apagaVentanaEmergente();

    posicion inicial;
    posicion final;

    inicial.Fila = (modelo->tableroModelo->jugada[0]/12)-2;
    inicial.Columna = (modelo->tableroModelo->jugada[0]%12)-2;
    final.Fila = (modelo->tableroModelo->jugada[1]/12)-2;
    final.Columna = (modelo->tableroModelo->jugada[1]%12)-2;

    std::cout << "tableroModelo->jugada[0] " << modelo->tableroModelo->jugada[0]<< std::endl;
    std::cout << "tableroModelo->jugada[1] " << modelo->tableroModelo->jugada[1]<< std::endl;

    tablero->actualizaTablero(inicial, final);

    //COMPRUEBA JAQUE AL MOVER TABLERO EN MODELO
    int resultado = modelo->mueveTablero();
    switch (resultado)
    {
    case 2:
        escena->muestraVentanaEmergente("Jaque");
    break;
    case 3:
        escena->muestraVentanaEmergente("JaqueMate");
        break;
    case 4:
        escena->muestraVentanaEmergente("Tablas");
        break;
    default:
        break;
    }
}

void Jugador::promocionaPeon()
{
    Tablero* tablero = escena->getTablero();
    Casilla* casilla = tablero->getCasillaSobrevolada();

    if(!casilla->sinHijos())
    {
        //MIRA SI PROMOCIONA PEON
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

        if(ficha->tipo_Ficha == 1
                && ((!tablero->getTurnoNegras()
                     && tablero->getCasillaSobrevolada()->getPosicion().Fila == 7)
                    || (tablero->getTurnoNegras()
                        && tablero->getCasillaSobrevolada()->getPosicion().Fila == 0 )))
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
