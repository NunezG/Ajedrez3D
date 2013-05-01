#include "../../headers/Modelo/JugadorHumano.h"



JugadorHumano::JugadorHumano() :
    Jugador()
  , esperaSeleccion(0)



{

}


JugadorHumano::~JugadorHumano()
{


}

void JugadorHumano::mueveFicha(float frecuencia){

    esperaSeleccion = true;



//punteroVentana.capture();

}




bool JugadorHumano::esHumano(){

    return true;
}
