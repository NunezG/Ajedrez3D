#include "../../headers/ModeloVista/JugadorHumano.h"

JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo) :
    Jugador(miEscena, modelo)
  
{   
}

JugadorHumano::~JugadorHumano()
{ 
}


bool JugadorHumano::botonIzquierdo(CEGUI::Vector2 pos)
{

    std::cout   << "   botonIzquierdo" << std::endl;

    Tablero* tablero = escena->getTablero();

    tablero->fichaSeleccionada = false;

    if (tablero->getNodoCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...
        tablero->getNodoCasillaSeleccionada()->apagaCasilla();
        //Ficha* ficha = static_cast<Ficha*>(tablero->getNodoCasillaSeleccionada()->getHijo(0));
       // ficha->getNodoOgre()->showBoundingBox(false);
        tablero->setNodoCasillaSeleccionada(-1);
    }
    std::cout   << "   botonIzquierdo222333333" << std::endl;
    std::cout   << "   botonIzqui" << escena->encuentraCasillaSobrevolada(pos)<<std::endl;

    Casilla* casilla = static_cast<Casilla*>(tablero->getHijo(escena->encuentraCasillaSobrevolada(pos)));
    std::cout   << "   botonIzquierdo222333333" << std::endl;

    if (casilla != NULL && !casilla->sinHijos())
    {
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));
        if ((tablero->getTurnoNegras()
             && ficha->esNegra)
                || (!tablero->getTurnoNegras()
                    && !ficha->esNegra))
        {
            casilla->iluminaCasilla();
            tablero->setNodoCasillaSeleccionada(casilla);
           // ficha->getNodoOgre()->showBoundingBox(true);
            tablero->fichaSeleccionada = true;
            return true;
        }
    }
    std::cout   << "   botonIzquierdo00000" << std::endl;

    return false;
}

bool JugadorHumano::botonDerecho()
{
    return (modelo->tableroModelo->jugada[1] > 0);
}




bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{
    if (Jugador::casillaSobrevolada(nombreCasilla))
    {
        Casilla* nodoSeleccionado = escena->getTablero()->getNodoCasillaSeleccionada();
        std::cout << "NPMBRE SELECT: "<<  nodoSeleccionado->getNombre() << std::endl;

        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;

        Ficha *mFicha = static_cast<Ficha*>(nodoSeleccionado->getHijo(0));
        tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        //   tableroModelo->casillasInt = tablero->traduceTablero();
        std::cout << "jugada inicia"<< std::endl;

        std::cout << "jug1: " <<modelo->tableroModelo->jugada[0] << std::endl;
        std::cout  <<"jug2: "<<modelo->tableroModelo->jugada[1] << std::endl;

        std::cout << "juggg seleccionado: " <<nodoSeleccionado->getPosicion().Fila <<" jug2COL: "<<nodoSeleccionado->getPosicion().Columna << std::endl;

        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
        modelo->tableroModelo->jugada[1] = 24 + (escena->getTablero()->getNodoCasillaSobrevolada()->getPosicion().Fila * 12) + escena->getTablero()->getNodoCasillaSobrevolada()->getPosicion().Columna + 2;

        std::cout << "jug12: " <<modelo->tableroModelo->jugada[0] << std::endl;
        std::cout  <<"jug22: "<<modelo->tableroModelo->jugada[1] << std::endl;

        //AUTORIZA
        int resultado = modelo->autorizaCasilla(tipo);

        if (resultado == 1)
        {
           // CASILLA AUTORIZADA
            escena->getTablero()->getNodoCasillaSobrevolada()->iluminaCasilla();
            return true;
        }
        else
        {
            // CASILLA PROHIBIDA
            modelo->tableroModelo->jugada[0] = -1;
            modelo->tableroModelo->jugada[1] = -1;

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
