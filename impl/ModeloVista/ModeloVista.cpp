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
void ModeloVista::cambiaPantalla(int pantallaNueva)
{
    setNumPantalla(pantallaNueva);
    setSalir(true);
}

int ModeloVista::getNumPantalla()
{
    return mPantalla;
}

void ModeloVista::setNumPantalla(int pantalla)
{
    mPantalla = pantalla;
}

void ModeloVista::setSalir(bool salir)
{
    reiniciar = salir;
}


bool ModeloVista::getSalir()
{
    return reiniciar;
}

//------------------------------------------------------------------------------------
bool ModeloVista::iniciaModeloAjedrez()
{
    std::cout << "pes" << std::endl;
    std::cout << "initii" << std::endl;
}

bool ModeloVista::generaJugadores()
{

    creaJugador(true, true);

    //jugadorActual = modelo->jugadores.at(0);

    if (getNumPantalla() == 1)
    {
        creaJugador(false, true);
    }else
    {
        creaJugador(false, false);
    }
}

//bool ModeloVista::reiniciaVista()
//{
//  if(getNumPantalla() > 0)
// {
// iniciaModeloAjedrez();

//resetOgre();

//creaVista();

//initOgre();
//  modeloVista->preparaEscena();

//  escena->createViewports(vista->mWindow);

// CEGUIResources();

//  escena->createScene();

//   Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);

//return false;
// Load resources
// loadResources();
//}
//}

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

bool ModeloVista::preparaEscena()
{
    std::cout   << "   iniciamodelo1" << std::endl;

    //   escena->setSceneManager();
    std::cout   << "   iniciamodelo2" << std::endl;

    std::cout   << "   iniciamodelo3" << std::endl;

    std::cout   << "   iniciamodelo4" << std::endl;

    // escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);

    // Set default mipmap level (NB some APIs ignore this)
    std::cout   << "   iniciamodelo5" << std::endl;

    return true;
}

bool ModeloVista::creaModeloTablero()
{
    if (modelo->tableroModelo != NULL)
    {

        escena->apagaVentanaEmergente();

        modelo->tableroModelo->casillasInt = traduceTablero();

        modelo->tableroModelo->alPaso = escena->tablero->getAlPaso();

        modelo->tableroModelo->turnoN = escena->tablero->getTurnoNegras();

        std::cout << "NTURNO: "<< modelo->tableroModelo->turnoN <<std::endl;
        //  if (tableroModelo->turnoN)
        //     casillas = Calculos::normalizaTablero(casillas);

        //  tableroModelo->jugada = new int[2];
        // tableroModelo->jugada[0] = -1;
    }
}

bool ModeloVista::botonIzquierdo()
{

    if(modelo->tableroModelo->jugada[1] > 0)
         aplicaCambio();

    if (!JugadorActivo->esHumano())
    {
        JugadorActivo->mueveFicha();
        botonIzquierdo();
    }
}

void ModeloVista::miraCambios()
{
    //Jugador* jugador = jugadores.at(escena->tablero->getTurnoNegras());
    if(JugadorActivo != NULL)
    {
        std::cout  << "mueveficha " << std::endl;
        JugadorActivo->esperaJugador();
    }
}

