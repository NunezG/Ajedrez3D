#include "../../headers/ModeloVista/ModeloVista.h"

//-------------------------------------------------------------------------------------
ModeloVista::ModeloVista():
    mPantalla(0)
  , escena(0)
  , mShutDown(0)
  ,  numJugadores(0)
  , modelo(0)
  , JugadorActivo(0)

{
    resolucion = "800 x 600";
}

//-------------------------------------------------------------------------------------
ModeloVista::~ModeloVista(void)
{
    for (int i=0; i<jugadores.size();i++)
    {
        delete jugadores.at(i);
        jugadores.at(i) = NULL;
    }
    jugadores.clear();

    // if (mInputMan) delete mInputMan;
}

bool ModeloVista::getApagar()
{
    return mShutDown;
}

void ModeloVista::setApagar(bool apaga)
{

    mShutDown = apaga;

}

int ModeloVista::getNumPantalla()
{
    return mPantalla;
}

void ModeloVista::setNumPantalla(int pantalla)
{
    mPantalla = pantalla;
}

bool ModeloVista::generaJugadores()
{
    creaJugador(true, true);

    if (getNumPantalla() == 1)
    {
        creaJugador(false, true);
    }else
    {
        creaJugador(false, false);
    }
}

//tal vez sea mejor una factoria de jugadores
void ModeloVista::creaJugador(bool blancas, bool humano)
{
    int num = numJugadores;

    //HAY QUE CAMBIAR LO DE MODELOTABKERO PORQUE LOS JUGADORES ESTAN EN UN VECTOR Y ESE ES EL PROBLEMA
    if (humano)
    {
        std::cout << "CREA UN JUGADOR HUMANO" << std::endl;

        jugadores.push_back(new JugadorHumano(escena, modelo));
    }
    else
    {
        std::cout << "CREA UN JUGADOR ARTIFICIAL" << std::endl;

        jugadores.push_back(new JugadorArtificial(escena, modelo));
    }

    if (blancas)
    {
        jugadores.at(num)->jugadorNegras = 0;
        JugadorActivo = jugadores.at(num);
    }
    else
    {
        jugadores.at(num)->jugadorNegras = 1;
    }
    numJugadores++;
}


bool ModeloVista::creaModeloTablero()
{


    if (modelo->tableroModelo != NULL)
    {
        modelo->tableroModelo->casillasInt = traduceTablero();
        modelo->tableroModelo->alPaso = escena->getTablero()->getAlPaso();
        modelo->tableroModelo->turnoN = escena->getTablero()->getTurnoNegras();
    }
}

bool ModeloVista::botonIzquierdo()
{

    if(modelo->tableroModelo->jugada[1] > 0)
        aplicaCambio();

    if (!JugadorActivo->esHumano())
    {
        static_cast<JugadorArtificial*>(JugadorActivo)->mueveIA();
        botonIzquierdo();
    }
}

int* ModeloVista::traduceTablero()
{
    int numCasilla = 0;
    int* casillasInt = new int[144];

    //AÑADE LOS BORDES
    for (int i = 0; i<12; i++)
    {
        for (int y = 0; y<12; y++)
        {
            if((i > 9)
                    || (y > 9)
                    || (i < 2)
                    || (y < 2))
            {
                casillasInt[(i*12)+y] = 99;

            }else
            {
                Casilla* casilla= static_cast<Casilla*>(escena->getTablero()->getHijo(((i-2)*8)+y-2));
                int filaTemp = casilla->getPosicion().Fila;
                int columnaTemp = casilla->getPosicion().Columna;
                int numeroCasilla = 24+(filaTemp*12)+columnaTemp+2;

                if (!casilla->sinHijos())
                {
                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //ESTO ASEGURA QUE LAS FICHAS CORRESPONDIENTES AL TURNO SEAN POSITIVAS
                    if (ficha->esNegra && !escena->getTablero()->getTurnoNegras() || !ficha->esNegra && escena->getTablero()->getTurnoNegras())
                    {
                        casillasInt[numeroCasilla] = -ficha->tipo_Ficha;;
                    }
                    else casillasInt[numeroCasilla] = ficha->tipo_Ficha;

                }else casillasInt[numeroCasilla] = 0;
                numCasilla++;
            }
        }
    }

    std::cout << "traducido" << std::endl;
    for(int i=0; i<12;i++)
    {
        std::cout  << casillasInt[(i*12)+2]<<"    "<<casillasInt[(i*12)+3]<<"    "<<casillasInt[(i*12)+4]<<"    "<<casillasInt[(i*12)+5]<<"    "<<casillasInt[(i*12)+6]<<"    "<<casillasInt[(i*12)+7] <<"    " <<casillasInt[(i*12)+8]<<"    " << casillasInt[(i*12)+9]<<"    " << std::endl;
    }
    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );

    return casillasInt;
}

