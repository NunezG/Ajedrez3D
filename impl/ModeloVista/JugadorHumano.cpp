#include "../../headers/ModeloVista/JugadorHumano.h"



JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo) :
    Jugador(miEscena, modelo)
  
  
  
{
    
}

JugadorHumano::~JugadorHumano()
{
    
    
}

//void JugadorHumano::setVentana(Ventana* obj){
//ventana = obj;
//}

void JugadorHumano::mueveFicha()
{

 //   std::cout << "HUMANO MUEVE FICHA " << std::endl;


   // if (miTablero == NULL)
     //   miTablero = tablero;
   // std::cout << "mueveficha dentro de humano"<< std::endl;

    
    //HA CAPTUURADO MOVIMIENTO??
    
    // if (miTablero->g)
    
    //esperaEleccion = true;
    
    //punteroVentana.capture();

   // return miTablero;
    
}

//bool JugadorHumano::ejecutaMov()
//{
 //   miTablero->movimiento[0] = 1;

//}



bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{



    if (Jugador::casillaSobrevolada(nombreCasilla))
    {

        std::cout << "SIGUE CON LO DE CASILLASOBRE" << std::endl;


        Casilla* nodoSeleccionado = escena->tablero->getNodoCasillaSeleccionada();
        std::cout << "NPMBRE SELECT: "<<  nodoSeleccionado->getNombre() << std::endl;

        // elTablero = miTablero;
        //   posicion seleccionado = nodoSeleccionado->getPosicion();
        // Ogre::Vector3 nuevo = nodoSobrevolado->getNodoOgre()->getPosition();
        std::cout << "entra 2"<< std::endl;

        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;

        Ficha *mFicha = static_cast<Ficha*>(nodoSeleccionado->getHijo(0));
        tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        std::cout << "entra3"<< std::endl;

      //  tableroModelo->
        //tablero->validacasilla();

        //   tableroModelo->casillasInt = tablero->traduceTablero();
        std::cout << "jugada inicia"<< std::endl;

        std::cout << "jug1: " <<modelo->tableroModelo->jugada[0] << std::endl;
        std::cout  <<"jug2: "<<modelo->tableroModelo->jugada[1] << std::endl;

        std::cout << "juggg seleccionado: " <<nodoSeleccionado->getPosicion().Fila <<" jug2COL: "<<nodoSeleccionado->getPosicion().Columna << std::endl;

        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;

      //  std::cout << "jugada final"<< std::endl;
        modelo->tableroModelo->jugada[1] = 24 + (escena->tablero->getNodoCasillaSobrevolada()->getPosicion().Fila * 12) + escena->tablero->getNodoCasillaSobrevolada()->getPosicion().Columna + 2;

        std::cout << "jug12: " <<modelo->tableroModelo->jugada[0] << std::endl;
        std::cout  <<"jug22: "<<modelo->tableroModelo->jugada[1] << std::endl;

        //AUTORIZA
        int resultado = modelo->autorizaCasilla(tipo);

       std::cout << "autorizaCasillaSobrevolada: "<< resultado << std::endl;

        //  ventanaEmergente = NULL;
        if (resultado == 1)
        {
            std::cout << "CASILLA AUTORIZADA" << std::endl;
            escena->tablero->getNodoCasillaSobrevolada()->iluminaCasilla();
        }else
        {
            std::cout << "CASILLA PROHIBIDA" << std::endl;

            modelo->tableroModelo->jugada[0] = -1;
            modelo->tableroModelo->jugada[1] = -1;

            if (resultado == 2)
            {
                std::cout << "JAQUE AL SOBREVOLAR CASILLA" << std::endl;
                escena->muestraVentanaEmergente("Jaque");

            }
        }



    }else return false;


}



bool JugadorHumano::esHumano()
{
    return true;
}

