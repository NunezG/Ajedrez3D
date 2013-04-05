#ifndef __FichaTorre_
#define __FichaTorre_

#include "Ficha.h"

class FichaTorre : public Ficha
{
public:

    ~FichaTorre(void);
    FichaTorre(std::string nombre);

protected:
    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);

private:  

};

#endif