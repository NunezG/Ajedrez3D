#ifndef __FichaCaballo_
#define __FichaCaballo_

#include "Ficha.h"


class FichaCaballo : Ficha
{
public:

    ~FichaCaballo(void);
    FichaCaballo(bool esNegra);

private:  
    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);

};

#endif
