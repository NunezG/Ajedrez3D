#include "../../headers/ModeloVista/JugadorHumano.h"

JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo) :
    Jugador(miEscena, modelo)
{   
}

JugadorHumano::~JugadorHumano()
{ 
}

bool JugadorHumano::aplicaSeleccion()
{

  //  modelo->jugadaElegida[0] = escena->tablero->getCasillaSeleccionada();
   //  modelo->jugadaElegida[1] = escena->tablero->getCasillaSobrevolada()

    return Jugador::aplicaSeleccion();



}


bool JugadorHumano::iniciaTurno()
{
    std::cout << "INICIATURNO HUMANO"<< std::endl;

    return false;


}

bool JugadorHumano::botonIzquierdo(CEGUI::Vector2 pos)
{
    std::cout   << "   botonIzquierdo" << std::endl;

    Tablero* tablero = escena->getTablero();

    if (tablero->getCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...
        //Ficha* ficha = static_cast<Ficha*>(tablero->getCasillaSeleccionada()->getHijo(0));
        // ficha->getNodoOgre()->showBoundingBox(false);
        tablero->setCasillaSeleccionada(-1);
    }
    std::cout   << "   botonIzquierdo222333333" << std::endl;
    std::cout   << "   botonIzqui" << escena->encuentraCasillaSobrevolada(pos)<<std::endl;

    Casilla* casilla = static_cast<Casilla*>(tablero->getHijo(escena->encuentraCasillaSobrevolada(pos)));

    if (casilla != NULL && !casilla->sinHijos())
    {
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));
        if ((tablero->getTurnoNegras()
             && ficha->esNegra)
                || (!tablero->getTurnoNegras()
                    && !ficha->esNegra))
        {
            std::cout   << "   setCasillaSeleccionada: "<<ficha->getNombre() << std::endl;
            tablero->setCasillaSeleccionada(casilla);
            // ficha->getNodoOgre()->showBoundingBox(true);
            return true;
        }
    }
    return false;
}

bool JugadorHumano::botonDerecho()
{
    return (escena->getTablero()->getCasillaSobrevolada() != NULL);
}

bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{
    if (escena->getTablero()->getCasillaSeleccionada() != NULL && Jugador::casillaSobrevolada(nombreCasilla))
    {
        Casilla* nodoSeleccionado = escena->getTablero()->getCasillaSeleccionada();
        std::cout << "NPMBRE SELECT: "<<  nodoSeleccionado->getNombre() << std::endl;

        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;

        Ficha *mFicha = static_cast<Ficha*>(nodoSeleccionado->getHijo(0));
        tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        //   tableroModelo->casillasInt = tablero->traduceTablero();
        std::cout << "jugada inicia"<< std::endl;

        std::cout << "jug1: " <<int(modelo->tableroModelo->jugada[0]) << std::endl;
        std::cout  <<"jug2: "<<int(modelo->tableroModelo->jugada[1]) << std::endl;

        std::cout << "juggg seleccionado: " <<nodoSeleccionado->getPosicion().Fila <<" jug2COL: "<<nodoSeleccionado->getPosicion().Columna << std::endl;

        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
        modelo->tableroModelo->jugada[1] = 24 + (escena->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escena->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;




        std::cout << "jug12: " << int(modelo->tableroModelo->jugada[0]) << std::endl;
        std::cout  <<"jug22: "<<int(modelo->tableroModelo->jugada[1]) << std::endl;

        //AUTORIZA
        int resultado = modelo->autorizaCasilla(tipo);

        if (resultado == 1)
        {
            modelo->jugadaElegida[0] = modelo->tableroModelo->jugada[0];
            modelo->jugadaElegida[1] = modelo->tableroModelo->jugada[1];

            // CASILLA AUTORIZADA
            escena->getTablero()->getCasillaSobrevolada()->iluminaCasilla();
            return true;
        }
        else
        {
            std::cout  <<"CASILLA PROHIBIDA: "<<  resultado<<std::endl;

            // CASILLA PROHIBIDA
            modelo->tableroModelo->jugada[0] = -1;
            modelo->tableroModelo->jugada[1] = -1;
            modelo->jugadaElegida[0] = -1;
            modelo->jugadaElegida[1] = -1;


            if (resultado == 2)
            {
                //JAQUE AL SOBREVOLAR CASILLA
                escena->muestraVentanaEmergente("Jaque");
            }
            return false;
        }
    }
    else return false;
}

bool JugadorHumano::esHumano()
{
    return true;
}
