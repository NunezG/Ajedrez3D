#ifndef __Movimientos_
#define __Movimientos_
//#include "Tablero.h"
#include "Calculos.h"





class Movimientos : public Calculos
{
public:
    static void generaMovimientos(ModeloTablero* miTablero);

private:

    static void aplicaMovimiento(ModeloTablero& miTablero,const int casOrigen,const int casDestino);
    static bool mueveTorre(ModeloTablero* miTablero, const int casilla);
    static bool mueveAlfil(ModeloTablero* miTablero, const int casilla);
    static bool mueveCaballo(ModeloTablero* miTablero,const int casilla);
    static bool mueveReina(ModeloTablero* miTablero,const int casilla);
    static void muevePeon(ModeloTablero* miTablero,const int casilla);
    static bool mueveRey(ModeloTablero* miTablero, const int casilla);
};

#endif
