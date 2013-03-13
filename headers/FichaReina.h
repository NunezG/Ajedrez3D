#ifndef __FichaReina_
#define __FichaReina_

#include "FichaTorre.h"
#include "FichaAlfil.h"


class FichaReina : Ficha
{
public:

    ~FichaReina(void);
    FichaReina(bool esNegra);

    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);

private:  


};

#endif
