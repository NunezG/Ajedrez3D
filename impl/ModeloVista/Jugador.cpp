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
        if (casillaSobreAnterior )
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

bool Jugador::aplicaSeleccion()
{
    std::cout << "aplicaSeleccion"<< std::endl;

    //ATUALIZA EL TABLERO DE LA VISTA
    escena->apagaVentanaEmergente();

    std::cout << "aplicaSeleccion2222"<< std::endl;

    int resultado = modelo->mueveTablero();

 /*    if (!modelo->tableroModelo->turnoN)
  {//INVIERTE
        std::cout << "TURNO MEGRAS EN ALFABETA" << std::endl;
        std::cout << "ORIG DE ALFABETA ANTES DE REVERTIR!!!!: "<< int( modelo->jugadaElegida[0])<< std::endl;
        std::cout << "DEST DE ALFABETA ANTES DE REVERTIR!!!!: "<< int( modelo->jugadaElegida[1])<< std::endl;

        modelo->jugadaElegida[0] = 143- modelo->jugadaElegida[0];
       modelo->jugadaElegida[1] = 143- modelo->jugadaElegida[1];
        // escena->tablero->setCasillaSeleccionada(escena->tablero->getCasillaSeleccionada());
    }
*/
    escena->getTablero()->actualizaTablero(escena->mSceneMgr);

    std::cout << "!!!!!promociona! " << std::endl;

    //PROMOCIONA PEÓN
    //  escena->getTablero()->promocionaPeon(escena->mSceneMgr);

    //COMPRUEBA JAQUE AL MOVER TABLERO EN MODELO

    modelo->jugadaElegida[0] = 0;
    modelo->jugadaElegida[1] = 0;

    switch (resultado)
    {
    case 2:
        escena->muestraVentanaEmergente("Jaque");
        return true;
    case 3:
        escena->muestraVentanaEmergente("JaqueMate");
        return false;
    case 4:
        escena->muestraVentanaEmergente("Tablas");
        return false;
    default: //MOVIMIENTO NORMAL
        return true;
    }  
}
