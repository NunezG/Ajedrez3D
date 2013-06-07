#include "../../headers/ModeloVista/JugadorArtificial.h"

JugadorArtificial::JugadorArtificial(EscenaAjedrez* miEscena, Modelo* modelo) :
    Jugador(miEscena, modelo)
  , dificultad(0)

{

}
JugadorArtificial::~JugadorArtificial()
{


}


void JugadorArtificial::mueveFicha()
{
    //  std::cout << "ARTIF MUEVE FICHA " << std::endl;
    //  std::cout << "TUDRNO DE MITABLERO:" << tablero->turnoN<< std::endl;

    bool result = modelo->construyeArbol();

    std::cout  << "IFFF " << std::endl;

    if (result == true && modelo->tableroModelo->jugada[0] != -1)
    {
        activaMovimiento();

        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        std::cout  << "ALFABETA HA DEVUELTO EL MOVIMIENTO 1: "<< modelo->tableroModelo->jugada[0] <<   " Y 2 "<< modelo->tableroModelo->jugada[1]<< std::endl;

    }else
    {
        std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;

    }


}



bool JugadorArtificial::casillaSobrevolada(const std::string nombreCasilla)
{

    std::cout << "CASILLA SOBREVOLADA EN JUGADOR ARTIFICIAL" << std::endl;


    Jugador::casillaSobrevolada(nombreCasilla);




}

bool JugadorArtificial::activaMovimiento()
{



    modelo->jugadaAutorizada = true;




}





//añade Tablero como parametro y asi se puede integrar al modelo??
void JugadorArtificial::calculaMovimiento()
{

}

bool JugadorArtificial::esHumano()
{
    return false;
}



