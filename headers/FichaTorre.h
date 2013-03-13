#ifndef __FichaTorre_
#define __FichaTorre_

#include "Ficha.h"

class FichaTorre : Ficha
{
public:

    ~FichaTorre(void);
    FichaTorre(bool esNegra);

protected:
    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);

private:  

};

#endif
