#include "../../headers/Modelo/JugadorHumano.h"



JugadorHumano::JugadorHumano() :
    Jugador()
  
  
  
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


bool JugadorHumano::esHumano()
{
    return true;
}

//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int JugadorHumano::autorizaCasilla(int* tablero, tipoFicha tipo, int filaSel, int colSel, int filaNueva, int colNueva, bool turnoNegras, int alPaso)
{

    //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
    bool autorizado= true;


    // tablero->casillasInt = tablero->traduceTablero();


    autorizado = Autorizaciones::autoriza(tablero, tipo, filaSel, colSel, filaNueva, colNueva, turnoNegras, alPaso);

    //  if (turnoNegras)tablero = Autorizaciones::normalizaTablero(tablero);
    std::cout << "autorizado en autorizacasilla: "<<autorizado << std::endl;


    if(autorizado)
    {
        //EVALUA EL JAQUE CON LA FICHA YA MOVIDA

        //si esta ocupado y no es comestible

        int* tableroInt = Autorizaciones::mueveTablero(tablero, filaSel, colSel, filaNueva, colNueva);

        //if(turnoNegras)Autorizaciones::normalizaTablero(tableroInt);
        // else return 0;

        std::cout << "evalua jaque" << std::endl;


        //Autorizaciones::normalizaTablero(tablero);
        // if (turnoNegras)tableroInt = Autorizaciones::normalizaTablero(tableroInt);

        std::cout << "evalua " << std::endl;

        //EVALUA JAQUE
        if (!Autorizaciones::evaluaJaque(tableroInt, turnoNegras))
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
