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
    escena->apagaVentanaEmergente();

    escena->getTablero()->actualizaTablero(escena->mSceneMgr);

    std::cout << "!!!!!promociona! " << std::endl;

    //PROMOCIONA PEÓN
  //  escena->getTablero()->promocionaPeon(escena->mSceneMgr);


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

