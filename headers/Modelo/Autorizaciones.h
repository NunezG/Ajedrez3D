#ifndef __Autorizaciones_
#define __Autorizaciones_
#include "Tablero.h"

class Autorizaciones
{
public:

    static bool autorizaCasilla(Tablero* miTablero);
    static bool evaluaJaque(int casillasInt[144], bool turnoNegras);

private:

    static bool autorizaRey(posicion diferencia, posicion nodoSobrevolado, Tablero* miTablero, bool turnoNegras);
    static bool autorizaReina(posicion diferencia, posicion nodoSobrevolado,Tablero* miTablero);
    static bool autorizaPeon(posicion diferencia, Casilla* nodoSobrevolado, posicion seleccionado, bool turnoNegras,Tablero* miTablero);
    static bool autorizaAlfil(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero);
    static bool autorizaTorre(posicion diferencia, posicion nodoSobrevolado, Tablero* elTablero);
    static bool autorizaCaballo(posicion diferencia);

    static bool verificaCamino(int distancia, posicion _nodoNuevo, int camino, Tablero* elTablero);
};

#endif
