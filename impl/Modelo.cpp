#include "../headers/Modelo.h"



Modelo::Modelo() :
    mPluginsCfg("plugins.cfg")




{

mRoot =new Ogre::Root(mPluginsCfg);
mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

}
Modelo::~Modelo()
{


}

bool Modelo::getApagar(){

    return mShutDown;

}


int Modelo::getNumPantalla(){

    return mPantalla;

}

bool Modelo::construyeArbol(){

    Tablero* nodoPadre = new Tablero();

 //   nivel = 0;

    for (int i = 0; i<10; i++){

       for (int i = 0; i<10; i++){
     //   nodoPadre.nodoNuevo() = new Tablero();
      //  nodoPadre.nodoDer = new Tablero();

        //corta la recursividad

       // nodoPadre.nodoIzq.construyeArbol();
      //  nodoPadre.nodoDer.construyeArbol();

    //    nivel++;
       }
    }

}

    bool Modelo::generaMovimientos(){


//Recorre las fichas en juego y genera tableros con todos los movimientos posibles






    }

bool Modelo::creaFichas(){

//tablero = Tablero.
    //entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");


}
