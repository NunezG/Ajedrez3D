#include "../../headers/ModeloVista/JugadorHumano.h"



JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena) :
    Jugador(miEscena)
  
  
  
{
    
}

JugadorHumano::~JugadorHumano()
{
    
    
}

//void JugadorHumano::setVentana(Ventana* obj){
//ventana = obj;
//}

void JugadorHumano::mueveFicha(ModeloTablero* tablero)
{

 //   std::cout << "HUMANO MUEVE FICHA " << std::endl;


    if (miTablero == NULL)
        miTablero = tablero;
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



        Casilla* nodoSeleccionado = tablero->getNodoCasillaSeleccionada();
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

        //tablero->validacasilla();

        //   tableroModelo->casillasInt = tablero->traduceTablero();
        std::cout << "jugada inicia"<< std::endl;

        std::cout << "jug1: " <<tableroModelo->jugada[0] << std::endl;
        std::cout << "jug2: " <<nodoSeleccionado->getPosicion().Fila <<"jug2: "<<nodoSeleccionado->getPosicion().Columna << std::endl;
        std::cout  <<"jug2: "<<nodoSeleccionado->getPosicion().Columna << std::endl;

        tableroModelo->jugada[0] = 24+ (nodoSeleccionado->getPosicion().Fila*12) + nodoSeleccionado->getPosicion().Columna + 2;

        std::cout << "jugada final"<< std::endl;
        tableroModelo->jugada[1] = 24+ (casillaSobrevolada->getPosicion().Fila*12) + casillaSobrevolada->getPosicion().Columna + 2;

        std::cout << "autorizaCasillaSobrevolada  2 222"<< std::endl;
        //AUTORIZA
        int resultado = autorizaCasilla(tableroModelo,tipo);

        std::cout << "autorizaCasillaSobrevolada   333"<< std::endl;

        //  ventanaEmergente = NULL;
        if (resultado == 1)
        {
            std::cout << "CASILLA AUTORIZADA" << std::endl;
            tablero->getNodoCasillaSobrevolada()->iluminaCasilla();
        }else
        {
            tableroModelo->jugada[0] = -1;
            tableroModelo->jugada[1] = -1;

            if (resultado == 3)
            {
                std::cout << "JAQUE AL SOBREVOLAR CASILLA" << std::endl;
                escena->muestraVentanaEmergente("Jaque");

            }
        }



    }else return false;


}

bool JugadorHumano::activaMovimiento()
{



    tableroModelo->jugadaAutorizada = true;




}



bool JugadorHumano::esHumano()
{
    return true;
}

//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int JugadorHumano::autorizaCasilla(ModeloTablero* tablero, tipoFicha tipo)
{

    //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
    bool autorizado= true;


    // tablero->casillasInt = tablero->traduceTablero();


    autorizado = Autorizaciones::autoriza(tablero, tipo);

    //  if (turnoNegras)tablero = Autorizaciones::normalizaTablero(tablero);
    std::cout << "autorizado en autorizacasilla: "<<autorizado << std::endl;


    if(autorizado)
    {
        //EVALUA EL JAQUE CON LA FICHA YA MOVIDA

        //si esta ocupado y no es comestible

        int* tableroInt = tablero->mueveTablero();

        //if(turnoNegras)Autorizaciones::normalizaTablero(tableroInt);
        // else return 0;

        std::cout << "evalua jaque" << std::endl;


        //Autorizaciones::normalizaTablero(tablero);
        // if (turnoNegras)tableroInt = Autorizaciones::normalizaTablero(tableroInt);

        std::cout << "evalua " << std::endl;

        //EVALUA JAQUE
        if (!tablero->evaluaJaque())
        {


            // tablero->getNodoCasillaSobrevolada()->seleccionada = true;
            //ILUMINA LA CASILLA


            std::cout << "ES COMESTIBLE" << std::endl;
            return 1;
        }else
        {

            std::cout << "JAQUE AL REY" << std::endl;





            return 3;

        }
    }
    std::cout << "sale de autorizado" << std::endl;


}
