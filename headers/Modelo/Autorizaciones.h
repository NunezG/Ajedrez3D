#ifndef __Autorizaciones_
#define __Autorizaciones_
//#include "Tablero.h"
#include "ModeloTablero.h"




enum tipoFicha
{
    Vacio,
    Peon,
    Caballo,
    Alfil,
    Torre,
    Reina,
    Rey
};


class Autorizaciones
{
public:

    static bool autorizaCasilla(ModeloTablero* miTablero,  tipoFicha tipo, int filaSel, int colSel,  int filaNueva, int colNueva);
    static bool evaluaJaque(int casillasInt[144], bool turnoNegras);
    static void generaMovimientos(ModeloTablero* miTablero);
    static void normalizaTablero(int* tablero);

private:

    static bool autorizaRey(int filaDif, int colDif,  int filaNueva, int colNueva, ModeloTablero* miTablero);
    static bool autorizaReina(int filaDif, int colDif,  int filaNueva, int colNueva,int* miTablero);
    static bool autorizaPeon(int filaDif, int colDif,  int filaNueva, int colNueva,  int filaSel, ModeloTablero* miTablero);
    static bool autorizaAlfil(int filaDif, int colDif,  int filaNueva,int colNueva, int* elTablero);
    static bool autorizaTorre(int filaDif, int colDif,  int filaNueva,int colNueva,int* elTablero);
    static bool autorizaCaballo(int filaDif, int colDif);

    static bool verificaCamino(int distancia,  int filaNueva,int colNueva, int camino, int* casillas);





  //  bool evaluaJaque(const int casillasInt[144], bool turnoNegras);



    static void aplicaMovimiento(ModeloTablero& miTablero,const int casOrigen,const int casDestino);


    static bool mueveTorre(ModeloTablero* miTablero, const int casilla);

    static bool mueveAlfil(ModeloTablero* miTablero, const int casilla);

    static bool mueveCaballo(ModeloTablero* miTablero,const int casilla);

    static bool mueveReina(ModeloTablero* miTablero,const int casilla);

    static void muevePeon(ModeloTablero* miTablero,const int casilla);

    static bool mueveRey(ModeloTablero* miTablero, const int casilla);


};

#endif
