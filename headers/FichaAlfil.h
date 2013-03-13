#ifndef __FichaAlfil_
#define __FichaAlfil_

#include "Ficha.h"


class FichaAlfil : Ficha
{
public:

    ~FichaAlfil(void);
    FichaAlfil(bool esNegra);


protected:

//    bool setCasilla(int cas[2]);

    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);


private:  



};


#endif
