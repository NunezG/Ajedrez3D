#include "../../headers/Modelo/JugadorHumano.h"



JugadorHumano::JugadorHumano(Tablero* tablero) :
    Jugador(tablero)



{

}


JugadorHumano::~JugadorHumano()
{


}


//void JugadorHumano::setVentana(Ventana* obj){

//ventana = obj;

//}


void JugadorHumano::mueveFicha(float time){


    //HA CAPTUURADO MOVIMIENTO??

    std::cout << "HUMANO MUEVE FICHA " << std::endl;


   // if (miTablero->g)

    //esperaEleccion = true;

//punteroVentana.capture();

}

void JugadorHumano::sobreVuelaCasilla(){
    miTablero->getNodoCasillaSobrevolada()->iluminaCasilla();
  //  miTablero->getNodoCasillaSobrevolada()->seleccionada = false;

}



void JugadorHumano::autorizaCasilla(){

    //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
    bool autorizado= true;
    autorizado = Autorizaciones::autorizaCasilla(miTablero);

    std::cout << "autorizado: "<<autorizado << std::endl;


    if(autorizado)
    {

        if  (miTablero->getNodoCasillaSobrevolada()->sinHijos() != true)
        {


            if (miTablero->FichaComestible()) {
                //falta evaluar jaque y ahogado
                if (!Autorizaciones::evaluaJaque(miTablero->mueveYTraduceTablero(), miTablero->getTurnoNegras()))
                {

                   // miTablero->getNodoCasillaSobrevolada()->seleccionada = true;

                    sobreVuelaCasilla();

                    std::cout << "ES COMESTIBLE" << std::endl;
                }else {
                    std::cout << "JAQUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;

                }

            }

        } else{

            //falta evaluar jaque y ahogado
            if (!Autorizaciones::evaluaJaque(miTablero->mueveYTraduceTablero(), miTablero->getTurnoNegras()))
            {
               // miTablero->getNodoCasillaSobrevolada()->seleccionada = true;

                sobreVuelaCasilla();

                std::cout << "ES COMESTIBLE" << std::endl;
            }else {
                std::cout << "JAQUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;


            }

        }
    }

}

void JugadorHumano::aplicaSeleccion()
{
   // esperaEleccion = false;
    miTablero->actualizaTablero(miTablero->getNodoCasillaSeleccionada()->getPosicion(), miTablero->getNodoCasillaSobrevolada()->getPosicion());
    miTablero->fichaSeleccionada = false;
    std::cout << "cambiatur 4 "<< std::endl;

    miTablero->cambiaTurno();
    miTablero->rotacionCamara = Ogre::Real(180.0f);


    std::cout << "FIN cambiatur 4 "<< std::endl;
}



bool JugadorHumano::esHumano()
{
    return true;
}
