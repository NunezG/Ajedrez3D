#include "../../headers/ModeloVista/JugadorArtificial.h"

JugadorArtificial::JugadorArtificial(EscenaAjedrez* miEscena, Modelo* modelo) :
    Jugador(miEscena, modelo)
  , dificultad(0)
{    
}
JugadorArtificial::~JugadorArtificial()
{
}

bool JugadorArtificial::botonIzquierdo(CEGUI::Vector2 pos)
{  
}

bool JugadorArtificial::botonDerecho()
{ 
}

bool JugadorArtificial::iniciaTurno()
{

    bool result = modelo->construyeArbol();

    if (result == true && modelo->tableroModelo->jugada[0] != -1)
    {
        // activaMovimiento();

        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        std::cout  << "ALFABETA HA DEVUELTO EL MOVIMIENTO 1: "<< modelo->tableroModelo->jugada[0] <<   " Y 2 "<< modelo->tableroModelo->jugada[1]<< std::endl;

    }else
    {
        std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;
    }

   return true;
}


int JugadorArtificial::aplicaSeleccion()
{
    posicion inicial;
    posicion final;

    inicial.Fila = (modelo->tableroModelo->jugada[0]/12)-2;
    inicial.Columna = (modelo->tableroModelo->jugada[0]%12)-2;
    final.Fila = (modelo->tableroModelo->jugada[1]/12)-2;
    final.Columna = (modelo->tableroModelo->jugada[1]%12)-2;

    std::cout << "tableroModelo->jugada[0] " << modelo->tableroModelo->jugada[0]<< std::endl;
    std::cout << "tableroModelo->jugada[1] " << modelo->tableroModelo->jugada[1]<< std::endl;
    // std::cout << "tableroModelo->jugada[0] en escenaajedrez al aplicar: "<< tableroModelo->jugada[0] << " tableroModelo->jugada[0]/12: "<< tableroModelo->jugada[0]/12 << " tableroModelo->jugada[0]%12 " << tableroModelo->jugada[0]%12 << std::endl;
    // std::cout << "tableroModelo->jugada[1]en escenaajedrez al aplicar: "<< tableroModelo->jugada[1] << " tableroModelo->jugada[1]/12: "<< tableroModelo->jugada[1]/12 << " tableroModelo->jugada[1]%12 " << tableroModelo->jugada[1]%12 << std::endl;
    std::cout << "SELECT 1 FILA: "<< (inicial.Fila*8)+inicial.Columna <<std::endl;
    escena->getTablero()->setCasillaSeleccionada((inicial.Fila * 8) + inicial.Columna);
    escena->getTablero()->setCasillaSobrevolada((final.Fila* 8) + final.Columna);

    Jugador::aplicaSeleccion();
}


bool JugadorArtificial::esHumano()
{
    return false;
}
