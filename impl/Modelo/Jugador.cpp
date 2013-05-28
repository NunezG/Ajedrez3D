#include "../../headers/Modelo/Jugador.h"



Jugador::Jugador() :
    jugadorNegras(false),
    nombre(""),
    miTablero(NULL)

  //esperaEleccion(false)



{


}

Jugador::~Jugador()
{


}






std::string Jugador::getNombre()
{

    return nombre;


}



void Jugador::setNombre( std::string unNombre)
{


    nombre = unNombre;
}


int Jugador::aplicaSeleccion(ModeloTablero* tablero, int filaSel,int colSel, int filaNueva, int colNueva)
{

    tablero->casillasInt == Calculos::mueveTablero( tablero->casillasInt, filaSel,  colSel,  filaNueva,  colNueva);

    std::cout << "cambiatur 6"<< tablero->turnoN<<std::endl;
    // tablero->cambiaTurno();



    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);


    //CAMBIA DE TURNO

    ModeloTablero* turnoSiguiente = new ModeloTablero(*tablero);
    //   tablero->turnoN = !tablero->turnoN;
    bool Jaque = false;

    //   if (turnoNegras)tablero = Calculos::normalizaTablero(tablero);


    std::cout << "cambiatur 7 "<< turnoSiguiente->turnoN<<std::endl;

    if (Calculos::evaluaJaque(turnoSiguiente->casillasInt, turnoSiguiente->turnoN))
    {//JAQUE AL REY

        std::cout << "!!!!HA EVALUADO JAQUE AL MOVER FICHA" << std::endl;


        Jaque = true;

    }
    std::cout << "!!!!!!pasa! " << std::endl;

    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Movimientos::generaMovimientos(turnoSiguiente, true))
    {
        delete turnoSiguiente;
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

    }else
    {
        delete turnoSiguiente;
        if (Jaque)
        {//Jaque asecas
            return 4;
        }
        else
        {
            std::cout << "!!!!!!!!!!!!!!!!!!NO HAY JAQUE Y MUEVE BIEN!!!: " << std::endl;

            //Mueve sin jaque
            return 1;
        }
    }


    return 0;

    std::cout << "FIN cambiatur 4 "<< std::endl;
}
