#ifndef __ModuloIA_
#define __ModuloIA_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>
#include "Tablero.h"
#include "Autorizaciones.h"


enum tipoF
{
    Vac,
    Pe,
    Cab,
    Alf,
    Tor,
    Rein,
    Re
};


class ModuloIA
{
public:
    //Singleton
    static ModuloIA* getCEGUISingletonPtr();
    ~ModuloIA(void);


    bool construyeArbol(TableroPrueba* tableroPadre);




    bool BorraArbol();


  //  TableroPrueba* tableroPadre;

    TableroPrueba* tableroElegido;
    int casillaCambiada;



private:


    bool BlackCheck;
    bool BlackMate;
    bool WhiteCheck;
    bool WhiteMate;
    bool StaleMate;

    int evaulaTablero(const int casillasInt[144], bool turnoN);

   // std::vector<TableroPrueba> vectorTableros;

    int alphaBeta(TableroPrueba* table,int alpha,int beta,const int depthleft );




    //Singleton;
    ModuloIA(void);
    void operator=(const ModuloIA& frameListener ) ;
    ModuloIA(const ModuloIA& ModuloIA);


    short valorFicha(const tipoF tipo);


};


#endif
