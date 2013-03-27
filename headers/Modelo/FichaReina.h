#ifndef __FichaReina_
#define __FichaReina_

#include "Ficha.h"


class FichaReina : public Ficha
{
public:

    ~FichaReina(void);
    FichaReina(bool esNegra);

    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);

private:  


};

#endif
