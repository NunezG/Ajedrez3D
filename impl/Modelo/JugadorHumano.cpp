#include "../../headers/Modelo/JugadorHumano.h"



JugadorHumano::JugadorHumano(Tablero* tabl) :
    Jugador(tabl)
  , esperaSeleccion(0)



{

}


JugadorHumano::~JugadorHumano()
{


}

void JugadorHumano::mueveFicha(float frecuencia){
    std::cout  << "mueveFicha humana" << std::endl;


    esperaSeleccion = true;



//punteroVentana.capture();

}



void JugadorHumano::movimientoSeleccionado(){





}




bool JugadorHumano::esHumano(){

    return true;
}
