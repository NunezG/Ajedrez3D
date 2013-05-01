#include "../../headers/Modelo/JugadorArtificial.h"


JugadorArtificial::JugadorArtificial(Tablero* tabl) :
    Jugador(tabl)



{

}
JugadorArtificial::~JugadorArtificial()
{


}


void JugadorArtificial::mueveFicha(float frecuencia){


    std::cout << "CALCULA MOVIMIENTO" << std::endl;


calculaMovimiento();


   // tableroInicial.casillas = ...

    //Recorre todas las fichas (negras) del tablero y crea un tablero para cada movimiento de cada ficha (estos seran lso hermanos)

    //Recorre todas las fichas (blancas) de cada tablero creado y crea un tablero para cada movimiento de cada ficha


//    tableroInicial


}


 bool JugadorArtificial::esHumano(){

     return false;
 }


void JugadorArtificial::calculaMovimiento(){

    std::cout << "CALCULA MOVIMIENTO" << std::endl;


    ModuloIA* modulo = ModuloIA::getCEGUISingletonPtr();

    //¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡PASALO A VITA AJEDREZ SOLO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    modulo->construyeArbol(tablero->traduceTablero());


    if (modulo->tableroElegido != NULL)
    {
        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[0]<< std::endl;
        std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[1]<< std::endl;

        mueveIA(modulo->tableroElegido->movimiento[0],modulo->tableroElegido->movimiento[1]);

        modulo->tableroElegido = NULL;

    } else std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;

    std::cout  << "DELETE TABLEROPADRE EN COTROL: "<<  std::endl;

    delete modulo->tableroPadre;

    std::cout  << "NULEA MODULO EN COTROL: "<<  std::endl;
    modulo->tableroPadre = NULL;

    modulo = NULL;

    //   std::cout   << "BORRA TABLERO " << std::endl;


    //  delete modulo->tableroElegido;


    //   std::cout  << "NULLEA TABLERO " << std::endl;


    //  modulo->tableroElegido = NULL;

    //modulo->ejecutaMovimiento(mod);

    //INICIA LA IA PARA CALCULAR LA FICHA A MOVER

    //PRIMERO HAZLO CON EL TABLERO Y LUEGO TE OCUPAS DE LAS FICHAS
    //EMPEZAMOS POR TODOS LOS MOVIMIENTOS DE TODOS LOS PEONES
    //ModuloIA modulo;

    // modelo->escena->tablero->movimientosPeon();
}




int* JugadorArtificial::mueveIA(int origen, int destino)
{
    posicion orig;
    orig.Fila = (origen/12)-2;
    orig.Columna = (origen%12)-2;

    posicion dest;
    dest.Fila = (destino/12)-2;
    dest.Columna = (destino%12)-2;
    //int columanOrigen = (origen%12)-2;
    // int filaOrigen =   ;

    // std::stringstream origenBaseOcho;

    //char letra = tablero->columnas[columanOrigen];


    //std::cout  << "letra: "<< letra << std::endl;

    //origenBaseOcho.str("");

    //origenBaseOcho<< filaOrigen;
    // origenBaseOcho<< letra ;

    // char columna = ;


    //char letraDestino = tablero->columnas[columanDestino];

    //std::cout  << "letraDestino: "<< letraDestino << std::endl;


    //std::stringstream destinoBaseOcho;

    //destinoBaseOcho.str("");

    //destinoBaseOcho<<filaDestino;
    //destinoBaseOcho <<letraDestino;

    //std::cout  << "columanOrigen "<< columanOrigen << std::endl;

    //std::cout  << "filaOrigen " << filaOrigen << std::endl;

    //std::cout  << "origenBaseOcho "<< origenBaseOcho.str() << std::endl;
    //std::cout  << "destinoBaseOcho "<< destinoBaseOcho.str() << std::endl;

    tablero->actualizaTablero(orig,dest );

    tablero->cambiaTurno();
}
