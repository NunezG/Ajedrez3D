#include "../../headers/Modelo/JugadorArtificial.h"

JugadorArtificial::JugadorArtificial(Tablero* tablero) :
    Jugador(tablero)
  , dificultad(0)

{

}
JugadorArtificial::~JugadorArtificial()
{


}


void JugadorArtificial::mueveFicha(float time){



    std::cout << "ARTIF MUEVE FICHA " << std::endl;


    calculaMovimiento();




    // tableroInicial.casillas = ...

    //Recorre todas las fichas (negras) del tablero y crea un tablero para cada movimiento de cada ficha (estos seran lso hermanos)

    //Recorre todas las fichas (blancas) de cada tablero creado y crea un tablero para cada movimiento de cada ficha


    //    tableroInicial


}



//añade Tablero como parametro y asi se puede integrar al modelo??
void JugadorArtificial::calculaMovimiento(){

    std::cout << "CALCULA MOVIMIENTO" << std::endl;

    // Modelo* modelo = Modelo::getSingletonPtr();

    ModuloIA* modulo = ModuloIA::getCEGUISingletonPtr();



    TableroPrueba* tableroPadre = new TableroPrueba();

    std::cout << "TUDRNO DE MITABLERO:" << miTablero->turnoN<< std::endl;


    tableroPadre->turnoN = miTablero->turnoN;



    std::cout << "CONSTRUYE ARBOL CO ALPASO:" << miTablero->alPaso<< std::endl;


    int fila = (miTablero->alPaso/8)+2;
    int col= (miTablero->alPaso%8)+2;

    tableroPadre->casillasInt = new int[144];
    tableroPadre->alPaso = ((fila*12)+col);
    std::cout << "TRADUCIDO:" << tableroPadre->alPaso<< std::endl;

    ////////////////////////////////////////////////////////////////////////////////////7
    tableroPadre->casillasInt = miTablero->traduceTablero();


    //  tablero->Score = 2;
/*
    for (int i = 0; i<144; i++)
    {


        tableroPadre->casillasInt[i] = listaCasillas[i];



    }



   */



    bool result = modulo->construyeArbol(tableroPadre);

    std::cout  << "IFFF " << std::endl;

    if (result == true && modulo->tableroElegido != NULL)
    {
        std::cout  << "HA ENCONTRADO UN RESULTADO Y MUEVE " << std::endl;
        //    std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[0]<< std::endl;
        //    std::cout  << "MAS MOVIMIENTOSS: "<< modulo->tableroElegido->movimiento[1]<< std::endl;

        mueveIA(modulo->tableroElegido->movimiento[0],modulo->tableroElegido->movimiento[1]);

        modulo->tableroElegido = NULL;

    }else{



         std::cout  << "NO HAY FICHA EN CONTROL, SE SUPONE JAQUE MATE O AHOGADO " << std::endl;

    }

    //  std::cout  << "DELETE TABLEROPADRE EN COTROL: "<<  std::endl;

    delete tableroPadre;

    //  std::cout  << "NULEA MODULO EN COTROL: "<<  std::endl;
    tableroPadre = NULL;

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

bool JugadorArtificial::esHumano()
{
    return false;
}



int* JugadorArtificial::mueveIA(int origen, int destino)
{

    std::cout  << "mueve" <<  origen << std::endl;

    std::cout  << "mueve" <<  destino << std::endl;

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

    miTablero->actualizaTablero(orig,dest );

    std::cout  << "cambiaturno " << std::endl;


    miTablero->cambiaTurno();
}


void JugadorArtificial::sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada)
{

}


