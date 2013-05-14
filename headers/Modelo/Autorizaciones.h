#ifndef __Autorizaciones_
#define __Autorizaciones_
#include "Tablero.h"






class Autorizaciones
{
public:

    static bool autorizaCasilla(Tablero* miTablero,  tipoFicha tipo,  posicion nodoSeleccionado,  posicion nodoSobrevolado);
    static bool evaluaJaque(int casillasInt[144], bool turnoNegras);
    static void generaMovimientos(TableroPrueba* miTablero);
    static void normalizaTablero(int* tablero);

private:

    static bool autorizaRey(posicion diferencia, posicion nodoSobrevolado, TableroPrueba* miTablero);
    static bool autorizaReina(posicion diferencia, posicion nodoSobrevolado,int* miTablero);
    static bool autorizaPeon(posicion diferencia, posicion nodoSobrevolado, posicion seleccionado,TableroPrueba* miTablero);
    static bool autorizaAlfil(posicion diferencia, posicion nodoSobrevolado, int* elTablero);
    static bool autorizaTorre(posicion diferencia, posicion nodoSobrevolado, int* elTablero);
    static bool autorizaCaballo(posicion diferencia);

    static bool verificaCamino(int distancia, posicion _nodoNuevo, int camino, int* casillas);





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
