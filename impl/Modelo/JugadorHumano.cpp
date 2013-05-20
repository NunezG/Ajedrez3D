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

void JugadorHumano::mueveFicha()
{


    std::cout << "mueveficha dentro de humano"<< std::endl;

    
    //HA CAPTUURADO MOVIMIENTO??
    
    // if (miTablero->g)
    
    //esperaEleccion = true;
    
    //punteroVentana.capture();
    
}



int JugadorHumano::aplicaSeleccion(int* tablero, int filaSel, int colSel, int filaNueva, int colNueva, bool turnoNegras, int alPaso)
{
    // esperaEleccion = false;

    tablero == Autorizaciones::mueveTablero( tablero, filaSel,  colSel,  filaNueva,  colNueva);


    
    std::cout << "cambiatur 6"<< std::endl;
    // tablero->cambiaTurno();
    
    turnoNegras = turnoNegras;

    // if(tablero->getTurnoNegras()) tablero->casillasInt = tablero->traduceTablero();
    

    
    std::cout << "cambiatur 7 "<< std::endl;
    
    if (Autorizaciones::verificaJaqueMate(tablero, turnoNegras, alPaso))
    {
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS (JAQUE MATE O AHOGADO)!!!: " << std::endl;

        return 2;
        

        
    }else
    {
        return 1;

    }
    
    
    std::cout << "FIN cambiatur 4 "<< std::endl;
}

bool JugadorHumano::esHumano()
{
    return true;
}

//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int JugadorHumano::autorizaCasilla(int* tablero, tipoFicha tipo, int filaSel, int colSel, int filaNueva, int colNueva, bool turnoNegras, int alPaso){

    //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
    bool autorizado= true;


    // tablero->casillasInt = tablero->traduceTablero();

    if (turnoNegras)Autorizaciones::normalizaTablero(tablero);

    autorizado = Autorizaciones::autoriza(tablero, tipo, filaSel, colSel, filaNueva, colNueva, turnoNegras, alPaso);

    std::cout << "autorizado en autorizacasilla: "<<autorizado << std::endl;


    if(autorizado)
    {
        //EVALUA EL JAQUE CON LA FICHA YA MOVIDA

        //si esta ocupado y no es comestible

        int* tableroInt = Autorizaciones::mueveTablero(tablero, filaSel, colSel, filaNueva, colNueva);

        if(!turnoNegras)Autorizaciones::normalizaTablero(tableroInt);
        else return 0;

        std::cout << "evalua jaque" << std::endl;

        //EVALUA JAQUE
        if (!Autorizaciones::evaluaJaque(tableroInt, !turnoNegras))
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

