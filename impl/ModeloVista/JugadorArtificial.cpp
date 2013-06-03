#include "../../headers/ModeloVista/JugadorArtificial.h"

JugadorArtificial::JugadorArtificial(EscenaAjedrez* miEscena) :
    Jugador(miEscena)
  , dificultad(0)

{

}
JugadorArtificial::~JugadorArtificial()
{


}


void JugadorArtificial::mueveFicha(ModeloTablero* miTablero)
{
    //  std::cout << "ARTIF MUEVE FICHA " << std::endl;
    //  std::cout << "TUDRNO DE MITABLERO:" << tablero->turnoN<< std::endl;

    bool result = construyeArbol(miTablero);

    std::cout  << "IFFF " << std::endl;

    if (result == true && miTablero->jugada[0] != -1)
    {
        miTablero->jugadaAutorizada = true;

        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        std::cout  << "ALFABETA HA DEVUELTO EL MOVIMIENTO 1: "<< miTablero->jugada[0] <<   " Y 2 "<< miTablero->jugada[1]<< std::endl;

    }else
    {
        std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;

    }


}



bool JugadorArtificial::casillaSobrevolada(const std::string nombreCasilla)
{
    Jugador::casillaSobrevolada(nombreCasilla);




}

bool JugadorArtificial::activaMovimiento()
{



    tableroModelo->jugadaAutorizada = true;




}





//añade Tablero como parametro y asi se puede integrar al modelo??
void JugadorArtificial::calculaMovimiento()
{

}

bool JugadorArtificial::esHumano()
{
    return false;
}



