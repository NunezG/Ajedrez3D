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



int JugadorHumano::aplicaSeleccion(ModeloTablero* tablero, int filaSel,int colSel, int filaNueva, int colNueva)
{

    int* casillas = tablero->casillasInt;
    bool turnoNegras = tablero->turnoN;

    casillas == Autorizaciones::mueveTablero( casillas, filaSel,  colSel,  filaNueva,  colNueva);

    std::cout << "cambiatur 6"<< std::endl;
    // tablero->cambiaTurno();
    


    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);

    std::cout << "cambiatur 7 "<< std::endl;
    
    //CAMBIA DE TURNO
    turnoNegras = !turnoNegras;
    bool Jaque = false;



    if (turnoNegras)
       casillas = Autorizaciones::normalizaTablero(casillas);

    if (Autorizaciones::evaluaJaque(casillas, turnoNegras))
    {//JAQUE AL REY

        Jaque = true;

    }
    std::cout << "!!!!!!pasa! " << std::endl;

    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Movimientos::verificaJaqueMate(tablero))
    {
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

    }else if (Jaque)
    {//Jaque asecas
        return 4;
    }
    else
    {
        std::cout << "!!!!!!!!!!!!!!!!!!NO HAY JAQUE Y MUEVE BIEN!!!: " << std::endl;

        //Mueve sin jaque
        return 1;
    }


    return 0;

    std::cout << "FIN cambiatur 4 "<< std::endl;
}

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

    if (turnoNegras)tablero = Autorizaciones::normalizaTablero(tablero);

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
