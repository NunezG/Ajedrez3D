#ifndef __Movimientos_
#define __Movimientos_
//#include "Tablero.h"
#include "Calculos.h"

class Movimientos : public Calculos
{
public:
    static bool generaMovimientos(ModeloTablero* miTablero, tipoFicha tipo);
    static bool verificaJaqueMate(ModeloTablero* tablero);

    static bool pruebaJaqueMate(ModeloTablero* miTablero);


private:
    static bool aplicaMovimiento(ModeloTablero& miTablero,const int casOrigen,const int casDestino, bool testJaque);


    static bool mueveFicha(ModeloTablero* miTablero, bool testJaque, int casilla, tipoFicha tipo);




  //  static bool miraJaque = false;

    static bool mueveTorre(ModeloTablero* miTablero, const int casilla, bool testJaque);
    static bool mueveAlfil(ModeloTablero* miTablero, const int casilla, bool testJaque);
    static bool mueveCaballo(ModeloTablero* miTablero,const int casilla, bool testJaque);
    static bool mueveReina(ModeloTablero* miTablero,const int casilla, bool testJaque);
    static bool muevePeon(ModeloTablero* miTablero,const int casilla, bool testJaque);
    static bool mueveRey(ModeloTablero* miTablero, const int casilla, bool testJaque);
};

#endif
