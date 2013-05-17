#ifndef __FichaPeon_
#define __FichaPeon_

#include "Ficha.h"

class FichaPeon : public Ficha
{
public:

    ~FichaPeon(void);
    FichaPeon(std::string nombre);

private:  

    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);
};

#endif
