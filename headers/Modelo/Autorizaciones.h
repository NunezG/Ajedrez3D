#ifndef __Autorizaciones_
#define __Autorizaciones_
#include "Tablero.h"






class Autorizaciones
{
public:

    static bool autorizaCasilla(Tablero* miTablero);
    static bool evaluaJaque(int casillasInt[144], bool turnoNegras);
    static void generaMovimientos(TableroPrueba* miTablero);

private:

    static bool autorizaRey(posicion diferencia, posicion nodoSobrevolado, Tablero* miTablero);
    static bool autorizaReina(posicion diferencia, posicion nodoSobrevolado,Tablero* miTablero);
    static bool autorizaPeon(posicion diferencia, Casilla* nodoSobrevolado, posicion seleccionado,Tablero* miTablero);
    static bool autorizaAlfil(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero);
    static bool autorizaTorre(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero);
    static bool autorizaCaballo(posicion diferencia);

    static bool verificaCamino(int distancia, posicion _nodoNuevo, int camino, Tablero* elTablero);



    static void normalizaTablero(int* tablero);


  //  bool evaluaJaque(const int casillasInt[144], bool turnoNegras);



    static void aplicaMovimiento(TableroPrueba& miTablero,const int casOrigen,const int casDestino);


    static bool mueveTorre(TableroPrueba* miTablero, const int casilla);

    static bool mueveAlfil(TableroPrueba* miTablero, const int casilla);

    static bool mueveCaballo(TableroPrueba* miTablero,const int casilla);

    static bool mueveReina(TableroPrueba* miTablero,const int casilla);

    static void muevePeon(TableroPrueba* miTablero,const int casilla);

    static bool mueveRey(TableroPrueba* miTablero, const int casilla);


};

#endif
