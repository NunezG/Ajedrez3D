#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")
  , mResourcesCfg("resources.cfg")
  , mPantalla(0)
  , salirPulsado(0)
  , tablero(NULL)
   , numJugadores(0)

  //,  jugadores(NULL)




{
    resolucion = new std::string("1024 x 768");
    tablero = new Tablero();

//mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

}
Modelo::~Modelo()
{
    for (int i=0; i<jugadores.size();i++){
        delete jugadores.at(i);
        jugadores.at(i) = NULL;
    }
    jugadores.clear();


}



Tablero* Modelo::getTablero()
{
return tablero;

}

bool Modelo::getApagar()
{

    return mShutDown;

}


bool Modelo::getSalir(){
    return salirPulsado;
}

void Modelo::setSalir(bool salir){
    salirPulsado = salir;
}
int Modelo::getNumPantalla()
{
    return mPantalla;
}


void Modelo::setNumPantalla(int pantalla)
{
    mPantalla = pantalla;
}

void Modelo::construyeMenu()
{
    menu = new ModeloMenu();

}





void Modelo::destruyeTablero(){
   //delete mSceneMgr;

    delete tablero;
    std::cout << "nullea " << std::endl;

    tablero = NULL;


}

void Modelo::destruyeMenu(){

    delete menu;

    std::cout << "nullea " << std::endl;

    menu = NULL;

}
void Modelo::mueveFicha(float time)
{



    std::cout << "mueve " << time<<std::endl;
    std::cout << "mueve " << static_cast<JugadorHumano*> (jugadores.at(0))->esHumano()<<std::endl;

    //Jugador* jug = jugadores[0];


    std::cout << "mueve22 " <<jugadores.at(0)->jugadorNegras<<std::endl;


    jugadores.at(getTablero()->getTurnoNegras())->mueveFicha(time);


}



//tal vez sea mejor una factoria de jugadores
void Modelo::creaJugador(bool blancas, bool humano ){

   // jugadores = new std::vector<Jugador*>();

 //   Jugador** catArray = new Jugador*[200];
   int num = numJugadores;

    std::cout << "CREA JUGADOR "<< num<<std::endl;


    if (humano){
        std::cout << "humano "<<std::endl;
       // JugadorHumano* jug =  static_cast<JugadorHumano*> (jugadores[modelo->numJugadores]);
        jugadores.push_back(new JugadorHumano(getTablero()));
        //static_cast<JugadorHumano*> (modelo->jugadores[num])->setVentana(punteroVentana);

    }
    else {
        std::cout << "maquina "<<std::endl;
        //JugadorArtificial* jug =  static_cast<JugadorArtificial*> (jugadores[modelo->numJugadores]);

        jugadores.push_back(new JugadorArtificial(getTablero()));


    }
   // Jugador* jugador = jugadores[modelo->numJugadores];


    if (blancas)
    {
        std::cout << "jugador blancas "<<std::endl;
        jugadores.at(num)->jugadorNegras = 0;

        std::cout << "jug->jugadorNegras "<<jugadores.at(0)->jugadorNegras<<std::endl;

    }else {
        std::cout << "jugador negras"<<std::endl;

        jugadores.at(num)->jugadorNegras = 1;
        std::cout << "jug->jugadorNegras "<<jugadores.at(1)->jugadorNegras<<std::endl;

    }


    //punteroVentana

    if (numJugadores == 0) jugadorActual = jugadores.at(0);

    numJugadores++;
}

Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}



