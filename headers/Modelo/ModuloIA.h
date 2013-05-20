#ifndef __ModuloIA_
#define __ModuloIA_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>
//#include "Tablero.h"
#include "Autorizaciones.h"



class ModuloIA
{
public:
    //Singleton
    static ModuloIA* getCEGUISingletonPtr();
    ~ModuloIA(void);



  //  ModeloTablero* tableroPadre;

    int casillaCambiada;



private:


    bool BlackCheck;
    bool BlackMate;
    bool WhiteCheck;
    bool WhiteMate;
    bool StaleMate;


   // std::vector<ModeloTablero> vectorTableros;







    //Singleton;
    ModuloIA(void);
    void operator=(const ModuloIA& frameListener ) ;
    ModuloIA(const ModuloIA& ModuloIA);



};


#endif