int* ModeloVista::traduceTablero()
{
    //ESTO SE PUEDE CAMBIAR MUCHO
    //  int *casillas = new int[144];
    int numCasilla = 0;

    //  ModeloTablero* nuevoModeloT = new ModeloTablero();

    int* casillasInt = new int[144];

    //    Ogre::SceneNode* nodoTest = tablero->nodoCasillero;

    // Ogre::Node::ChildNodeIterator iterator = _nodoNuevo->getChildIterator();
    // Ogre::Node::ChildNodeIterator iterator = getNodoOgre()->getChildIterator();

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
                Casilla* casilla= static_cast<Casilla*>(escena->tablero->getHijo(((i-2)*8)+y-2));

                int filaTemp = casilla->getPosicion().Fila;

                int columnaTemp = casilla->getPosicion().Columna;

                int numeroCasilla = 24+(filaTemp*12)+columnaTemp+2;

                if (!casilla->sinHijos())
                {
                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //Ogre::SceneNode* nodoFichaTemporal =  static_cast<Ogre::SceneNode*>(nodoCasillaTemporal->getChild(0));

                    //Ogre::Entity* entidadFichaTemporal =  static_cast<Ogre::Entity*>(nodoFichaTemporal->getAttachedObject(0));

                    //ESTO ASEGURA QUE LAS FICHAS CORRESPONDIENTES AL TURNO SEAN POSITIVAS
                    if (ficha->esNegra && !escena->tablero->getTurnoNegras() || !ficha->esNegra && escena->tablero->getTurnoNegras())
                    {
                        casillasInt[numeroCasilla] = -ficha->tipo_Ficha;;
                    }else casillasInt[numeroCasilla] = ficha->tipo_Ficha;

                    //  casillas[numCasilla] = traduceFicha(entidadFichaTemporal->getName()[4]);

                }else casillasInt[numeroCasilla] = 0;
                // casillas[numCasilla] = 0;
                numCasilla++;
            }
            //  std::cout << tablero->casillasInt[((i-2)*8)+y-2] << std::endl;
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
    std::cout << "SELECCIONA FICHA "<<std::endl;

    std::cout << "esc "<< escena->esModoCamara() <<std::endl;

    std::cout << "tab "<< escena->tablero<<std::endl;

    escena->tablero->fichaSeleccionada = false;

    std::cout << "SELECCCHA "<<std::endl;

    if (escena->tablero->getNodoCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...
        std::cout << "SELEfifiifififiHA "<<std::endl;

        Ficha* ficha = static_cast<Ficha*>(escena->tablero->getNodoCasillaSeleccionada()->getHijo(0));
        ficha->getNodoOgre()->showBoundingBox(false);
        escena->tablero->setNodoCasillaSeleccionada(-1);
    }
    std::cout << "SELECCIONA FICHA  2"<<std::endl;

   Casilla* casilla = static_cast<Casilla*>(escena->tablero->getHijo(escena->encuentraCasillaSobrevolada(pos)));



    std::cout << "SELECCIONA FICHA 3 "<<std::endl;


    if (casilla != NULL && !casilla->sinHijos())
    {

        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

        std::cout << "SELECCIONA FICHA INTERIOR 1"<<std::endl;
        if ((escena->tablero->getTurnoNegras()
             && ficha->esNegra)
                || (!escena->tablero->getTurnoNegras() && !ficha->esNegra))
        {

            std::cout << "SELECCIONA FICHA INTERIOR 2"<<std::endl;


            std::cout << "SELECCIONA :" << casilla->getNombre()  <<std::endl;

            escena->tablero->setNodoCasillaSeleccionada(casilla);

            ficha->getNodoOgre()->showBoundingBox(true);
            escena->tablero->fichaSeleccionada = true;
            return true;
        }
        std::cout << "SALE SELECCIONA FICHA INTERIOR "<<std::endl;
    }
    std::cout << "SELECCIONA FICHA 4 "<<std::endl;
    return false;
}

