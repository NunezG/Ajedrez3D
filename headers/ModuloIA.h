#ifndef __ModuloIA_
#define __ModuloIA_
#include "Modelo/Tablero.h"
#include <algorithm>    // std::for_each
#include <vector>       // std::vector

class ModuloIA
{
public:
    //Singleton
    static ModuloIA* getCEGUISingletonPtr();
    ~ModuloIA(void);


    bool construyeArbol(int* listaCasillas);

    void insert( TableroPrueba *newKey);




private:
    bool evaulaTablero();

    std::vector<TableroPrueba> vectorTableros;

    int alphaBeta(TableroPrueba* table, int alpha, int beta, int depthleft );

    TableroPrueba* siguienteMovimiento(TableroPrueba *newkey);


    void insert_helper( TableroPrueba **root, TableroPrueba *newkey,int profundidad );


    bool mueveTorre();

    bool mueveAlfil();

    bool mueveCaballo();

    bool mueveReina();

    bool muevePeon();

    bool mueveRey();



    TableroPrueba* tablero;

    std::vector<TableroPrueba> generaMovimientos();

    //Singleton;
    ModuloIA(void);
    void operator=(const ModuloIA& frameListener ) ;
    ModuloIA(const ModuloIA& ModuloIA);

};


#endif
