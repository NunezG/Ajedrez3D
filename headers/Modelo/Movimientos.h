#ifndef __Movimientos_
#define __Movimientos_

#include "ModeloTablero.h"

class Movimientos
{
public:
    static bool generaMovimientos(ModeloTablero* miTablero);
    static bool pruebaJaqueMate(ModeloTablero* miTablero);
    static ModeloTablero* aplicaMovimiento(ModeloTablero& miTablero);

protected:
    static bool recorreCasillas(ModeloTablero* miTablero, unsigned char salto);

private:

    static ModeloTablero* nuevoMovimiento(ModeloTablero *miTablero);

    static bool mueveFicha(ModeloTablero* miTablero,bool testJaque, char tipo);
    static bool mueveTorre(ModeloTablero* miTablero);
    static bool mueveAlfil(ModeloTablero* miTablero, bool testJaque);
    static bool mueveCaballo(ModeloTablero* miTablero, bool testJaque);
    static bool mueveReina(ModeloTablero* miTablero, bool testJaque);
    static bool muevePeon(ModeloTablero* miTablero, bool testJaque);
    static bool mueveRey(ModeloTablero* miTablero, bool testJaque);
};

#endif