bool ModeloVista::seleccionaFichaEnPosicion(CEGUI::Vector2 pos)
{    
    Tablero* tablero = escena->getTablero();


    tablero->fichaSeleccionada = false;

    if (tablero->getNodoCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...
        Ficha* ficha = static_cast<Ficha*>(tablero->getNodoCasillaSeleccionada()->getHijo(0));
        ficha->getNodoOgre()->showBoundingBox(false);
        tablero->setNodoCasillaSeleccionada(-1);
    }

    Casilla* casilla = static_cast<Casilla*>(tablero->getHijo(escena->encuentraCasillaSobrevolada(pos)));

    if (casilla != NULL && !casilla->sinHijos())
    {

        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));
        if ((tablero->getTurnoNegras()
             && ficha->esNegra)
                || (!tablero->getTurnoNegras()
                    && !ficha->esNegra))
        {
            tablero->setNodoCasillaSeleccionada(casilla);
            ficha->getNodoOgre()->showBoundingBox(true);
            tablero->fichaSeleccionada = true;
            return true;
        }
    }
    return false;
}

bool ModeloVista::aplicaCambio()
{
    Tablero* tablero = escena->getTablero();


    std::cout << "APLICA YA EL MOVIMIENTO DEFINITIVO" << std::endl;

    if (tablero->getNodoCasillaSobrevolada() != NULL)
        tablero->getNodoCasillaSobrevolada()->apagaCasilla();

    escena->apagaVentanaEmergente();
    tablero->fichaSeleccionada = false;

    int filaSel;
    int colSel;
    int filaNueva;
    int colNueva;

    std::cout << "tableroModelo->jugada[0] " << modelo->tableroModelo->jugada[0]<< std::endl;
    std::cout << "tableroModelo->jugada[1] " << modelo->tableroModelo->jugada[1]<< std::endl;

    filaSel = (modelo->tableroModelo->jugada[0]/12)-2;
    colSel = (modelo->tableroModelo->jugada[0]%12)-2;
    filaNueva = (modelo->tableroModelo->jugada[1]/12)-2;
    colNueva = (modelo->tableroModelo->jugada[1]%12)-2;

    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    int resultado = JugadorActivo->aplicaSeleccion();

    if (tablero->getNodoCasillaSeleccionada() == NULL)
    {    //JUGADOR ARTIFICIAL

        // std::cout << "tableroModelo->jugada[0] en escenaajedrez al aplicar: "<< tableroModelo->jugada[0] << " tableroModelo->jugada[0]/12: "<< tableroModelo->jugada[0]/12 << " tableroModelo->jugada[0]%12 " << tableroModelo->jugada[0]%12 << std::endl;
        // std::cout << "tableroModelo->jugada[1]en escenaajedrez al aplicar: "<< tableroModelo->jugada[1] << " tableroModelo->jugada[1]/12: "<< tableroModelo->jugada[1]/12 << " tableroModelo->jugada[1]%12 " << tableroModelo->jugada[1]%12 << std::endl;
        std::cout << "SELECT 1 FILA: "<< (filaSel*8)+colSel <<std::endl;

        tablero->setNodoCasillaSeleccionada((filaSel * 8) + colSel);

        std::cout << "nombre: "<< tablero->getNodoCasillaSeleccionada()->getNombre()<<std::endl;

        tablero->setNodoCasillaSobrevolada((filaNueva * 8) + colNueva);
    }

    tablero->actualizaTablero();

    if (resultado == 1 || resultado == 4)
    {//FICHA MOVIDA

        if (resultado == 4)
        {//JAQUE AL REY
            escena->muestraVentanaEmergente("Jaque");
        }
        //   tablero->actualizaTablero();

        if (static_cast<Jugador*>(jugadores[0])->esHumano() && static_cast<Jugador*>(jugadores[1])->esHumano())
            tablero->rotacionCamara = Ogre::Real(180.0f);

        //COMPRUEBA JAQUE MATE

        JugadorActivo->promocionaPeon();

        tablero->setNodoCasillaSobrevolada(-1);
        tablero->setNodoCasillaSeleccionada(-1);

        std::cout << "fin cambia "<< std::endl;

        tablero->turnoNegras = !tablero->turnoNegras;

        modelo->tableroModelo->turnoN = !modelo->tableroModelo->turnoN;

        //NORMALIZA EL TABLERO PARA EL CAMBIO DE TURNO
        for(int i=0; i<144;i++)
        {
            //NORMALIZA EL TABLERO, CAMBIA EL SIGNO DE LAS FICHAS
            if (modelo->tableroModelo->casillasInt[i] != 0 && modelo->tableroModelo->casillasInt[i] != 99)
            {
                modelo->tableroModelo->casillasInt[i] = -modelo->tableroModelo->casillasInt[i];
            }
        }
        JugadorActivo = jugadores.at(tablero->getTurnoNegras());

        return true;
    }
    else if (resultado == 2)
    {//JAQUE MATE
        escena->muestraVentanaEmergente("JaqueMate");
    }
    else if (resultado == 3)
    {
        //REY AHOGADO (TABLAS)
        std::cout << "REY AHOGADO (TABLAS)!!"<< std::endl;
        escena->muestraVentanaEmergente("Tablas");
    }
    return false;
}