bool ModeloVista::aplicaCambio()
{
    std::cout << "APLICA YA EL MOVIMIENTO DEFINITIVO" << std::endl;

    if (escena->tablero->getNodoCasillaSobrevolada() != NULL)
        escena->tablero->getNodoCasillaSobrevolada()->apagaCasilla();

    escena->tablero->fichaSeleccionada = false;

    // ModeloTablero* tableroModelo = new ModeloTablero();

    //  tableroModelo->casillasInt = tablero->traduceTablero();

    //  tableroModelo->alPaso = tablero->getAlPaso();

    //  tableroModelo->turnoN = tablero->getTurnoNegras();

    int filaSel;
    int colSel;
    int filaNueva;
    int colNueva;

    /* if (tableroModelo->movimiento == NULL)
    {

        filaSel=tablero->getNodoCasillaSeleccionada()->getPosicion().Fila;

        colSel = tablero->getNodoCasillaSeleccionada()->getPosicion().Columna;

        filaNueva = tablero->getNodoCasillaSobrevolada()->getPosicion().Fila;

        colNueva = tablero->getNodoCasillaSobrevolada()->getPosicion().Columna;

    }else
    {*/
    std::cout << "tableroModelo->jugada[0] " << modelo->tableroModelo->jugada[0]<< std::endl;
    std::cout << "tableroModelo->jugada[1] " << modelo->tableroModelo->jugada[1]<< std::endl;

    filaSel = (modelo->tableroModelo->jugada[0]/12)-2;
    colSel = (modelo->tableroModelo->jugada[0]%12)-2;
    filaNueva = (modelo->tableroModelo->jugada[1]/12)-2;
    colNueva = (modelo->tableroModelo->jugada[1]%12)-2;

    std::cout << " ficha que se va a mover: " <<modelo->tableroModelo->casillasInt[modelo->tableroModelo->jugada[0]]<< std::endl;
    // }
    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    int resultado = JugadorActivo->aplicaSeleccion();

    std::cout << "ACTUALIZA TABLERO1" << std::endl;

    // delete tableroModelo;
    //  std::cout  << "nullea tablromov" << std::endl;
    // tableroModelo = NULL;
    //  std::cout  << "ACABA EL MOV!!! " << std::endl;

    //JUGADOR ARTIFICIAL
    if (escena->tablero->getNodoCasillaSeleccionada() == NULL)
    {
        // std::cout << "tableroModelo->jugada[0] en escenaajedrez al aplicar: "<< tableroModelo->jugada[0] << " tableroModelo->jugada[0]/12: "<< tableroModelo->jugada[0]/12 << " tableroModelo->jugada[0]%12 " << tableroModelo->jugada[0]%12 << std::endl;
        // std::cout << "tableroModelo->jugada[1]en escenaajedrez al aplicar: "<< tableroModelo->jugada[1] << " tableroModelo->jugada[1]/12: "<< tableroModelo->jugada[1]/12 << " tableroModelo->jugada[1]%12 " << tableroModelo->jugada[1]%12 << std::endl;

        std::cout << "SELECT 1 FILA: "<< (filaSel*8)+colSel <<std::endl;

        escena->tablero->setNodoCasillaSeleccionada((filaSel * 8) + colSel);

        std::cout << "nombre: "<< escena->tablero->getNodoCasillaSeleccionada()->getNombre()<<std::endl;

        //    seleccionaFichaEnPosicion(filaSel, colSel);

        std::cout << "SELECT 2 FILA: "<< (filaNueva * 8) + colNueva <<std::endl;

        escena->tablero->setNodoCasillaSobrevolada((filaNueva * 8) + colNueva);

        std::cout << "nombre: "<< escena->tablero->getNodoCasillaSobrevolada()->getNombre()<<std::endl;

        //tablero->setNodoCasillaSobrevolada(seleccionaCasillaEnPosicion(filaNueva, colNueva));
    }
    std::cout << "ACTUALIZA TABLERO2" << resultado<<std::endl;

    escena->tablero->actualizaTablero();

    if (resultado == 1 || resultado == 4)
    {//FICHA MOVIDA

        if (resultado == 4)
        {//JAQUE AL REY
            escena->muestraVentanaEmergente("Jaque");
        }
        //   tablero->actualizaTablero();

        escena->tablero->rotacionCamara = Ogre::Real(180.0f);
        std::cout << "cambia turno" << std::endl;

        //CAMBIA TURNO
        //NOTIFICAR A LAS VISTAS?? AL FUNCIONAR EN BUCLE EN REALIDAD NO HACE FALTA NOTIFICAR
        //COMPRUEBA JAQUE MATE

        JugadorActivo->promocionaPeon();

        escena->tablero->setNodoCasillaSobrevolada(-1);
        escena->tablero->setNodoCasillaSeleccionada(-1);

        std::cout << "fin cambia "<< std::endl;

        escena->tablero->turnoNegras = !escena->tablero->turnoNegras;

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

//


        JugadorActivo = jugadores.at(escena->tablero->getTurnoNegras());
        std::cout << "sale" << std::endl;

        return true;
    }
    else if (resultado == 2)
    {//JAQUE MATE
        std::cout << "JAQUE EVALUADO!!"<< std::endl;
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
