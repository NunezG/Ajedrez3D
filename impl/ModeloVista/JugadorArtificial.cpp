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
    std::cout << "INICIATURNO HUMANO"<< std::endl;

    std::cout << "CONST ARBOL: "<< modelo->tableroModelo->nodoInicial<< std::endl;
    std::cout << "ORIGEN ANTES: "<< int(modelo->tableroModelo->jugada[0])<< std::endl;
    std::cout << "DEST ANTES: "<< int(modelo->tableroModelo->jugada[1])<< std::endl;

    //delete modelo->tableroModelo->cambiaTurno()

    std::cout << "TABLERO EN ALFABETA vectorJugadas: " << modelo->tableroModelo->vectorJugadas.size()<<std::endl;
    std::cout << "TABLERO EN ALFABETA casillasProtegidas: " << modelo->tableroModelo->casillasProtegidas.size()<<std::endl;

    for(int i=0; i<12;i++)
    {
        std::cout << int(modelo->tableroModelo->casillasInt[(i*12)])<<"    "  << int(modelo->tableroModelo->casillasInt[(i*12)+1])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+2])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+3])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+4])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+5])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+6])<<"    "<<int(modelo->tableroModelo->casillasInt[(i*12)+7]) <<"    " <<int(modelo->tableroModelo->casillasInt[(i*12)+8])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+9])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+10])<<"    " << int(modelo->tableroModelo->casillasInt[(i*12)+11])<<"    " << std::endl;
    }

    int resultado = ArbolBusqueda::alphaBeta(modelo->tableroModelo,-70000, 70000, 2);

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
    posicion inicial;
    posicion final;
    std::cout << "!!!!!!!!!aplicaSeleccionL" << std::endl;




    inicial.Fila = (modelo->jugadaElegida[0]/12)-2;
    inicial.Columna = (modelo->jugadaElegida[0]%12)-2;
    final.Fila = (modelo->jugadaElegida[1]/12)-2;
    final.Columna = (modelo->jugadaElegida[1]%12)-2;
    std::cout << "!!!!!!!!!aplicaSeleccionL2" << std::endl;


    if (modelo->tableroModelo->turnoN)
    {//INVIERTE
          std::cout << "TURNO MEGRAS EN ALFABETA" << std::endl;
         // std::cout << "ORIG DE ALFABETA ANTES DE REVERTIR!!!!: "<< int( modelo->jugadaElegida[0])<< std::endl;
         // std::cout << "DEST DE ALFABETA ANTES DE REVERTIR!!!!: "<< int( modelo->jugadaElegida[1])<< std::endl;

          inicial.Fila = 7-inicial.Fila;
          inicial.Columna =  7-inicial.Columna;
          final.Fila = 7-final.Fila;
          final.Columna =  7-final.Columna;
          std::cout << "!!!!!!!!!aplicaSeleccionL2" << std::endl;



         // modelo->jugadaElegida[0] = 143- modelo->jugadaElegida[0];
         //modelo->jugadaElegida[1] = 143- modelo->jugadaElegida[1];
          // escena->tablero->setCasillaSeleccionada(escena->tablero->getCasillaSeleccionada());
      }



    std::cout << "tableroModelo->jugada[0] " << int(modelo->jugadaElegida[0]) << std::endl;
    std::cout << "tableroModelo->jugadaElegida " << int(modelo->jugadaElegida[1])<< std::endl;
    // std::cout << "tableroModelo->jugada[0] en escenaajedrez al aplicar: "<< tableroModelo->jugada[0] << " tableroModelo->jugada[0]/12: "<< tableroModelo->jugada[0]/12 << " tableroModelo->jugada[0]%12 " << tableroModelo->jugada[0]%12 << std::endl;
    // std::cout << "tableroModelo->jugada[1]en escenaajedrez al aplicar: "<< tableroModelo->jugada[1] << " tableroModelo->jugada[1]/12: "<< tableroModelo->jugada[1]/12 << " tableroModelo->jugada[1]%12 " << tableroModelo->jugada[1]%12 << std::endl;
    std::cout << "SELECT 1 FILA: "<< inicial.Fila <<std::endl;
    std::cout << "SELECT 1 COL: "<< inicial.Columna <<std::endl;

    std::cout << "FINAL 1 FILA: "<< final.Fila <<std::endl;
    std::cout << "FINAL 1 COL: "<< final.Columna <<std::endl;

    escena->getTablero()->setCasillaSeleccionada((inicial.Fila * 8) + inicial.Columna);
    escena->getTablero()->setCasillaSobrevolada((final.Fila* 8) + final.Columna);
    std::cout << "!!!!!!!!!aplicaSeleccionL3" << std::endl;

    return Jugador::aplicaSeleccion();
}

bool JugadorArtificial::esHumano()
{
    return false;
}
