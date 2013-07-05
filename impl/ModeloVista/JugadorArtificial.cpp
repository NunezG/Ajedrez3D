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
    std::cout << "INICIATURNO ARTIFICIAL"<< std::endl;

    if (construyeArbol())
    {

        // activaMovimiento();

        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        std::cout  << "ALFABETA HA DEVUELTO EL MOVIMIENTO 1: "<< int(modelo->tableroModelo->jugada[0]) <<   " Y 2 "<< int(modelo->tableroModelo->jugada[1])<< std::endl;

    }else
    {
        std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;
        return false;

    }

   return true;
}
bool JugadorArtificial::construyeArbol()
{
    std::cout << "CONST ARBOL: "<< modelo->tableroModelo->nodoInicial<< std::endl;
    std::cout << "ORIGEN ANTES: "<< int(modelo->tableroModelo->jugada[0])<< std::endl;
    std::cout << "DEST ANTES: "<< int(modelo->tableroModelo->jugada[1])<< std::endl;

    //delete modelo->tableroModelo->cambiaTurno()

    for(int i=0; i<12;i++)
    {
        std::cout << int(modelo->tableroModelo->casillasInt[(i*12)])<<"    "  << int(modelo->tableroModelo->casillasInt[(i*12)+1])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+2])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+3])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+4])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+5])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+6])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+7]) <<"    " <<int(modelo->tableroModelo->casillasInt[(i*12)+8])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+9])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+10])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+11])<<"    " << std::endl;
    }
    std::cout << "TABLERO EN ALFABETA" << std::endl;


    int resultado = ArbolBusqueda::alphaBeta(modelo->tableroModelo,-70000, 70000, 3);




    std::cout << "FIN CONST ARBOL"<< std::endl;
    std::cout << "ORIGEN DESPUES DE ALFABETA!!!!: "<< int(modelo->jugadaElegida[0])<< std::endl;
    std::cout << "CASILLA ORIGEN DESPUES DE ALFABETA!!!!: "<<     int(modelo->tableroModelo->casillasInt[modelo->jugadaElegida[0]]) << std::endl;

    std::cout << "DEST REAL DE ALFABETA!!!!: "<< int(modelo->jugadaElegida[1])<< std::endl;
    std::cout << "CASILLA DEST DESPUES DE ALFABETA!!!!: "<<     int(modelo->tableroModelo->casillasInt[modelo->jugadaElegida[1]]) << std::endl;

    std::cout << "RESULTADO DE ALFABETA: "<< resultado<< std::endl;

    // resultado = resultado;

   // std::cout << "RESULTADO DE ALFABETA DESPUES: "<< resultado<< std::endl;
 //   std::cout << "NUMERO NODOS TABLERO INICIAL: "<< tableroModelo->vectorMov.size()<< std::endl;

    if (modelo->jugadaElegida[0] == modelo->jugadaElegida[1])
    {//SIN RESULTADO
        std::cout << "NO HAY TABLEROS EN EL VECTOR POR LO QUE ES UN JAQUE MATE O UN AHOGADO, HABRA QUE DIFERENCIAR"<< std::endl;
        return false;
    }

    return true;
}

bool JugadorArtificial::aplicaSeleccion()
{


    return Jugador::aplicaSeleccion();
}


bool JugadorArtificial::esHumano()
{
    return false;
}
