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
    static bool recorreCasillas(ModeloTablero* miTablero, unsigned char salto);

private:
   // bool myfunction (unsigned char* primeraJugada, unsigned char* segundaJugada);

    static void nuevoMovimiento(ModeloTablero *miTablero);

    static bool mueveFicha(ModeloTablero* miTablero, char tipo);
    static bool mueveTorre(ModeloTablero* miTablero);
    static bool mueveAlfil(ModeloTablero* miTablero);
    static bool mueveCaballo(ModeloTablero* miTablero);
    static bool mueveReina(ModeloTablero* miTablero);
    static bool muevePeon(ModeloTablero* miTablero);
    static bool mueveRey(ModeloTablero* miTablero);
};

#endif
