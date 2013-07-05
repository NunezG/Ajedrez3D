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
    //0: para nada encontrado, 1: para ficha amiga encontrada, 2: para ficha enemiga encontrada
    static int recorreCasillas(ModeloTablero* miTablero, unsigned char salto);

private:

    static ModeloTablero* nuevoMovimiento(ModeloTablero *miTablero);

    static int mueveFicha(ModeloTablero* miTablero, char tipo);
    static int mueveTorre(ModeloTablero* miTablero);
    static int mueveAlfil(ModeloTablero* miTablero);
    static int mueveCaballo(ModeloTablero* miTablero);
    static int mueveReina(ModeloTablero* miTablero);
    static int muevePeon(ModeloTablero* miTablero);
    static int mueveRey(ModeloTablero* miTablero);
};

#endif
