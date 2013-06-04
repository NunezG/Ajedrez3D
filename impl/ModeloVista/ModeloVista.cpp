
#include "../../headers/ModeloVista/ModeloVista.h"

//-------------------------------------------------------------------------------------
ModeloVista::ModeloVista():
   mPantalla(0)
  , escena(NULL)
  , mShutDown(0)
  ,  numJugadores(0)
 , modelo(0)


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

void ModeloVista::cambiaTurno()
{
    // escena->tablero->cambiaTurno();

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

    modelo = Modelo::getSingletonPtr();



    escena  = new EscenaAjedrez();

    std::cout << "escc" << std::endl;


    std::cout << "initii" << std::endl;

    iniciaJugadores();
}


//------------------------------------------------------------------------------------
bool ModeloVista::iniciaJugadores()
{




    // mR-aySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
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




    escena->setSceneManager();
    std::cout   << "   iniciamodelo2" << std::endl;

    escena->createCamera();
    std::cout   << "   iniciamodelo3" << std::endl;

    escena->createRayQuery();
    std::cout   << "   iniciamodelo4" << std::endl;

    // escenaAjedrez->createCamera();
    //mInputMan->setTopSpeed(100);

    // Set default mipmap level (NB some APIs ignore this)
    std::cout   << "   iniciamodelo5" << std::endl;


    return true;
}


bool ModeloVista::copiaTablero()
{


    if (modelo->tableroModelo != NULL)
    {

        escena->apagaVentanaEmergente();
        std::cout << "COPIA TABLEROMODELO"<<std::endl;

        modelo->tableroModelo->casillasInt = escena->tablero->traduceTablero();

        modelo->tableroModelo->alPaso = escena->tablero->getAlPaso();

        modelo->tableroModelo->turnoN = escena->tablero->getTurnoNegras();
        std::cout << "COPIA TABLEROMODELO"<<std::endl;

        std::cout << "NTURNO: "<< modelo->tableroModelo->turnoN <<std::endl;
        //  if (tableroModelo->turnoN)
        //     casillas = Calculos::normalizaTablero(casillas);

        //  tableroModelo->jugada = new int[2];
        // tableroModelo->jugada[0] = -1;

    }


}



bool ModeloVista::botonIzquierdo()
{
    if(escena->tablero->getNodoCasillaSobrevolada() != NULL)
    static_cast<Jugador*>(jugadores.at(escena->tablero->getTurnoNegras()))->activaMovimiento();

}



void ModeloVista::miraCambios()
{

    if (jugadores.size() == 2)
    {
        Jugador* jugador = jugadores.at(escena->tablero->getTurnoNegras());
        if(jugador != NULL)
        {
            //  std::cout  << "mueveficha " << std::endl;
            jugador->esperaJugador();


        }


    }
}

