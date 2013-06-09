#include "../../headers/Control/BaseJuego.h"

//-------------------------------------------------------------------------------------
BaseJuego::BaseJuego(void): punteroVentana(NULL)

{

}
//-------------------------------------------------------------------------------------
BaseJuego::~BaseJuego(void)
{
}


//-------------------------------------------------------------------------------------
void BaseJuego::go(void)
{
    modelo = Modelo::getSingletonPtr();
    modeloVista = new ModeloVista();
    punteroVentana = new Ventana(modeloVista);

    //UN BUCLE WHILE QUE MIRE UNA VARIABLE PARA RESETEAR LA VENTANA O ACABAR DEL TODO
    while(!modeloVista->getApagar())
    {
        punteroVentana->creaVista();
        punteroVentana->destruyeVista();
    }

    std::cout << "acaba del todo" << std::endl;

    // clean up (despues de ejeucion)
    delete punteroVentana;
    delete modeloVista;
}
