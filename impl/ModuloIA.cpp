#include "../headers/ModuloIA.h"

ModuloIA::ModuloIA()
{  
}

ModuloIA::~ModuloIA()
{

}

ModuloIA* ModuloIA::getCEGUISingletonPtr()
{
    static ModuloIA miFrameListener;
    static ModuloIA* miFrameListenerPtr = &miFrameListener;
    return miFrameListenerPtr;
}


bool ModuloIA::construyeArbol(){

  //  Tablero* nodoPadre = new Tablero();

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






bool ModuloIA::generaMovimientos(){


    //Recorre las fichas en juego y genera tableros con todos los movimientos posibles






}

//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?

