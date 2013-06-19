#ifndef __Movimientos_
#define __Movimientos_

#include "ModeloTablero.h"

class Movimientos
{
public:
    static bool generaMovimientos(ModeloTablero* miTablero, tipoFicha tipo);
    static bool pruebaJaqueMate(ModeloTablero* miTablero);

protected:
    static int pruebaCamino(ModeloTablero* miTablero, int salto);

private:
    static bool aplicaMovimiento(ModeloTablero& miTablero,const int casOrigen,const int casDestino);
    static bool mueveFicha(ModeloTablero* miTablero, const int casilla,bool testJaque, tipoFicha tipo);
    static bool mueveTorre(ModeloTablero* miTablero, const int casilla, bool testJaque);
    static bool mueveAlfil(ModeloTablero* miTablero, const int casilla, bool testJaque);
    static bool mueveCaballo(ModeloTablero* miTablero,const int casilla, bool testJaque);
    static bool mueveReina(ModeloTablero* miTablero,const int casilla, bool testJaque);
    static bool muevePeon(ModeloTablero* miTablero,const int casilla, bool testJaque);
    static bool mueveRey(ModeloTablero* miTablero, const int casilla, bool testJaque);
};

#endif
